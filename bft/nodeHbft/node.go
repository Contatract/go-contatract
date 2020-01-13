package nodeHbft

import (
	"errors"
	"fmt"
	"sync"
	"time"

	"github.com/contatract/go-contatract/accounts"
	"github.com/contatract/go-contatract/bft/consensus/hbft"
	"github.com/contatract/go-contatract/blizparam"
	"github.com/contatract/go-contatract/common"
	types "github.com/contatract/go-contatract/core/types_elephant"
	core "github.com/contatract/go-contatract/core_elephant"
	"github.com/contatract/go-contatract/eth"
	"github.com/contatract/go-contatract/event"
)

type Node struct {
	//NodeID       string
	NodeTable    map[common.Address]int64 // stores the validators and the time that the node should start to seal a new block
	CurrentState *hbft.State
	CoinBase     common.Address

	ReceivedBlocks  []*types.Block    // block buffer that store the blocks we received.
	ReplyBuffer     *[]*hbft.ReplyMsg // stores the replies of pre-confirm or confirm messages
	confirmReplyCnt int

	chainHeadCh  chan core.ChainHeadEvent
	chainHeadSub event.Subscription
	isBusy       bool

	lastBlockTimeStamp int64 // the time stamp when the latest block received by the node

	MsgMutex      sync.Mutex
	ReplyBufMutex sync.Mutex
	SuccMutex     sync.Mutex

	Sealed map[common.Hash]bool

	Lamp       *eth.Ethereum
	EleBackend Elephant
	AccMan     *accounts.Manager
}

func (node *Node) reset(oldHead, newHead *types.Header, ethHeight uint64) {
	if node.CurrentState == nil {
		return
	}

	newestBlock := oldHead
	newestStage := node.CurrentState.GetNewestStateCompletedStage()
	if newestStage != nil {
		newestBlockHash := newestStage.BlockHash
		for _, block := range node.CurrentState.Blocks {
			if newestBlockHash.Equal(block.HashNoBft()) {
				newestBlock = block.Header()
			}
		}
	}

	if newHead.Number.Uint64() >= newestBlock.Number.Uint64() {
		newestHash := newestBlock.HashNoBft()
		if node.CurrentState == nil || node.CurrentState.CurrentStage == hbft.Idle {

		} else if node.CurrentState.CurrentStage == hbft.Confirm && newestHash.Equal(newHead.HashNoBft()) {
			LogStage(fmt.Sprintf("Confirm, seq: %d, view: %d, prim: %s",
				node.CurrentState.SequenceID, node.CurrentState.ViewID, node.CurrentState.ViewPrimary), true)
		} else {
			LogStageReset()
		}

		node.CurrentState.Reset(true)
		node.ReceivedBlocks = node.ReceivedBlocks[len(node.ReceivedBlocks)-1:]
	} else {
		node.CurrentState.ClearConnected(newHead)

		if len(node.ReceivedBlocks) > 0 {
			delHeight := uint64(0)
			for _, block := range node.ReceivedBlocks {
				if block.NumberU64() < newHead.Number.Uint64() {
					delHeight += 1
				}
			}
			node.ReceivedBlocks = node.ReceivedBlocks[delHeight:]
		}
	}
}

// loop is the hbft node's main event loop, waiting for and reacting to
// outside blockchain events.
func (node *Node) loop() {
	// Track the previous head headers for transaction reorgs
	head := node.EleBackend.GetCurrentBlock()

	// Keep waiting for and reacting to the various events
	for {
		select {
		// Handle ChainHeadEvent
		case ev := <-node.chainHeadCh:
			if ev.Block != nil {
				node.lastBlockTimeStamp = time.Now().Unix()
				node.reset(head.Header(), ev.Block.Header(), ev.EthHeight)
				head = ev.Block
				sealers, _ := node.EleBackend.GetCurRealSealers()
				node.UpdateNodeTable(head.Coinbase(), node.lastBlockTimeStamp, sealers)
			}
		// Be unsubscribed due to system stopped
		case <-node.chainHeadSub.Err():
			return
		}
	}
}

func (node *Node) SendHBFTMsg(msg interface{}, msgType hbft.TypeHBFTMsg) {
	go node.EleBackend.SendBFTMsg(msg, uint(msgType))
}

func (node *Node) ValidateNewBlocks(preConfirmMsg *hbft.PreConfirmMsg) error {
	blocks := make([]*types.Block, 0)
	completedStages := preConfirmMsg.CurState.Completed
	for i := 0; i < len(completedStages); i++ {
		hash := completedStages[i].BlockHash
		for _, receivedBlock := range node.ReceivedBlocks {
			if hash.Equal(receivedBlock.HashNoBft()) {
				HBFTDebugInfo(fmt.Sprintf("ValidateNewBlocks receivedBlock, %s", receivedBlock.HashNoBft().String()))
				HBFTDebugInfo(fmt.Sprintf("ValidateNewBlocks parent, %s", receivedBlock.ParentNoBftHash().String()))

				blocks = append(blocks, receivedBlock)
			}
		}
	}
	blocks = append(blocks, preConfirmMsg.NewBlock)

	return node.EleBackend.ValidateNewBftBlocks(blocks)
}

// HandleReq can be called when our node starting mining a block.
// Consensus start procedure for the Primary.
func (node *Node) HandleReq(reqMsg *hbft.RequestMsg) (*hbft.PreConfirmMsg, error) {
	// Create a new state for the new consensus if the current state is nil.
	node.createStateForNewConsensus(reqMsg)
	node.CurrentState.ViewPrimary = reqMsg.ViewPrimary
	node.CurrentState.AppendBlock(reqMsg.NewBlock)

	// Start the consensus process.
	for _, completed := range node.CurrentState.Completed {
		HBFTDebugInfo(fmt.Sprintf("StartConsensus state.Completed, %s", completed.Hash().String()))
	}
	preConfirmMsg, err := node.CurrentState.StartConsensus(reqMsg, node.ReplyBuffer, node.EleBackend.GetCurrentBlock())
	if err != nil {
		return nil, err
	} else {
		signature, err := node.getMsgSignature(preConfirmMsg.Hash())
		if err != nil {
			return nil, err
		}
		preConfirmMsg.Signature = signature

		return preConfirmMsg, nil
	}
}

// HandlePreConfirmMsg can be called when the node receives a pre-confirm message.
func (node *Node) HandlePreConfirmMsg(preConfirmMsg *hbft.PreConfirmMsg) (*hbft.ReplyMsg, error) {
	// Check Signature first
	if err := node.checkMsgSignature(preConfirmMsg); err != nil {
		return nil, err
	}
	// Create a new state for the new consensus if the current state is nil.
	node.createStateForNewConsensus(preConfirmMsg)
	node.CurrentState.AppendBlock(preConfirmMsg.NewBlock)

	// Check the preConfirm message if valid
	elephant := node.EleBackend
	err := node.CurrentState.CheckView(preConfirmMsg) // Check view
	if err != nil {
		return nil, err
	}
	err = node.CurrentState.CheckCurrentState(preConfirmMsg, elephant.GetCurrentBlock(), elephant.BFTOldestFutureBlock(), elephant.Get2fRealSealersCnt()) // Check current state
	if err != nil {
		return nil, err
	}
	err = node.ValidateNewBlocks(preConfirmMsg) // Check new blocks
	if err != nil {
		return nil, errors.New(fmt.Sprintf("ValidateNewBlocks failed, %s", err.Error()))
	}

	node.CurrentState.MsgLogs.PreConfirmMsgs[preConfirmMsg.ViewPrimary] = preConfirmMsg
	node.CurrentState.ViewPrimary = preConfirmMsg.ViewPrimary

	replyMsg, errReply := node.GetReplyMsg(preConfirmMsg)
	if errReply != nil {
		return nil, errReply
	} else {
		return replyMsg, nil
	}
}

// HandleConfirmMsg can be called when the node receives a confirm message.
func (node *Node) HandleConfirmMsg(confirmMsg *hbft.ConfirmMsg) (*hbft.ReplyMsg, error) {
	// Check Signature first
	if err := node.checkMsgSignature(confirmMsg); err != nil {
		return nil, err
	}
	// Create a new state for the new consensus if the current state is nil.
	node.createStateForNewConsensus(confirmMsg)
	if node.CurrentState == nil || node.CurrentState.CurrentStage == hbft.Idle {
		return nil, errors.New("the node is in idle state and discard the confirm message received")
	}

	// Check the preConfirm message if valid
	elephant := node.EleBackend
	err := node.CurrentState.CheckView(confirmMsg) // Check view
	if err != nil {
		return nil, err
	}
	err = node.CurrentState.CheckCurrentState(confirmMsg, elephant.GetCurrentBlock(), nil, elephant.Get2fRealSealersCnt()) // Check current state
	if err != nil {
		return nil, err
	}

	node.CurrentState.MsgLogs.ConfirmMsgs[confirmMsg.ViewPrimary] = confirmMsg
	node.CurrentState.ViewPrimary = confirmMsg.ViewPrimary
	node.EleBackend.AddBFTFutureBlock(node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1])
	HBFTDebugInfo(fmt.Sprintf("AddBFTFutureBlock block, %s", node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1].HashNoBft().String()))

	replyMsg, errReply := node.GetReplyMsg(confirmMsg)
	if errReply != nil {
		return nil, errReply
	} else {
		return replyMsg, nil
	}
}

func (node *Node) GetConfirmMsg() (*hbft.ConfirmMsg, error) {
	if len(node.CurrentState.Blocks) == 0 {
		return nil, errors.New("GetConfirmMsg failed, there is no any block in current state")
	}

	stageCompleted := &types.HBFTStageCompleted{
		ViewID:      node.CurrentState.ViewID,
		SequenceID:  node.CurrentState.SequenceID,
		BlockHash:   node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1].HashNoBft(),
		BlockNum:    node.CurrentState.Blocks[len(node.CurrentState.Blocks)-1].NumberU64(),
		MsgType:     uint(hbft.MsgPreConfirm),
		MsgHash:     node.CurrentState.MsgHash,
		ValidSigns:  make([][]byte, 0),
		ParentStage: node.CurrentState.GetNewestCompletedStage(node.EleBackend.GetCurrentBlock()).Hash(),
	}
	for _, reply := range *node.ReplyBuffer {
		if stageCompleted.MsgHash.Equal(reply.MsgHash) {
			stageCompleted.ValidSigns = append(stageCompleted.ValidSigns, reply.Signature)
		}
	}
	if len(stageCompleted.ValidSigns) <= node.EleBackend.Get2fRealSealersCnt() {
		return nil, errors.New("GetConfirmMsg failed, not enough HBFT pre-confirm stage message")
	}

	curCompleted := make([]*types.HBFTStageCompleted, 0)
	for _, completed := range node.CurrentState.Completed {
		curCompleted = append(curCompleted, completed)
	}
	curCompleted = append(curCompleted, stageCompleted)
	curState := &hbft.StateMsg{
		ViewID:       node.CurrentState.ViewID,
		SequenceID:   node.CurrentState.SequenceID,
		CurrentStage: node.CurrentState.CurrentStage,
		Completed:    curCompleted,
	}

	confirmMsg := &hbft.ConfirmMsg{
		ViewPrimary: node.CurrentState.ViewPrimary,
		ViewID:      node.CurrentState.ViewID,
		SequenceID:  node.CurrentState.SequenceID,
		CurState:    curState,
	}

	signature, err := node.getMsgSignature(confirmMsg.Hash())
	if err != nil {
		return nil, err
	}
	confirmMsg.Signature = signature

	node.CurrentState.SetStageCompleted(stageCompleted)
	HBFTDebugInfo(fmt.Sprintf("SetStageCompleted stage, %s", stageCompleted.Hash().String()))
	HBFTDebugInfo(fmt.Sprintf("SetStageCompleted parent, %s", stageCompleted.ParentStage.String()))

	return confirmMsg, nil
}

func (node *Node) GetReplyMsg(msg hbft.MsgHbftConsensus) (*hbft.ReplyMsg, error) {
	replyMsg := &hbft.ReplyMsg{
		ViewPrimary: msg.GetViewPrimary(),
		ViewID:      msg.GetViewID(),
		SequenceID:  msg.GetSequenceID(),
		MsgHash:     msg.Hash(),
	}

	switch msg.(type) {
	case *hbft.PreConfirmMsg:
		replyMsg.MsgType = hbft.MsgPreConfirm

	case *hbft.ConfirmMsg:
		replyMsg.MsgType = hbft.MsgConfirm
	}

	signature, err := node.getMsgSignature(replyMsg.MsgHash)
	if err != nil {
		return nil, err
	}
	replyMsg.Signature = signature

	return replyMsg, nil
}

func (node *Node) createStateForNewConsensus(msg hbft.MsgHbftConsensus) {
	node.confirmReplyCnt = 0
	if node.CurrentState != nil && node.CurrentState.CurrentStage != hbft.Idle {
		return
	}

	blocks := make([]*types.Block, 0)
	if node.CurrentState != nil {
		blocks = node.CurrentState.Blocks
	}
	// Create a new state for this new consensus process in the Primary
	switch msg.(type) {
	case *hbft.RequestMsg, *hbft.PreConfirmMsg:
		node.CurrentState = hbft.CreateState(msg.GetViewPrimary(), msg.GetViewID(), msg.GetSequenceID(), blocks)

	case *hbft.ConfirmMsg:
		return
	}
}

func (node *Node) routeMsg(msg interface{}) {
	node.MsgMutex.Lock()
	defer node.MsgMutex.Unlock()

	switch msg.(type) {
	case *hbft.RequestMsg:
		msgs := make([]*hbft.RequestMsg, 0)
		msgs = append(msgs, msg.(*hbft.RequestMsg))
		node.resolveMsg(msgs)

	case *hbft.PreConfirmMsg:
		msgs := make([]*hbft.PreConfirmMsg, 0)
		msgs = append(msgs, msg.(*hbft.PreConfirmMsg))
		node.resolveMsg(msgs)

	case *hbft.ConfirmMsg:
		msgs := make([]*hbft.ConfirmMsg, 0)
		msgs = append(msgs, msg.(*hbft.ConfirmMsg))
		node.resolveMsg(msgs)

	default:
		Error("routeMsg failed, unknown msg type")

	}
}

func (node *Node) resolveMsg(msgs interface{}) {
	switch msgs.(type) {
	case []*hbft.RequestMsg:
		err := node.resolveRequestMsg(msgs.([]*hbft.RequestMsg))
		if err != nil {
			Warn("resolveRequestMsg failed", "err", err)
		}

	case []*hbft.PreConfirmMsg:
		err := node.resolvePreConfirmMsg(msgs.([]*hbft.PreConfirmMsg))
		if err != nil {
			Warn("resolvePreConfirmMsg failed", "err", err)
		}

	case []*hbft.ConfirmMsg:
		err := node.resolveConfirmMsg(msgs.([]*hbft.ConfirmMsg))
		if err != nil {
			Warn("resolveConfirmMsg failed", "err", err)
		}
	}
}

func (node *Node) resolveRequestMsg(msgs []*hbft.RequestMsg) error {
	for _, reqMsg := range msgs {
		preConfirmMsg, err := node.HandleReq(reqMsg)
		if err != nil {
			return err
		}
		node.ReceivedBlocks = append(node.ReceivedBlocks, preConfirmMsg.NewBlock)

		// Change the stage to pre-confirm.
		node.CurrentState.CurrentStage = hbft.PreConfirm
		node.CurrentState.ViewID = preConfirmMsg.ViewID
		node.CurrentState.SequenceID = preConfirmMsg.SequenceID
		node.CurrentState.MsgHash = preConfirmMsg.Hash()

		*node.ReplyBuffer = make([]*hbft.ReplyMsg, 0)
		replyMsg, err := node.GetReplyMsg(preConfirmMsg)
		if err != nil {
			Error(err.Error())
		} else {
			node.AddReplyMsg(replyMsg)
		}

		LogStage(fmt.Sprintf("Pre-confirm, seq: %d, view: %d, prim: %s",
			preConfirmMsg.SequenceID, preConfirmMsg.ViewID, preConfirmMsg.ViewPrimary), false)

		node.SendHBFTMsg(preConfirmMsg, hbft.MsgPreConfirm)
	}

	return nil
}

func (node *Node) resolvePreConfirmMsg(msgs []*hbft.PreConfirmMsg) error {
	for _, preConfirmMsg := range msgs {
		replyMsg, err := node.HandlePreConfirmMsg(preConfirmMsg)
		if err != nil {
			return err
		}
		node.ReceivedBlocks = append(node.ReceivedBlocks, preConfirmMsg.NewBlock)

		// Change the stage to pre-confirm.
		node.CurrentState.CurrentStage = hbft.PreConfirm
		node.CurrentState.ViewID = preConfirmMsg.ViewID
		node.CurrentState.SequenceID = preConfirmMsg.SequenceID

		LogStage(fmt.Sprintf("Pre-confirm, seq: %d, view: %d, prim: %s",
			preConfirmMsg.SequenceID, preConfirmMsg.ViewID, preConfirmMsg.ViewPrimary), false)

		node.SendHBFTMsg(replyMsg, hbft.MsgReply)
	}

	return nil
}

func (node *Node) resolveConfirmMsg(msgs []*hbft.ConfirmMsg) error {
	for _, confirmMsg := range msgs {
		replyMsg, err := node.HandleConfirmMsg(confirmMsg)
		if err != nil {
			return err
		}
		for _, completed := range confirmMsg.CurState.Completed {
			node.CurrentState.SetStageCompleted(completed)

			HBFTDebugInfo(fmt.Sprintf("SetStageCompleted stage, %s", completed.Hash().String()))
			HBFTDebugInfo(fmt.Sprintf("SetStageCompleted parent, %s", completed.ParentStage.String()))
		}

		// Change the stage to pre-confirm.
		node.CurrentState.CurrentStage = hbft.Confirm
		node.CurrentState.ViewID = confirmMsg.ViewID
		node.CurrentState.SequenceID = confirmMsg.SequenceID

		LogStage(fmt.Sprintf("Pre-confirm, seq: %d, view: %d, prim: %s",
			confirmMsg.SequenceID, confirmMsg.ViewID, confirmMsg.ViewPrimary), true)
		LogStage(fmt.Sprintf("Confirm, seq: %d, view: %d, prim: %s",
			confirmMsg.SequenceID, confirmMsg.ViewID, confirmMsg.ViewPrimary), false)

		node.SendHBFTMsg(replyMsg, hbft.MsgReply)
	}

	return nil
}

func (node *Node) sealed(blockHash common.Hash) bool {
	node.SuccMutex.Lock()
	defer node.SuccMutex.Unlock()

	for hash, succ := range node.Sealed {
		if hash.Equal(blockHash) {
			if succ {
				return true
			}
		}
	}
	return false
}

func (node *Node) getMsgSignature(msgHash common.Hash) ([]byte, error) {
	passwd := blizparam.GetCsSelfPassphrase()
	if common.EmptyAddress(node.CoinBase) {
		var err error
		if node.CoinBase, err = node.EleBackend.Etherbase(); err != nil {
			return nil, err
		}
	}
	return node.HbftSign(node.CoinBase, passwd, msgHash.Bytes())
}

func (node *Node) checkMsgSignature(msg hbft.MsgHbftConsensus) error {
	switch msg.(type) {
	case *hbft.PreConfirmMsg, *hbft.ConfirmMsg:
		addr, err := node.HbftEcRecover(msg.Hash().Bytes(), msg.GetSignature())
		if err != nil {
			return err
		}
		sealers, _ := node.EleBackend.GetCurRealSealers()
		curSealer := node.GetCurrentSealer(sealers, false)
		if !addr.Equal(curSealer) {
			return fmt.Errorf("checkMsgSignature failed, the sealer address %s is not valid, which is supposed to be %s",
				addr.String(), curSealer.String())
		}

		primary := common.HexToAddress(msg.GetViewPrimary())
		if !addr.Equal(primary) {
			return fmt.Errorf("checkMsgSignature failed, view primary address %s is not valid", msg.GetViewPrimary())
		}
		return nil

	case *hbft.ReplyMsg:
		_, err := node.HbftEcRecover(msg.GetMsgHash().Bytes(), msg.GetSignature())
		if err != nil {
			return err
		}
		return nil
	}
	return errors.New("checkMsgSignature failed, unknown msg type")
}
