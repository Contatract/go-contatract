// Copyright 2018 The go-contatract Authors
// This file is part of the go-contatract library.
//
// The go-contatract library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The go-contatract library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the go-contatract library. If not, see <http://www.gnu.org/licenses/>.

package miner_elephant

import (
	"fmt"
	"math/big"
	"sync"
	"sync/atomic"
	"time"

	"github.com/contatract/go-contatract/common"
	"github.com/contatract/go-contatract/consensus"
	types "github.com/contatract/go-contatract/core/types_elephant"
	core "github.com/contatract/go-contatract/core_elephant"
	"github.com/contatract/go-contatract/core_elephant/state"
	"github.com/contatract/go-contatract/eth"

	//"github.com/contatract/go-contatract/consensus/misc"

	//"github.com/contatract/go-contatract/core/vm"
	"github.com/contatract/go-contatract/ethdb"
	"github.com/contatract/go-contatract/event"
	"github.com/contatract/go-contatract/log"
	"github.com/contatract/go-contatract/params"
	"gopkg.in/fatih/set.v0"
)

const (
	resultQueueSize  = 10
	miningLogAtDepth = 5

	// txChanSize is the size of channel listening to TxPreEvent.
	// The number is referenced from the size of tx pool.
	txChanSize = 4096
	// chainHeadChanSize is the size of channel listening to ChainHeadEvent.
	chainHeadChanSize = 10
	// chainSideChanSize is the size of channel listening to ChainSideEvent.
	chainSideChanSize = 10
)

// Agent can register themself with the worker
type Agent interface {
	Work() chan<- *Work
	SetReturnCh(chan<- *Result)
	Stop()
	Start()
	GetHashRate() int64
}

// Work is the workers current environment and holds
// all of the current state information
type Work struct {
	config *params.ElephantChainConfig
	signer types.Signer

	state       *state.StateDB // apply state changes here
	ancestors   *set.Set       // ancestor set (used for checking uncle parent validity)
	family      *set.Set       // family set (used for checking uncle invalidity)
	uncles      *set.Set       // uncle set
	localCount  int            // local tx count in cycle
	inputCount  int            // input tx count in cycle
	outputCount int            // output tx count in cycle

	Block *types.Block // the new block

	header   *types.Header
	txs      []*types.Transaction
	inputTxs []*types.ShardingTxBatch
	receipts []*types.Receipt

	createdAt time.Time
}

type Result struct {
	Work   *Work
	Block  *types.Block
	Stages []*types.HBFTStageCompleted
}

// worker is the main object which takes care of applying messages to the new state
type worker struct {
	config *params.ElephantChainConfig
	engine consensus.EngineCtt

	mu sync.Mutex

	// update loop
	mux          *event.TypeMux
	txCh         chan core.TxPreEvent
	txSub        event.Subscription
	chainHeadCh  chan core.ChainHeadEvent
	chainHeadSub event.Subscription
	chainSideCh  chan core.ChainSideEvent
	chainSideSub event.Subscription
	wg           sync.WaitGroup

	agents map[Agent]struct{}
	recv   chan *Result

	elephant Backend
	chain    *core.BlockChain
	proc     core.Validator
	chainDb  ethdb.Database

	coinbase common.Address
	extra    []byte

	currentMu sync.Mutex
	current   *Work

	uncleMu        sync.Mutex
	possibleUncles map[common.Hash]*types.Block

	unconfirmed *unconfirmedBlocks // set of locally mined blocks pending canonicalness confirmations

	futureParentBlock *types.Block // the block that has 2f+1 times pre-confirmed but timed out in confirm stage
	futureParentWork  *Work        // the work of the futureParent block, which has 2f+1 times pre-confirmed but timed out in confirm stage

	// atomic status counters
	mining int32
	atWork int32
	lamp   *eth.Ethereum
}

func newWorker(config *params.ElephantChainConfig, engine consensus.EngineCtt, coinbase common.Address, elephant Backend, mux *event.TypeMux, eth *eth.Ethereum) *worker {
	worker := &worker{
		config:         config,
		engine:         engine,
		elephant:       elephant,
		mux:            mux,
		txCh:           make(chan core.TxPreEvent, txChanSize),
		chainHeadCh:    make(chan core.ChainHeadEvent, chainHeadChanSize),
		chainSideCh:    make(chan core.ChainSideEvent, chainSideChanSize),
		chainDb:        elephant.ChainDb(),
		recv:           make(chan *Result, resultQueueSize),
		chain:          elephant.BlockChain(),
		proc:           elephant.BlockChain().Validator(),
		possibleUncles: make(map[common.Hash]*types.Block),
		coinbase:       coinbase,
		agents:         make(map[Agent]struct{}),
		unconfirmed:    newUnconfirmedBlocks(elephant.BlockChain(), miningLogAtDepth),
		lamp:           eth,
	}
	// Subscribe TxPreEvent for tx pool
	worker.txSub = elephant.TxPool().SubscribeTxPreEvent(worker.txCh)
	// Subscribe events for blockchain
	worker.chainHeadSub = elephant.BlockChain().SubscribeChainHeadEvent(worker.chainHeadCh)
	worker.chainSideSub = elephant.BlockChain().SubscribeChainSideEvent(worker.chainSideCh)
	go worker.update()

	go worker.wait()
	worker.commitNewWork()

	return worker
}

func (self *worker) setEtherbase(addr common.Address) {
	self.mu.Lock()
	defer self.mu.Unlock()
	self.coinbase = addr
}

func (self *worker) setExtra(extra []byte) {
	self.mu.Lock()
	defer self.mu.Unlock()
	self.extra = extra
}

func (self *worker) pending() (*types.Block, *state.StateDB) {
	self.currentMu.Lock()
	defer self.currentMu.Unlock()

	if atomic.LoadInt32(&self.mining) == 0 {
		return types.NewBlock(
			self.current.header,
			self.current.txs,
			self.current.inputTxs,
			nil,
			self.current.receipts,
			nil,
			&self.coinbase,
		), self.current.state.Copy()
	}
	return self.current.Block, self.current.state.Copy()
}

func (self *worker) pendingBlock() *types.Block {
	self.currentMu.Lock()
	defer self.currentMu.Unlock()

	if atomic.LoadInt32(&self.mining) == 0 {
		return types.NewBlock(
			self.current.header,
			self.current.txs,
			self.current.inputTxs,
			nil,
			self.current.receipts,
			nil,
			&self.coinbase,
		)
	}
	return self.current.Block
}

func (self *worker) start() {
	self.mu.Lock()
	defer self.mu.Unlock()

	atomic.StoreInt32(&self.mining, 1)

	// spin up agents
	for agent := range self.agents {
		agent.Start()
	}
}

func (self *worker) stop() {
	self.wg.Wait()

	self.mu.Lock()
	defer self.mu.Unlock()
	if atomic.LoadInt32(&self.mining) == 1 {
		for agent := range self.agents {
			agent.Stop()
		}
	}
	atomic.StoreInt32(&self.mining, 0)
	atomic.StoreInt32(&self.atWork, 0)
}

func (self *worker) register(agent Agent) {
	self.mu.Lock()
	defer self.mu.Unlock()
	self.agents[agent] = struct{}{}
	agent.SetReturnCh(self.recv)
}

func (self *worker) unregister(agent Agent) {
	self.mu.Lock()
	defer self.mu.Unlock()
	delete(self.agents, agent)
	agent.Stop()
}

func (self *worker) update() {
	defer self.txSub.Unsubscribe()
	defer self.chainHeadSub.Unsubscribe()
	defer self.chainSideSub.Unsubscribe()

	for {
		// A real event arrived, process interesting content
		select {
		// Handle ChainHeadEvent
		case <-self.chainHeadCh:
			// 一个新区块挂上本地主干区块链，我们需要在此基础上做下一个新区块的挖掘
			// 并挂载到这个已经挂上主干的区块后面
			// 这里需要触发一下，过滤掉已经存在的 tx 交易，重构下一个新区块的信息
			// 再提交
			self.commitNewWork()

		// Handle ChainSideEvent
		case ev := <-self.chainSideCh:
			// 收集了一个侧链分叉的交易区块，侧链是因为它的 difficult 难度值
			// 不大于主干canon的同一序号的新区块，于是被编到侧链位置，这里形成
			// Uncle叔区块
			self.uncleMu.Lock()
			self.possibleUncles[ev.Block.Hash()] = ev.Block
			self.uncleMu.Unlock()

		// Handle TxPreEvent
		case ev := <-self.txCh:
			// Apply transaction to the pending state if we're not mining
			if atomic.LoadInt32(&self.mining) == 0 {
				self.currentMu.Lock()
				acc, _ := types.Sender(self.current.signer, ev.Tx)
				txs := map[common.Address]types.Transactions{acc: {ev.Tx}}
				txset := types.NewTransactionsByPriceAndNonce(self.current.signer, txs)
				self.current.commitTransactions(self.mux, txset, self.chain, &self.coinbase, false, uint64(self.lamp.CurrBlockNum()))
				self.currentMu.Unlock()
			} /*else {
				// If we're mining, but nothing is being processed, wake on new transactions
				if self.config.Clique != nil && self.config.Clique.Period == 0 {
					self.commitNewWork()
				}
			}*/

		// System stopped
		case <-self.txSub.Err():
			return
		case <-self.chainHeadSub.Err():
			return
		case <-self.chainSideSub.Err():
			return
		}
	}
}

func BFTDebugInfo(msg string) {
	//log.Info("===HBFT Debug===%s", msg)
}

func (self *worker) wait() {
	for {
		mustCommitNewWork := true
		// JiangHan：这里表示 worker 的 recv 通道等到了挖矿成功的新block通知
		// 早先将 recv 通道注册给了agent.SetReturnCh(self.recv)，于是agent
		// 在 returnCh 上将新挖掘到的区块返回，这个新区块已经完成了POW计算，即将向
		// 全网广播（新区块就是之前在 self.update()的commitNewWork函数中提交的
		// 本地主干canon block）
		for result := range self.recv {
			atomic.AddInt32(&self.atWork, -1)

			if result == nil {
				continue
			}
			block := result.Block
			work := result.Work
			stages := result.Stages

			if common.GetconsenusBft() {
				if types.EmptyHbftHash.Equal(block.Header().BftHash) { // BFT pre-confirm stage timed out or should handle new BFT future blocks
					log.Warn("the BFT pre-confirm stage timed out or new BFT future blocks should be handle first, discard the block and commit new work")

					if futures := self.chain.BFTFutureBlocks(); len(futures) > 1 {
						self.handleBFTFutures(futures, stages, &mustCommitNewWork)
						continue
					}
					self.commitNewWork()
					continue
				} else if common.EmptyHash(block.Header().BftHash) { // BFT confirm stage timed out
					log.Warn("the BFT confirm stage timed out, commit new work after connecting current sealing block")
					if self.futureParentBlock != nil {
						if !self.handleFutureParent(stages, &mustCommitNewWork, true) {
							continue
						}
					} else {
						if futures := self.chain.BFTFutureBlocks(); len(futures) > 1 {
							if !self.handleBFTFutures(futures, stages, &mustCommitNewWork) {
								continue
							}
						} else {
							mustCommitNewWork = true
						}
					}

					self.futureParentBlock = self.chain.BFTNewestFutureBlock()
					self.futureParentWork = work
					if mustCommitNewWork {
						self.commitNewWork()
					}
					continue
				}

				if self.futureParentBlock != nil {
					if !self.handleFutureParent(stages, &mustCommitNewWork, false) {
						continue
					}
				} else if futures := self.chain.BFTFutureBlocks(); len(futures) > 1 {
					if !self.handleBFTFutures(futures, stages, &mustCommitNewWork) {
						continue
					}
				}
			}

			if !self.connectBlock(block, work, false, &mustCommitNewWork) {
				continue
			}
		}
	}
}

func (self *worker) handleFutureParent(stages []*types.HBFTStageCompleted, mustCommitNewWork *bool, confirmTiemdOut bool) bool {
	BFTDebugInfo(fmt.Sprintf("handleFutureParent, %s", self.futureParentBlock.HashNoBft().String()))

	if self.chain.GetBlockByNumber(self.futureParentBlock.NumberU64()) != nil { // outdated self.futureParentBlock
		self.chain.ClearBFTFutureBlock(self.futureParentBlock.HashNoBft())
		self.futureParentBlock = nil
		self.futureParentWork = nil

		if futures := self.chain.BFTFutureBlocks(); len(futures) > 1 {
			if !self.handleBFTFutures(futures, stages, mustCommitNewWork) {
				return false
			}
		} else {
			*mustCommitNewWork = true
		}
	} else if confirmTiemdOut { // BFT confirm stage timed out
		if !self.connectParentFuture(self.futureParentBlock, self.futureParentWork, stages, mustCommitNewWork) {
			return false
		}
	} else {
		sealedStages := self.getSealedBlockStages(self.futureParentBlock.HashNoBft(), stages)
		if len(sealedStages) == 0 {
			log.Error(fmt.Sprintf("sealing block failed, the worker do not have BFT completed stages of specific block, hashNoBft = %s",
				self.futureParentBlock.HashNoBft().String()))
			return false
		}
		self.futureParentBlock.SetBftStageComplete(sealedStages)
		if !self.connectBlock(self.futureParentBlock, self.futureParentWork, true, mustCommitNewWork) {
			return false
		}
		log.Info(fmt.Sprintf("connected BFT future block succesfully, future number = %d, future hashNoBFT = %s",
			self.futureParentBlock.NumberU64(), self.futureParentBlock.HashNoBft().String()))

		self.futureParentBlock = nil
		self.futureParentWork = nil
	}

	return true
}

func (self *worker) handleBFTFutures(futures []*types.Block, stages []*types.HBFTStageCompleted, mustCommitNewWork *bool) bool {
	for _, future := range futures {
		BFTDebugInfo(fmt.Sprintf("handleBFTFutures, %s", future.HashNoBft().String()))
	}

	futureParent := futures[0].WithSeal(futures[0].Header())
	curBlockHash := self.chain.CurrentBlock().Hash()
	if !curBlockHash.Equal(futures[0].ParentHash()) {
		log.Error(fmt.Sprintf("the oldest BFT future block's parent hash mismatch with the latest block in chain, future hashNoBft = %s",
			futureParent.HashNoBft().String()))
		return false
	}
	futureParentWork := self.finalizeWork(time.Now(), futureParent)
	if futureParentWork == nil {
		return false
	}
	if !self.connectParentFuture(futureParent, futureParentWork, stages, mustCommitNewWork) {
		return false
	}
	log.Info(fmt.Sprintf("connected BFT future block succesfully, future number = %d, future hashNoBFT = %s",
		futureParent.NumberU64(), futureParent.HashNoBft().String()))

	return true
}

func (self *worker) getSealedBlockStages(blockNoHbftHash common.Hash, stages []*types.HBFTStageCompleted) []*types.HBFTStageCompleted {
	for i, stage := range stages {
		if i < len(stages)-1 {
			if blockNoHbftHash.Equal(stage.BlockHash) && stages[i+1].ParentStage.Equal(stage.Hash()) {
				sealedStages := make([]*types.HBFTStageCompleted, 0)
				sealedStages = append(sealedStages, stage)
				sealedStages = append(sealedStages, stages[i+1])
				return sealedStages
			}
		}
	}

	return []*types.HBFTStageCompleted{}
}

func (self *worker) connectParentFuture(block *types.Block, work *Work, stages []*types.HBFTStageCompleted, mustCommitNewWork *bool) bool {
	sealedStages := self.getSealedBlockStages(block.HashNoBft(), stages)
	if len(sealedStages) == 0 {
		log.Error(fmt.Sprintf("connectParentFuture failed, the worker do not have BFT completed stages of the specific block, hashNoBft = %s",
			block.HashNoBft().String()))
		return false
	}
	block.SetBftStageComplete(sealedStages)
	if !self.connectBlock(block, work, true, mustCommitNewWork) {
		return false
	}

	return true
}

func (self *worker) connectBlock(block *types.Block, work *Work, isFutureBlock bool, mustCommitNewWork *bool) bool {
	self.chain.ClearBFTFutureBlock(block.HashNoBft())

	// Generate the transactions to other sharding
	shardingTxBatches, mapBatchNonce, errG := self.elephant.GenerateShardingTxBatches(block, work.state)
	if errG != nil {
		log.Error(errG.Error())
		return false
		//continue
	}

	stat, err := self.chain.WriteBlockWithState(block, work.receipts, work.state)
	if err != nil {
		log.Error("Failed writing block to chain when connecting a new block", "err", err,
			"number", block.NumberU64(), "hash", block.Hash(), "hashNoBft", block.HashNoBft())
		return false
		//continue
	}
	// check if canon block and write transactions
	if stat == core.CanonStatTy {
		// implicit by posting ChainHeadEvent
		*mustCommitNewWork = false
	}

	// Update batch nonce of state db
	for shardingID, batchNonce := range mapBatchNonce {
		work.state.UpdateStoreBatchNonce(shardingID, batchNonce)
	}

	// Broadcast the block and announce chain insertion event
	self.mux.Post(core.NewMinedBlockEvent{Block: block, ShardTxs: shardingTxBatches})

	var (
		events []interface{}
	)
	events = append(events, core.ChainEvent{Block: block, Hash: block.Hash()})
	if stat == core.CanonStatTy {
		events = append(events, core.ChainHeadEvent{Block: block})
	}
	self.chain.PostChainEvents(events)

	// Insert the block into the set of pending ones to wait for confirmations
	self.unconfirmed.Insert(block.NumberU64(), block.Hash(), block.HashNoBft())

	if !isFutureBlock && *mustCommitNewWork {
		self.commitNewWork()
	}

	return true
}

// push sends a new work task to currently live miner agents.
func (self *worker) push(work *Work) {
	if atomic.LoadInt32(&self.mining) != 1 {
		return
	}
	for agent := range self.agents {
		atomic.AddInt32(&self.atWork, 1)
		if ch := agent.Work(); ch != nil {
			ch <- work
		}
	}
}

// makeCurrent creates a new environment for the current cycle.
func (self *worker) makeCurrent(parent *types.Block, header *types.Header) error {
	state, err := self.chain.StateAt(parent.Root())
	if err != nil {
		return err
	}
	work := &Work{
		config:    self.config,
		signer:    types.NewEIP155Signer(self.config.ChainId),
		state:     state,
		ancestors: set.New(),
		family:    set.New(),
		uncles:    set.New(),
		header:    header,
		createdAt: time.Now(),
	}

	// when 08 is processed ancestors contain 07 (quick block)
	for _, ancestor := range self.chain.GetBlocksFromHash(parent.Hash(), 7) {
		for _, uncle := range ancestor.Uncles() {
			work.family.Add(uncle.Hash())
		}
		work.family.Add(ancestor.Hash())
		work.ancestors.Add(ancestor.Hash())
	}

	// Keep track of transactions which return errors so they can be removed
	work.localCount = 0
	work.inputCount = 0
	work.outputCount = 0
	self.current = work
	return nil
}

// makeCurrentFromFuture creates a new environment for the current cycle from a future block's state.
func (self *worker) getCurrentFromFuture(parentFuture *types.Block, header *types.Header) error {
	stateCache, err := self.chain.StateAt(self.chain.CurrentBlock().Root())
	if err != nil {
		return err
	}
	receipts, _, errP := self.elephant.BlockChain().Processor().Process(parentFuture, stateCache, uint64(self.lamp.CurrBlockNum()), &self.coinbase)
	if errP != nil {
		return errP
	}

	work := &Work{
		config:    self.config,
		signer:    types.NewEIP155Signer(self.config.ChainId),
		state:     stateCache,
		ancestors: set.New(),
		family:    set.New(),
		uncles:    set.New(),
		header:    header,
		createdAt: time.Now(),
		receipts:  receipts,
	}

	// when 08 is processed ancestors contain 07 (quick block)
	for _, ancestor := range self.chain.GetBlocksFromHash(parentFuture.Hash(), 7) {
		for _, uncle := range ancestor.Uncles() {
			work.family.Add(uncle.Hash())
		}
		work.family.Add(ancestor.Hash())
		work.ancestors.Add(ancestor.Hash())
	}

	self.current = work

	return nil
}

// makeCurrentFromFuture creates a new environment for the current cycle from a future block's state.
func (self *worker) makeCurrentFromFuture(parentFuture *types.Block, header *types.Header) error {
	stateCache, err := self.chain.StateAt(self.chain.CurrentBlock().Root())
	if err != nil {
		return err
	}
	_, _, err = self.elephant.BlockChain().Processor().Process(parentFuture, stateCache, uint64(self.lamp.CurrBlockNum()), &self.coinbase)
	if err != nil {
		return err
	}

	work := &Work{
		config:    self.config,
		signer:    types.NewEIP155Signer(self.config.ChainId),
		state:     stateCache,
		ancestors: set.New(),
		family:    set.New(),
		uncles:    set.New(),
		header:    header,
		createdAt: time.Now(),
	}

	// when 08 is processed ancestors contain 07 (quick block)
	for _, ancestor := range self.chain.GetBlocksFromHash(parentFuture.Hash(), 7) {
		for _, uncle := range ancestor.Uncles() {
			work.family.Add(uncle.Hash())
		}
		work.family.Add(ancestor.Hash())
		work.ancestors.Add(ancestor.Hash())
	}

	// Keep track of transactions which return errors so they can be removed
	work.localCount = 0
	work.inputCount = 0
	work.outputCount = 0
	self.current = work

	return nil
}

// JiangHan：收集本地的 pending tx, 并打包新区块，提交给minor agent做seal封装
// minor agent 的默认实现 CpuAgent 的 work 队列只容纳一个元素，所以提交不了的就
// 堵塞排队，如果 agent 比较多，则可以分发并行处理（也就是提到的所谓矿池）
func (self *worker) commitNewWork() {
	tstart := time.Now()
	work := self.finalizeWork(tstart, nil)
	if work == nil {
		return
	}

	// We only care about logging if we're actually mining.
	if atomic.LoadInt32(&self.mining) == 1 {
		log.Info("Commit new sealing work", "number", work.Block.Number(), "local", work.localCount, "input", work.inputCount, "output", work.outputCount, "elapsed", common.PrettyDuration(time.Since(tstart)))
	}

	self.push(work)
}

// finalizeWork finalizes the work for sealing a new block, when parameter newFuture is not nil, it represents the work finalized is the
// work of the newFuture block
func (self *worker) finalizeWork(tstart time.Time, newFuture *types.Block) *Work {
	self.mu.Lock()
	defer self.mu.Unlock()
	self.uncleMu.Lock()
	defer self.uncleMu.Unlock()
	self.currentMu.Lock()
	defer self.currentMu.Unlock()

	var reSelectTxs = false
	var future *types.Block
	parent := self.chain.CurrentBlock()
	if newFuture == nil {
		future = self.chain.BFTNewestFutureBlock()
		if future != nil {
			log.Info("Finalizing the block after the BFT future block", "future number", future.NumberU64(),
				"future hashNoBFT", future.HashNoBft())
			parent = future
			reSelectTxs = true
		}
	}

	tstamp := tstart.Unix()
	if parent.Time().Cmp(new(big.Int).SetInt64(tstamp)) >= 0 {
		tstamp = parent.Time().Int64() + 1
	}
	// this will ensure we're not going off too far in the future
	if now := time.Now().Unix(); tstamp > now+1 {
		wait := time.Duration(tstamp-now) * time.Second
		log.Info("Finalizing too far in the future", "wait", common.PrettyDuration(wait))
		time.Sleep(wait)
	}

	num := parent.Number()
	lampNum := big.NewInt(int64(self.lamp.CurrEleSealersBlockNum()))
	header := &types.Header{
		ParentHash:      parent.Hash(),
		ParentNoBftHash: parent.HashNoBft(),
		Number:          num.Add(num, common.Big1),
		LampBaseNumber:  lampNum,
		LampBaseHash:    self.lamp.CurrEleSealersBlockHash(),
		GasLimit:        core.CalcGasLimit(parent),
		Extra:           self.extra,
		Time:            big.NewInt(tstamp),
	}
	if newFuture != nil {
		header.ParentHash = newFuture.ParentHash()
		header.ParentNoBftHash = newFuture.ParentNoBftHash()
		header.Number = newFuture.Number()
		header.LampBaseNumber = newFuture.LampBaseNumber()
		header.LampBaseHash = newFuture.LampHash()
		header.GasLimit = newFuture.GasLimit()
		header.Extra = newFuture.Extra()
		header.Time = newFuture.Time()
	}

	// Only set the coinbase if we are mining (avoid spurious block rewards)
	if newFuture == nil && atomic.LoadInt32(&self.mining) == 1 {
		header.Coinbase = self.coinbase
	}
	if future == nil {
		if err := self.engine.Prepare(self.chain, header); err != nil {
			log.Error("Failed to prepare header for finalizing", "err", err)
			return nil
		}
	}

	// Could potentially happen if starting to mine in an odd state.
	if newFuture == nil {
		err := self.makeCurrent(parent, header)
		if err != nil {
			if future != nil {
				err := self.makeCurrentFromFuture(future, header)
				if err != nil {
					log.Error("Failed to create finalizing context", "err", err)
					return nil
				}
			} else {
				log.Error("Failed to create finalizing context", "err", err)
				return nil
			}
		}
	} else {
		err := self.getCurrentFromFuture(newFuture, newFuture.Header())
		if err != nil {
			log.Error("Failed to get finalizing context from BFT parent future block", "err", err)
			return nil
		}

		root := self.current.state.IntermediateRoot(false)
		if !root.Equal(newFuture.Header().Root) {
			log.Error("Failed to get finalizing context from BFT parent future block", "err", "the root of the state is not correct")
			return nil
		}
	}
	// Create the current work task and check any fork transitions needed
	work := self.current

	// JiangHan:从本地 pending 交易池 txpool 中选取交易进行签名并执行 commitTransactions
	// 将它们挂在新work上
	if newFuture == nil {
		pending, err := self.elephant.TxPool().Pending()
		if err != nil {
			log.Error("Failed to fetch pending transactions", "err", err)
			return nil
		}
		if reSelectTxs {
			alreadyHasTxs := make(map[common.Hash]struct{})
			for _, alreadyHasTx := range parent.Transactions() {
				alreadyHasTxs[alreadyHasTx.Hash()] = struct{}{}
			}
			for addr, addrTxs := range pending {
				length := len(addrTxs)
				for i := 0; i < len(addrTxs); {
					if _, ok := alreadyHasTxs[addrTxs[i].Hash()]; ok {
						addrTxs = append(addrTxs[:i], addrTxs[i+1:]...)
					} else {
						i++
					}
				}
				if len(addrTxs) == 0 {
					delete(pending, addr)
				} else if length != len(addrTxs) {
					pending[addr] = addrTxs
				}
			}
		}
		txs := types.NewTransactionsByPriceAndNonce(self.current.signer, pending)
		work.commitTransactions(self.mux, txs, self.chain, &self.coinbase, true, uint64(self.lamp.CurrBlockNum()))

		pendingInputTxs := make(types.ShardingTxBatches, 0)
		if reSelectTxs {
			alreadyHasInputTxs := make(map[common.Hash]struct{})
			for _, alreadyHasInputTx := range parent.InputTxs() {
				alreadyHasInputTxs[alreadyHasInputTx.Hash()] = struct{}{}
			}
			for _, txBatch := range self.elephant.TxPool().PendingInputTxs() {
				if _, ok := alreadyHasInputTxs[txBatch.Hash()]; !ok {
					pendingInputTxs = append(pendingInputTxs, txBatch)
				}
			}
		}
		self.commitInputTransactions(pendingInputTxs)

		// JiangHan：收集并执行完所有当前transaction, 这里进行区块封装
		// Create the new block to seal with the consensus engine
		var uncles []*types.Header
		if work.Block, err = self.engine.Finalize(self.chain, header, work.state, work.txs, work.inputTxs, uncles, work.receipts, &self.coinbase); err != nil {
			log.Error("Failed to finalize block for sealing", "err", err)
			return nil
		}
	}

	if atomic.LoadInt32(&self.mining) == 1 {
		self.unconfirmed.Shift(parent.NumberU64())
		//self.unconfirmed.Shift(work.Block.NumberU64() - 1)
	}

	return work
}

func (self *worker) commitInputTransactions(inputTxs types.ShardingTxBatches) {
	if len(inputTxs) == 0 {
		pending := self.elephant.TxPool().PendingInputTxs()
		pending = self.checkInputTxs(pending)
		pending = self.getValidInputTxs(pending)
		self.current.commitInputTxs(pending, &self.coinbase)
		//for _, batch := range pending {
		//	self.elephant.TxPool().RemoveInputTxs(batch.Hash()) // if mined timed out, it need to be deleted???
		//}
	} else {
		inputTxs = self.checkInputTxs(inputTxs)
		inputTxs = self.getValidInputTxs(inputTxs)
		self.current.commitInputTxs(inputTxs, &self.coinbase)
		//for _, batch := range inputTxs {
		//	self.elephant.TxPool().RemoveInputTxs(batch.Hash()) // if mined timed out, it need to be deleted???
		//}
	}
}

// Check input txs
func (self *worker) checkInputTxs(batches types.ShardingTxBatches) types.ShardingTxBatches {
	ret := make(types.ShardingTxBatches, 0, len(batches))
	for _, txBatch := range batches {
		toShardingID := txBatch.ToShardingID()
		height := self.current.state.GetShardingHeight(toShardingID)
		// Download has already dealed
		if txBatch.BlockHeight <= height {
			self.elephant.TxPool().RemoveInputTxs(txBatch.Hash())
			continue
		}
		ret = append(ret, txBatch)
	}
	return ret
}

func (self *worker) getValidInputTxs(batches types.ShardingTxBatches) types.ShardingTxBatches {
	valids := make(types.ShardingTxBatches, 0, len(batches))
	for _, txBatch := range batches {
		shardingID := txBatch.ShardingID
		verifiedValid := self.lamp.GetNewestValidHeaders()
		if verifiedValid[shardingID].BlockHeight == txBatch.BlockHeight &&
			verifiedValid[shardingID].Header.Equal(*txBatch.BlockHash) {
			valids = append(valids, txBatch)
		} else if verifiedValid[shardingID].BlockHeight > txBatch.BlockHeight {
			previous := self.lamp.GetValidPrevious(shardingID, uint64(self.lamp.CurrEleSealersBlockNum()), txBatch.BlockHeight)
			if txBatch.BlockHash.Equal(previous) {
				valids = append(valids, txBatch)
			}
		}
	}

	return valids
}

func (self *worker) commitUncle(work *Work, uncle *types.Header) error {
	hash := uncle.Hash()
	if work.uncles.Has(hash) {
		return fmt.Errorf("uncle not unique")
	}
	if !work.ancestors.Has(uncle.ParentHash) {
		return fmt.Errorf("uncle's parent unknown (%x)", uncle.ParentHash[0:4])
	}
	if work.family.Has(hash) {
		return fmt.Errorf("uncle already in family (%x)", hash)
	}
	work.uncles.Add(uncle.Hash())
	return nil
}

// update: consensus update
func (env *Work) commitTransactions(mux *event.TypeMux, txs *types.TransactionsByPriceAndNonce, bc *core.BlockChain,
	coinbase *common.Address, update bool, lampHeight uint64) {
	gp := new(core.GasPool).AddGas(env.header.GasLimit)

	for {
		// If we don't have enough gas for any further transactions then we're done
		if gp.Gas() < params.TxGas {
			log.Trace("Not enough gas for further transactions", "gp", gp)
			break
		}
		// Retrieve the next transaction and abort if all done
		tx := txs.Peek()
		if tx == nil {
			break
		}
		if !tx.IsLocalOrOutputTx(lampHeight, coinbase) {
			log.Error("Commit tx, type of tx isn't local or output")
			break
		}
		// Error may be ignored here. The error has already been checked
		// during transaction acceptance is the transaction pool.
		//
		// We use the eip155 signer regardless of the current hf.
		from, _ := types.Sender(env.signer, tx)

		// Start executing the transaction
		// jh -- tx:transaction hash;
		// jh -- common.Hash:block hash byte 数组；
		// jh -- env.tcount: current traction total(index)
		env.state.Prepare(tx.Hash(), common.Hash{}, env.localCount)

		// JiangHan: 开始执行交易，带入coinbase(主账户），tx（交易信息），bc(当前区块链），gp(用户提供的gaspool,用户扣gas)
		err := env.commitTransaction(tx, bc, coinbase, gp, update, lampHeight)

		switch err {
		case core.ErrGasLimitReached:
			// Pop the current out-of-gas transaction without shifting in the next from the account
			log.Trace("Gas limit exceeded for current block", "sender", from)
			txs.Pop()

		case core.ErrNonceTooLow:
			// New head notification data race between the transaction pool and miner, shift
			log.Trace("Skipping transaction with low nonce", "sender", from, "nonce", tx.Nonce())
			txs.Shift()

		case core.ErrNonceTooHigh:
			// Reorg notification data race between the transaction pool and miner, skip account =
			log.Trace("Skipping account with hight nonce", "sender", from, "nonce", tx.Nonce())
			txs.Pop()

		case nil:
			// Everything ok, collect the logs and shift in the next transaction from the same account
			if tx.IsLocalTx(lampHeight, coinbase) {
				env.localCount++
			} else if tx.IsOutputTx(lampHeight, coinbase) {
				env.outputCount++
			}
			txs.Shift()

		default:
			// Strange error, discard the transaction and get the next in line (note, the
			// nonce-too-high clause will prevent us from executing in vain).
			log.Debug("Transaction failed, account skipped", "hash", tx.Hash(), "err", err)
			txs.Shift()
		}
	}

	/*
		if len(coalescedLogs) > 0 || env.tcount > 0 {
			// make a copy, the state caches the logs and these logs get "upgraded" from pending to mined
			// logs by filling in the block hash when the block was mined by the local miner. This can
			// cause a race condition if a log was "upgraded" before the PendingLogsEvent is processed.
			cpy := make([]*types.Log, len(coalescedLogs))
			for i, l := range coalescedLogs {
				cpy[i] = new(types.Log)
				*cpy[i] = *l
			}
			go func(logs []*types.Log, tcount int) {
				if len(logs) > 0 {
					mux.Post(core.PendingLogsEvent{Logs: logs})
				}
				if tcount > 0 {
					mux.Post(core.PendingStateEvent{})
				}
			}(cpy, env.tcount)
		}
	*/

}

func (env *Work) commitInputTxs(batches types.ShardingTxBatches, eBase *common.Address) {
txBatch:
	for _, txBatch := range batches {
		toShardingID := txBatch.ToShardingID()
		env.state.UpdateStoreShardingHeight(toShardingID, txBatch.BlockHeight)
		env.state.UpdateStoreBatchNonce(toShardingID, txBatch.BatchNonce)

		// Check txBatch
		for _, tx := range txBatch.Txs {
			if success := core.ApplyInputTxs(env.state, tx, txBatch.LampNum, eBase); !success {
				continue txBatch
			}
		}
		env.inputTxs = append(env.inputTxs, txBatch)
		env.inputCount++
	}
}

func (env *Work) commitTransaction(tx *types.Transaction, bc *core.BlockChain, coinbase *common.Address, gp *core.GasPool, update bool, lampHeight uint64) error {
	// JiangHan: 执行交易前先拍个快照，发生错误就恢复快照内容还原
	snap := env.state.Snapshot()

	// JiangHan: （重点：交易执行点一）这里应该是 work 从其他用户节点收集交易请求，并执行它们
	receipt, _, err := core.ApplyTransaction(env.config, bc, coinbase, gp, env.state, env.header, tx, &env.header.GasUsed, update, lampHeight)
	if err != nil {
		// 有错误发生，还原快照
		env.state.RevertToSnapshot(snap)
		return err
	}
	env.txs = append(env.txs, tx)
	env.receipts = append(env.receipts, receipt)

	return nil
}
