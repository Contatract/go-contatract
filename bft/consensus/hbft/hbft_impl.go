package hbft

import (
	"errors"
	"fmt"
	"sync"

	"github.com/contatract/go-contatract/common"
	types "github.com/contatract/go-contatract/core/types_elephant"
)

type State struct {
	ViewPrimary  string
	ViewID       uint64
	SequenceID   uint64
	CurrentStage Stage
	MsgHash      common.Hash
	Blocks       []*types.Block
	Completed    map[common.Hash]*types.HBFTStageCompleted
	MsgLogs      *MsgLogs

	mu sync.Mutex
}

type StateMsg struct {
	ViewID       uint64
	SequenceID   uint64
	CurrentStage Stage
	Completed    []*types.HBFTStageCompleted
}

type MsgLogs struct {
	ReqMsg         *RequestMsg
	PreConfirmMsgs map[string]*PreConfirmMsg
	ConfirmMsgs    map[string]*ConfirmMsg
}

// stage represents that the node in which state in the consensus process
type Stage uint

const (
	Idle         Stage = iota // Node is created successfully, but the consensus process is not started yet.
	PreConfirm                // The `preConfirmMsg` is processed successfully. The node is ready to head to the Confirm stage.
	Confirm                   // The `confirmMsg` is processed successfully. The node is ready to head to the next block processing.
	InvalidStage              // Unavailable stage
)

// f: # of Byzantine faulty node
// f = (n­1) / 3
// n = 4, in this case.
const f = 1
const f2 = 1 // 2 * f // test

func GetF2() int {
	return f2
}

// lastSequenceID will be -1 if there is no last sequence ID.
func CreateState(viewPrimary string, viewID uint64, sequenceID uint64, blocks []*types.Block) *State {
	return &State{
		ViewPrimary:  viewPrimary,
		ViewID:       viewID,
		SequenceID:   sequenceID,
		CurrentStage: Idle,
		Blocks:       blocks,
		Completed:    make(map[common.Hash]*types.HBFTStageCompleted),
		MsgLogs: &MsgLogs{
			ReqMsg:         nil,
			PreConfirmMsgs: make(map[string]*PreConfirmMsg),
			ConfirmMsgs:    make(map[string]*ConfirmMsg),
		},
	}
}

func (state *State) GetNewestStateCompletedStage() *types.HBFTStageCompleted {
	curStateStage := new(types.HBFTStageCompleted)
	curStateStage.MsgHash = common.Hash{}
	viewID, seqID, msgType, blockNum := uint64(0), uint64(0), uint(0), uint64(0)
	num := 0
	if state.Completed != nil {
		for _, completed := range state.Completed {
			if num == 0 {
				curStateStage, viewID, seqID, msgType, blockNum = completed, completed.ViewID, completed.SequenceID, completed.MsgType, completed.BlockNum
			} else if completed.SequenceID > seqID || (completed.SequenceID == seqID && completed.ViewID > viewID) ||
				(completed.SequenceID == seqID && completed.ViewID == viewID && completed.MsgType > msgType) ||
				(completed.SequenceID == seqID && completed.ViewID == viewID && completed.MsgType == msgType && completed.BlockNum > blockNum) {
				curStateStage, viewID, seqID, msgType, blockNum = completed, completed.ViewID, completed.SequenceID, completed.MsgType, completed.BlockNum
			}
			num++
		}
	}

	return curStateStage
}

func (state *State) GetNewestCompletedStage(currentBlock *types.Block) *types.HBFTStageCompleted {
	HBFTStageChain := currentBlock.HBFTStageChain()
	if HBFTStageChain == nil || len(HBFTStageChain) == 0 {
		return state.GetNewestStateCompletedStage()
	}

	blockStage := HBFTStageChain[len(HBFTStageChain)-1]
	stateStage := state.GetNewestStateCompletedStage()
	if stateStage.SequenceID > blockStage.SequenceID ||
		(stateStage.SequenceID == blockStage.SequenceID && stateStage.ViewID > blockStage.ViewID) ||
		(stateStage.SequenceID == blockStage.SequenceID && stateStage.ViewID == blockStage.ViewID && stateStage.MsgType > blockStage.MsgType) {
		return stateStage
	} else {
		return blockStage
	}
}

func (state *State) CheckView(msg interface{}) error {
	switch msg.(type) {
	case *PreConfirmMsg:
		m := msg.(*PreConfirmMsg)
		if (state.CurrentStage == PreConfirm || state.CurrentStage == Confirm) && state.ViewID == m.ViewID &&
			state.SequenceID == m.SequenceID && state.ViewPrimary == m.ViewPrimary {
			return errors.New(fmt.Sprintf("CheckView failed, %s, seq: %d, view: %d, prim: %s, statePrim: %s", SameViewPrimaryErr,
				m.SequenceID, m.ViewID, m.ViewPrimary, state.ViewPrimary))
		} else if state.SequenceID < m.SequenceID || (m.SequenceID == state.SequenceID && m.ViewID < state.ViewID) {
			return errors.New(fmt.Sprintf("CheckView failed, %s", InvalidViewOrSeqIDErr))
		}

	case *ConfirmMsg:
		m := msg.(*ConfirmMsg)
		if state.CurrentStage != Idle && (state.ViewID != m.ViewID || state.SequenceID != m.SequenceID || state.ViewPrimary != m.ViewPrimary) {
			return errors.New(fmt.Sprintf("CheckView failed, %s, seq: %d, view: %d, prim: %s, statePrim: %s", InvalidViewOrSeqIDErr,
				m.SequenceID, m.ViewID, m.ViewPrimary, state.ViewPrimary))
		}
	}

	return nil
}

func (state *State) CheckCurrentState(msg interface{}, currentBlock, BFTFuture *types.Block, cnt2f int) error {
	switch msg.(type) {
	case *PreConfirmMsg:
		preConfirmMsg := msg.(*PreConfirmMsg)
		err := state.CheckCompletedStage(preConfirmMsg.CurState.Completed, currentBlock, cnt2f)
		if err != nil {
			return err
		}

		newestBlockInConfirm := state.GetNewestStateCompletedStage().BlockHash
		if state.CurrentStage == Confirm && !newestBlockInConfirm.Equal(preConfirmMsg.NewBlock.ParentNoBftHash()) {
			return errors.New(fmt.Sprintf("CheckCurrentState failed, %s case 1, whose parent is supposed to be %s", InvalidNewBlockErr,
				newestBlockInConfirm.String()))
		} else if BFTFuture != nil {
			newestBlockInConfirmHeight := BFTFuture.NumberU64()
			if preConfirmMsg.NewBlock.NumberU64() == newestBlockInConfirmHeight+1 &&
				!newestBlockInConfirm.Equal(preConfirmMsg.NewBlock.ParentNoBftHash()) {
				return errors.New(fmt.Sprintf("CheckCurrentState failed, %s case 2, whose parent is supposed to be %s", InvalidNewBlockErr,
					newestBlockInConfirm.String()))
			} else if preConfirmMsg.NewBlock.NumberU64() == newestBlockInConfirmHeight &&
				!newestBlockInConfirm.Equal(preConfirmMsg.NewBlock.HashNoBft()) {
				return errors.New(fmt.Sprintf("CheckCurrentState failed, %s case 3, whose parent is supposed to be %s", InvalidNewBlockErr,
					newestBlockInConfirm.String()))
			}
		}

	case *ConfirmMsg:
		confirmMsg := msg.(*ConfirmMsg)
		err := state.CheckCompletedStage(confirmMsg.CurState.Completed, currentBlock, cnt2f)
		if err != nil {
			return err
		}

		if len(state.Blocks) == 0 {
			return errors.New(fmt.Sprintf("CheckCurrentState failed, %s", NoSpecificBlockErr))
		}
		if len(confirmMsg.CurState.Completed) == 0 {
			return errors.New(fmt.Sprintf("CheckCurrentState failed, %s", InvalidCompletedErr))
		}
		newestBlockInPreConfirm := state.Blocks[len(state.Blocks)-1]
		newestBlockHashInMsg := confirmMsg.CurState.Completed[len(confirmMsg.CurState.Completed)-1].BlockHash
		if state.CurrentStage == PreConfirm && !newestBlockHashInMsg.Equal(newestBlockInPreConfirm.HashNoBft()) {
			return errors.New(fmt.Sprintf("CheckCurrentState failed, %s", InvalidNewBlockErr))
		} else if state.CurrentStage == Confirm {
			if currentBlock.Number().Uint64() >= newestBlockInPreConfirm.Number().Uint64() {
				state.Reset(true)
			}
			return errors.New(fmt.Sprintf("CheckCurrentState failed, %s", ShouldNotHandleErr))
		}

	}

	return nil
}

func (state *State) CheckCompletedStage(completedStages []*types.HBFTStageCompleted, currentBlock *types.Block, cnt2f int) error {
	var parentHash common.Hash
	for i := 0; i < len(completedStages); i++ {
		if i == 0 {
			blockStage := new(types.HBFTStageCompleted)
			HBFTStageChain := currentBlock.HBFTStageChain()
			if HBFTStageChain != nil && len(HBFTStageChain) != 0 {
				blockStage = HBFTStageChain[len(HBFTStageChain)-1]
			}
			if blockStage == nil {
				return errors.New(fmt.Sprintf("CheckCompletedStage failed case 1, %s", InvalidParentHashErr))
			}

			newest := blockStage.Hash()
			if currentBlock.NumberU64() > 0 && blockStage.MsgType == uint(MsgPreConfirm) {
				// if the msgType of newest stage in the latest block is MsgPreConfirm, the stage may also belong to the next block
				if !newest.Equal(completedStages[i].Hash()) && !newest.Equal(completedStages[i].ParentStage) {
					return errors.New(fmt.Sprintf("CheckCompletedStage failed case 2, %s", InvalidParentHashErr))
				}
			} else {
				if !newest.Equal(completedStages[i].ParentStage) {
					return errors.New(fmt.Sprintf("CheckCompletedStage failed case 3, %s", InvalidParentHashErr))
				}
			}
		} else {
			if !parentHash.Equal(completedStages[i].ParentStage) {
				return errors.New(fmt.Sprintf("CheckCompletedStage failed case 4, %s", InvalidParentHashErr))
			}
		}
		parentHash = completedStages[i].Hash()

		if len(completedStages[i].ValidSigns) <= cnt2f {
			return errors.New(fmt.Sprintf("CheckCompletedStage failed, %s", InvalidSignsCntErr))
		}

		weHaveTheBlock := false
		for _, block := range state.Blocks {
			blockHash := block.HashNoBft()
			blockNum := block.NumberU64()
			if blockHash.Equal(completedStages[i].BlockHash) && blockNum == completedStages[i].BlockNum {
				weHaveTheBlock = true
				break
			}
		}
		if !weHaveTheBlock {
			return errors.New(fmt.Sprintf("CheckCompletedStage failed, %s", NoSpecificBlockErr))
		}

	}

	return nil
}

func (state *State) StartConsensus(request *RequestMsg, replys *[]*ReplyMsg, currentBlock *types.Block) (*PreConfirmMsg, error) {
	curState := &StateMsg{
		ViewID:       request.ViewID,
		SequenceID:   request.SequenceID,
		CurrentStage: state.CurrentStage,
		Completed:    make([]*types.HBFTStageCompleted, 0),
	}

	curState.Completed = state.BuildCompletedStageChain()
	if len(curState.Completed) != len(state.Completed) {
		return nil, errors.New("can not build a correct chain for the completed stages in current state")
	}
	blockStageHash := types.EmptyHbftStage.Hash()
	blockStages := currentBlock.HBFTStageChain()
	if blockStages.Len() > 0 {
		blockStageHash = blockStages[blockStages.Len()-1].Hash()
	}
	if len(curState.Completed) > 0 &&
		!(blockStageHash.Equal(curState.Completed[0].ParentStage) || blockStageHash.Equal(curState.Completed[0].Hash())) {
		return nil, errors.New("can not build a correct chain for the completed stages in current state and current block")
	}

	return &PreConfirmMsg{
		ViewPrimary: request.ViewPrimary,
		ViewID:      request.ViewID,
		SequenceID:  request.SequenceID,
		NewBlock:    request.NewBlock,
		CurState:    curState,
	}, nil
}

func (state *State) BuildCompletedStageChain() (stages []*types.HBFTStageCompleted) {
	for _, completed := range state.Completed {
		if chain, ok := obtainCompletedStageChain(completed, state.Completed, 0); ok {
			chain = append(chain, completed)
			stages = append(stages, chain[:]...)
			return stages
		}
	}

	return []*types.HBFTStageCompleted{}
}

func obtainCompletedStageChain(completedStage *types.HBFTStageCompleted, completedMap map[common.Hash]*types.HBFTStageCompleted,
	chainLen int) ([]*types.HBFTStageCompleted, bool) {
	if completed, ok := completedMap[completedStage.ParentStage]; ok {
		chainLen += 1
		if chain, ok := obtainCompletedStageChain(completed, completedMap, chainLen); ok {
			chain = append(chain, completed)
			return chain, true
		}
	} else {
		if chainLen == len(completedMap)-1 {
			return make([]*types.HBFTStageCompleted, 0), true
		}
	}

	return []*types.HBFTStageCompleted{}, false
}

func (state *State) AppendBlock(b *types.Block) {
	state.mu.Lock()
	defer state.mu.Unlock()

	state.Blocks = append(state.Blocks, b)
}

func (state State) SetStageCompleted(stage *types.HBFTStageCompleted) {
	state.mu.Lock()
	defer state.mu.Unlock()

	state.Completed[stage.Hash()] = stage
}

func (state *State) Reset(clearCompleted bool) {
	state.mu.Lock()
	defer state.mu.Unlock()

	state.CurrentStage = Idle
	state.MsgHash = common.Hash{}
	state.Blocks = state.Blocks[len(state.Blocks)-1:]
	if clearCompleted {
		state.Completed = make(map[common.Hash]*types.HBFTStageCompleted)
	}
}

func (state *State) ClearConnected(newHead *types.Header) {
	state.mu.Lock()
	defer state.mu.Unlock()

	for hash, completed := range state.Completed {
		if completed.BlockNum <= newHead.Number.Uint64() {
			delete(state.Completed, hash)
		}
	}

	if len(state.Blocks) > 0 {
		delHeight := uint64(0)
		for _, block := range state.Blocks {
			if block.NumberU64() < newHead.Number.Uint64() {
				delHeight += 1
			}
		}
		state.Blocks = state.Blocks[delHeight:]
	}
}
