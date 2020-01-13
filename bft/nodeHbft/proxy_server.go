package nodeHbft

import (
	"errors"
	"fmt"
	"time"

	"github.com/contatract/go-contatract/accounts"
	"github.com/contatract/go-contatract/bft/consensus/hbft"
	"github.com/contatract/go-contatract/common"
	types "github.com/contatract/go-contatract/core/types_elephant"
	core "github.com/contatract/go-contatract/core_elephant"
	"github.com/contatract/go-contatract/crypto"
	"github.com/contatract/go-contatract/eth"
	"github.com/contatract/go-contatract/event"
)

const (
	BlockSealingBeat = time.Millisecond * 100

	BlockMinPeriodHbft     = time.Second * 2
	BlockMaxPeriodHbft     = time.Second * 6
	BlockMaxStartDelayHbft = (BlockMaxPeriodHbft - BlockMinPeriodHbft) / 2
	BlockAvgPeriodHbft     = BlockMaxPeriodHbft + BlockMinPeriodHbft - BlockMaxStartDelayHbft - BlockMinPeriodHbft/2

	NodeServerMinCountHbft = 4
)

type Elephant interface {
	Etherbase() (eb common.Address, err error)
	AccountManager() *accounts.Manager
	SendBFTMsg(msg interface{}, msgType uint)
	GetCurRealSealers() ([]common.Address, bool)
	GetRealSealersByNum(number uint64) ([]common.Address, bool)
	Get2fRealSealersCnt() int
	GetCurrentBlock() *types.Block
	AddBFTFutureBlock(b *types.Block)
	BFTFutureBlocks() []*types.Block
	BFTOldestFutureBlock() *types.Block
	NextIsNewSealersFirstBlock(block *types.Block) bool
	ValidateNewBftBlocks(blocks []*types.Block) error
	SubscribeChainHeadEvent(ch chan<- core.ChainHeadEvent) event.Subscription
}

func NewNode(lamp *eth.Ethereum, elephant Elephant) (*Node, error) {
	node := &Node{
		NodeTable:      make(map[common.Address]int64),
		ReceivedBlocks: make([]*types.Block, 0),
		ReplyBuffer:    new([]*hbft.ReplyMsg),
		chainHeadCh:    make(chan core.ChainHeadEvent, core.ChainHeadChanSize),
		isBusy:         false,
		Sealed:         make(map[common.Hash]bool),
		Lamp:           lamp,
		AccMan:         elephant.AccountManager(),
		EleBackend:     elephant,
	}

	coinBase, err := elephant.Etherbase()
	if err != nil {
		Warn("Etherbase have not be explicitly specified, the node can not start sealing")
	}
	node.CoinBase = coinBase

	return node, nil
}

// SubscribeChainHeadEvent Subscribes events from blockchain and start the loop
func (node *Node) SubscribeChainHeadEvent() {
	node.chainHeadSub = node.EleBackend.SubscribeChainHeadEvent(node.chainHeadCh)

	go node.loop()
}

func (node *Node) InitNodeTable() {
	lastTime := int64(0)
	if node.EleBackend.GetCurrentBlock().NumberU64() != 0 {
		lastTime = node.EleBackend.GetCurrentBlock().Time().Int64()
		if node.EleBackend.GetCurrentBlock().ReceivedAt.Unix()-lastTime > 0 &&
			node.EleBackend.GetCurrentBlock().ReceivedAt.Unix()-lastTime < int64(BlockMaxPeriodHbft.Seconds()) {
			lastTime = node.EleBackend.GetCurrentBlock().ReceivedAt.Unix()
		}
	}

	lastSealer := node.EleBackend.GetCurrentBlock().Coinbase()
	sealers, _ := node.EleBackend.GetCurRealSealers()
	node.UpdateNodeTable(lastSealer, lastTime, sealers)
}

func (node *Node) UpdateNodeTable(lastSealer common.Address, lastTime int64, sealers []common.Address) {
	node.NodeTable = make(map[common.Address]int64)
	num := 0
	for i, sealer := range sealers {
		if sealer.Equal(lastSealer) {
			num = i + 1
		}
	}
	for cnt := 0; cnt < len(sealers); cnt++ {
		if num == len(sealers) {
			num = 0
		}
		if cnt == 0 {
			node.NodeTable[sealers[num]] = lastTime + int64(BlockMinPeriodHbft.Seconds())
		} else {
			node.NodeTable[sealers[num]] = lastTime + int64(BlockMinPeriodHbft.Seconds()) +
				int64(cnt)*int64((BlockMinPeriodHbft+BlockMaxPeriodHbft).Seconds())
		}
		num++
	}
}

func (node *Node) IsBusy() bool {
	return node.isBusy
}

func (node *Node) SetBusy(flag bool) {
	node.isBusy = flag
}

func (node *Node) GetCurrentSealer(sealers []common.Address, selfWork bool) common.Address {
	if len(node.NodeTable) < NodeServerMinCountHbft {
		node.InitNodeTable()
	}

	now := time.Now().Unix()
	minTimeDiff := int64(0)
	sealerAddr := common.Address{}
	first := true
	for sealer, startTime := range node.NodeTable {
		if first && now-startTime >= 0 {
			minTimeDiff = getTimeDiff(now, startTime, len(sealers))
			sealerAddr = sealer
			first = false
		} else {
			if now-startTime >= 0 && getTimeDiff(now, startTime, len(sealers)) < minTimeDiff {
				minTimeDiff = getTimeDiff(now, startTime, len(sealers))
				sealerAddr = sealer
			}
		}
	}

	if selfWork && minTimeDiff > int64(BlockMaxStartDelayHbft.Seconds()) {
		return common.Address{}
	}

	return sealerAddr
}

func getTimeDiff(now, startTime int64, cntSealers int) int64 {
	return (now - startTime) % int64(cntSealers*int((BlockMinPeriodHbft+BlockMaxPeriodHbft).Seconds()))
}

func (node *Node) GetRequest(sealerAddr string, block *types.Block) {
	var msg hbft.RequestMsg
	currentState := node.CurrentState
	if currentState == nil {
		msg.ViewID, msg.SequenceID = 0, 0
	} else {
		newestStage := currentState.GetNewestCompletedStage(node.EleBackend.GetCurrentBlock())
		if newestStage == nil || common.EmptyHash(newestStage.MsgHash) {
			msg.ViewID, msg.SequenceID = 0, 0
		} else if node.EleBackend.GetCurrentBlock().NumberU64() != 0 &&
			node.EleBackend.NextIsNewSealersFirstBlock(node.EleBackend.GetCurrentBlock()) {
			msg.ViewID, msg.SequenceID = 0, newestStage.SequenceID+1
		} else {
			msg.ViewID, msg.SequenceID = newestStage.ViewID+1, newestStage.SequenceID
		}
	}

	msg.ViewPrimary = sealerAddr
	msg.Timestamp = uint64(time.Now().Unix())
	msg.NewBlock = block

	node.SetBusy(true)
	node.routeMsg(&msg)
}

func (node *Node) BlockSealedCompleted(blockHash common.Hash) bool {
	times := uint32(BlockAvgPeriodHbft.Nanoseconds() / BlockSealingBeat.Nanoseconds())
	ticker := time.NewTicker(BlockSealingBeat)
	defer ticker.Stop()
	var current uint32

	for {
		select {
		case <-ticker.C:
			if node.sealed(blockHash) {
				return true
			}
			current++

			if current >= times {
				node.SuccMutex.Lock()
				node.Sealed[blockHash] = false
				node.SuccMutex.Unlock()

				node.ReplyBufMutex.Lock()
				*node.ReplyBuffer = make([]*hbft.ReplyMsg, 0)
				node.ReplyBufMutex.Unlock()

				Warn(fmt.Sprintf("Block sealing timed out, seq: %d, view: %d, prim: %s",
					node.CurrentState.SequenceID, node.CurrentState.ViewID, node.CurrentState.ViewPrimary))
				return false
			}
		}
	}
}

func (node *Node) GetFakeStagesForTest(viewID uint64) []*types.HBFTStageCompleted {
	fake := new(types.HBFTStageCompleted)
	return fake.Fake(viewID, 0)
}

func (node *Node) HbftProcess(msg interface{}) {
	// First handle reply message
	if replyMsg, ok := msg.(*hbft.ReplyMsg); ok {
		sigAddr, err := node.HbftEcRecover(replyMsg.MsgHash.Bytes(), replyMsg.Signature)
		if err != nil {
			Error("HbftProcess failed", "err", err.Error())
			return
		}

		sealers, _ := node.EleBackend.GetCurRealSealers()
		for _, addr := range sealers {
			if sigAddr.Equal(addr) {
				node.AddReplyMsg(replyMsg)
				break
			}
		}
		return
	}

	node.routeMsg(msg)
}

func (node *Node) AddReplyMsg(replyMsg *hbft.ReplyMsg) {
	if node.CurrentState.CurrentStage == hbft.Idle {
		Warn(hbft.ShouldNotHandleErr)
		return
	}

	if replyMsg.MsgType == hbft.MsgPreConfirm && replyMsg.MsgHash.Equal(node.CurrentState.MsgHash) {
		node.ReplyBufMutex.Lock()
		*node.ReplyBuffer = append(*node.ReplyBuffer, replyMsg)

		var (
			confirmMsg *hbft.ConfirmMsg
			err        error
		)
		if len(*node.ReplyBuffer) == node.EleBackend.Get2fRealSealersCnt()+1 {
			HBFTDebugInfo("2f+1 MsgPreConfirm")
			confirmMsg, err = node.GetConfirmMsg()
			if err != nil {
				Warn(err.Error())
				node.ReplyBufMutex.Unlock()
				return
			}

			// Change the stage to confirm.
			node.CurrentState.CurrentStage = hbft.Confirm
			node.CurrentState.MsgHash = confirmMsg.Hash()
			*node.ReplyBuffer = make([]*hbft.ReplyMsg, 0)
			node.EleBackend.AddBFTFutureBlock(node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1])
			HBFTDebugInfo(fmt.Sprintf("AddBFTFutureBlock block, %s", node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1].HashNoBft().String()))

			LogStage(fmt.Sprintf("Pre-confirm, seq: %d, view: %d, prim: %s",
				confirmMsg.SequenceID, confirmMsg.ViewID, confirmMsg.ViewPrimary), true)
			LogStage(fmt.Sprintf("Confirm, seq: %d, view: %d, prim: %s",
				confirmMsg.SequenceID, confirmMsg.ViewID, confirmMsg.ViewPrimary), false)

			node.SendHBFTMsg(confirmMsg, hbft.MsgConfirm)
		}
		node.ReplyBufMutex.Unlock()

		if confirmMsg != nil {
			replyMsg, err := node.GetReplyMsg(confirmMsg)
			if err != nil {
				Warn(err.Error())
			} else {
				node.AddReplyMsg(replyMsg)
			}
		}

	} else if replyMsg.MsgType == hbft.MsgConfirm && replyMsg.MsgHash.Equal(node.CurrentState.MsgHash) {
		node.ReplyBufMutex.Lock()

		*node.ReplyBuffer = append(*node.ReplyBuffer, replyMsg)
		node.confirmReplyCnt += 1
		if node.confirmReplyCnt == node.EleBackend.Get2fRealSealersCnt()+1 {
			HBFTDebugInfo("2f+1 MsgConfirm")
			newestBlock := node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1]
			if _, ok := node.Sealed[newestBlock.Hash()]; !ok {
				stageCompleted := &types.HBFTStageCompleted{
					ViewID:      node.CurrentState.ViewID,
					SequenceID:  node.CurrentState.SequenceID,
					BlockHash:   newestBlock.HashNoBft(),
					BlockNum:    newestBlock.NumberU64(),
					MsgType:     uint(hbft.MsgConfirm),
					MsgHash:     node.CurrentState.MsgHash,
					ValidSigns:  make([][]byte, 0),
					ParentStage: node.CurrentState.GetNewestStateCompletedStage().Hash(),
				}
				for _, reply := range *node.ReplyBuffer {
					if stageCompleted.MsgHash.Equal(reply.MsgHash) {
						stageCompleted.ValidSigns = append(stageCompleted.ValidSigns, reply.Signature)
					}
				}
				if len(stageCompleted.ValidSigns) <= node.EleBackend.Get2fRealSealersCnt() {
					node.confirmReplyCnt -= 1
					node.ReplyBufMutex.Unlock()
					return
				}

				node.SuccMutex.Lock()
				node.Sealed[newestBlock.Hash()] = true
				node.SuccMutex.Unlock()

				node.CurrentState.Reset(false)
				node.CurrentState.SetStageCompleted(stageCompleted)
				HBFTDebugInfo(fmt.Sprintf("SetStageCompleted stage, %s", stageCompleted.Hash().String()))
				HBFTDebugInfo(fmt.Sprintf("SetStageCompleted parent, %s", stageCompleted.ParentStage.String()))

				*node.ReplyBuffer = make([]*hbft.ReplyMsg, 0)

				LogStage(fmt.Sprintf("Confirm, seq: %d, view: %d, prim: %s",
					replyMsg.SequenceID, replyMsg.ViewID, replyMsg.ViewPrimary), true)
			}
		}
		node.ReplyBufMutex.Unlock()
	}
}

func (node *Node) GetSealedBlockStages() ([]*types.HBFTStageCompleted, bool) {
	for hash, completed := range node.CurrentState.Completed {
		HBFTDebugInfo(fmt.Sprintf("GetSealedBlockStages Completed, %s", hash.String()))
		HBFTDebugInfo(fmt.Sprintf("GetSealedBlockStages parent, %s", completed.ParentStage.String()))
	}

	stages := make([]*types.HBFTStageCompleted, 0)
	newest := node.CurrentState.GetNewestStateCompletedStage()
	if stagePreConfirm, ok := node.CurrentState.Completed[newest.ParentStage]; ok {
		stages = append(stages, stagePreConfirm)
		stages = append(stages, newest)
		return stages, true
	}

	return nil, false
}

func (node *Node) GetCurrentStateStage() uint {
	return uint(node.CurrentState.CurrentStage)
}

func (node *Node) HbftSign(address common.Address, passwd string, data []byte) ([]byte, error) {
	// Look up the wallet containing the requested signer
	account := accounts.Account{Address: address}
	wallet, err := node.AccMan.Find(account)
	if err != nil {
		return nil, errors.New(fmt.Sprintf("HbftSign failed, %s", err.Error()))
	}
	// Assemble sign the data with the wallet
	signature, err := wallet.SignHashWithPassphrase(account, passwd, data)
	if err != nil {
		return nil, errors.New(fmt.Sprintf("HbftSign failed, %s", err.Error()))
	}

	return signature, nil
}

func (node *Node) HbftEcRecover(data, sig []byte) (common.Address, error) {
	if len(sig) != 65 {
		return common.Address{}, fmt.Errorf("signature must be 65 bytes long")
	}
	signature := make([]byte, len(sig))
	copy(signature, sig)

	rpk, err := crypto.Ecrecover(data, signature)
	if err != nil {
		return common.Address{}, err
	}
	pubKey := crypto.ToECDSAPub(rpk)
	recoveredAddr := crypto.PubkeyToAddress(*pubKey)
	return recoveredAddr, nil
}
