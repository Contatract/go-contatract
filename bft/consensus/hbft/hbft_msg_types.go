package hbft

import (
	"github.com/contatract/go-contatract/common"
	types "github.com/contatract/go-contatract/core/types_elephant"
	"github.com/contatract/go-contatract/crypto/sha3"
	"github.com/contatract/go-contatract/rlp"
)

var (
	EmptyPreConfirmMsg = &PreConfirmMsg{
		NewBlock: types.NewBlockWithHeader(types.EmptyHeader),
		CurState: &StateMsg{
			Completed: make([]*types.HBFTStageCompleted, 0),
		},
	}

	EmptyConfirmMsg = &ConfirmMsg{
		CurState: &StateMsg{
			Completed: make([]*types.HBFTStageCompleted, 0),
		},
	}

	EmptyReplyMsg = &ReplyMsg{
		MsgHash: common.Hash{},
	}
)

type MsgHbftConsensus interface {
	GetViewPrimary() string
	GetViewID() uint64
	GetSequenceID() uint64
	GetNewBlock() *types.Block
	GetCurStage() Stage
	GetCompleted() []*types.HBFTStageCompleted
	GetMsgType() TypeHBFTMsg
	GetMsgHash() common.Hash
	GetSignature() []byte
	Hash() common.Hash
}

type RequestMsg struct {
	ViewPrimary string       `json:"viewPrimary"`
	ViewID      uint64       `json:"viewID"`
	Timestamp   uint64       `json:"timestamp"`
	SequenceID  uint64       `json:"sequenceID"`
	NewBlock    *types.Block `json:"newBlock"`
}

func (m *RequestMsg) Hash() common.Hash {
	return rlpHash([]interface{}{
		m.ViewPrimary,
		m.ViewID,
		m.Timestamp,
		m.SequenceID,
		m.NewBlock,
	})
}

func (m *RequestMsg) GetViewPrimary() string {
	return m.ViewPrimary
}

func (m *RequestMsg) GetViewID() uint64 {
	return m.ViewID
}

func (m *RequestMsg) GetSequenceID() uint64 {
	return m.SequenceID
}

func (m *RequestMsg) GetNewBlock() *types.Block {
	return m.NewBlock
}

func (m *RequestMsg) GetCurStage() Stage {
	return InvalidStage
}

func (m *RequestMsg) GetCompleted() []*types.HBFTStageCompleted {
	return nil
}

func (m *RequestMsg) GetMsgType() TypeHBFTMsg {
	return MsgInvalid
}

func (m *RequestMsg) GetMsgHash() common.Hash {
	return common.Hash{}
}

func (m *RequestMsg) GetSignature() []byte {
	return nil
}

type PreConfirmMsg struct {
	ViewPrimary string       `json:"viewPrimary"`
	ViewID      uint64       `json:"viewID"`
	SequenceID  uint64       `json:"sequenceID"`
	NewBlock    *types.Block `json:"newBlock"`
	CurState    *StateMsg    `json:"curState"`
	Signature   []byte       `json:"signature"`
}

func (msg *PreConfirmMsg) Hash() common.Hash {
	return rlpHash([]interface{}{
		msg.ViewPrimary,
		msg.ViewID,
		msg.SequenceID,
		msg.NewBlock,
		msg.CurState,
	})
}

func (m *PreConfirmMsg) GetViewPrimary() string {
	return m.ViewPrimary
}

func (m *PreConfirmMsg) GetViewID() uint64 {
	return m.ViewID
}

func (m *PreConfirmMsg) GetSequenceID() uint64 {
	return m.SequenceID
}

func (m *PreConfirmMsg) GetNewBlock() *types.Block {
	return m.NewBlock
}

func (m *PreConfirmMsg) GetCurStage() Stage {
	return m.CurState.CurrentStage
}

func (m *PreConfirmMsg) GetCompleted() []*types.HBFTStageCompleted {
	return m.CurState.Completed
}

func (m *PreConfirmMsg) GetMsgType() TypeHBFTMsg {
	return MsgInvalid
}

func (m *PreConfirmMsg) GetMsgHash() common.Hash {
	return common.Hash{}
}

func (m *PreConfirmMsg) GetSignature() []byte {
	return m.Signature
}

type ConfirmMsg struct {
	ViewPrimary string    `json:"viewPrimary"`
	ViewID      uint64    `json:"viewID"`
	SequenceID  uint64    `json:"sequenceID"`
	CurState    *StateMsg `json:"curState"`
	Signature   []byte    `json:"signature"`
}

func (msg *ConfirmMsg) Hash() common.Hash {
	return rlpHash([]interface{}{
		msg.ViewPrimary,
		msg.ViewID,
		msg.SequenceID,
		msg.CurState,
	})
}

func (m *ConfirmMsg) GetViewPrimary() string {
	return m.ViewPrimary
}

func (m *ConfirmMsg) GetViewID() uint64 {
	return m.ViewID
}

func (m *ConfirmMsg) GetSequenceID() uint64 {
	return m.SequenceID
}

func (m *ConfirmMsg) GetNewBlock() *types.Block {
	return nil
}

func (m *ConfirmMsg) GetCurStage() Stage {
	return m.CurState.CurrentStage
}

func (m *ConfirmMsg) GetCompleted() []*types.HBFTStageCompleted {
	return m.CurState.Completed
}

func (m *ConfirmMsg) GetMsgType() TypeHBFTMsg {
	return MsgInvalid
}

func (m *ConfirmMsg) GetMsgHash() common.Hash {
	return common.Hash{}
}

func (m *ConfirmMsg) GetSignature() []byte {
	return m.Signature
}

type ReplyMsg struct {
	ViewPrimary string      `json:"viewPrimary"`
	ViewID      uint64      `json:"viewID"`
	SequenceID  uint64      `json:"sequenceID"`
	MsgType     TypeHBFTMsg `json:"MsgType"`
	MsgHash     common.Hash `json:"msgHash"`
	Signature   []byte      `json:"signature"`
}

func (msg *ReplyMsg) Hash() common.Hash {
	return rlpHash([]interface{}{
		msg.ViewPrimary,
		msg.ViewID,
		msg.SequenceID,
		msg.MsgType,
		msg.MsgHash,
	})
}

func (m *ReplyMsg) GetViewPrimary() string {
	return m.ViewPrimary
}

func (m *ReplyMsg) GetViewID() uint64 {
	return m.ViewID
}

func (m *ReplyMsg) GetSequenceID() uint64 {
	return m.SequenceID
}

func (m *ReplyMsg) GetNewBlock() *types.Block {
	return nil
}

func (m *ReplyMsg) GetCurStage() Stage {
	return InvalidStage
}

func (m *ReplyMsg) GetCompleted() []*types.HBFTStageCompleted {
	return nil
}

func (m *ReplyMsg) GetMsgType() TypeHBFTMsg {
	return m.MsgType
}

func (m *ReplyMsg) GetMsgHash() common.Hash {
	return m.MsgHash
}

func (m *ReplyMsg) GetSignature() []byte {
	return m.Signature
}

type TypeHBFTMsg uint

const (
	MsgPreConfirm TypeHBFTMsg = iota
	MsgConfirm
	MsgReply
	MsgInvalid
)

func rlpHash(x interface{}) (h common.Hash) {
	hw := sha3.NewKeccak256()
	rlp.Encode(hw, x)
	hw.Sum(h[:0])
	return h
}
