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

package elephanthash

import (
	crand "crypto/rand"
	"math"
	"math/big"
	"math/rand"
	"sync"
	"time"

	"github.com/contatract/go-contatract/bft/nodeHbft"
	"github.com/contatract/go-contatract/common"
	"github.com/contatract/go-contatract/consensus"
	types "github.com/contatract/go-contatract/core/types_elephant"
	"github.com/contatract/go-contatract/log"
)

// Stages copied from hbft_imp.go
const (
	Idle       uint = iota // Node is created successfully, but the consensus process is not started yet.
	PreConfirm             // The `preConfirmMsg` is processed successfully. The node is ready to head to the Confirm stage.
	Confirm                // The `confirmMsg` is processed successfully. The node is ready to head to the next block processing.
)

type foundResult struct {
	Block  *types.Block
	Stages []*types.HBFTStageCompleted
}

// Seal implements consensus.Engine, attempting to find a nonce that satisfies
// the block's difficulty requirements.
func (elephanthash *Elephanthash) Seal(chain consensus.ChainReaderCtt, block *types.Block, stop <-chan struct{}) (*types.Block,
	[]*types.HBFTStageCompleted, error) {
	// If we're running a fake PoW, simply return a 0 nonce immediately
	if elephanthash.config.PowMode == ModeFake || elephanthash.config.PowMode == ModeFullFake {
		header := block.Header()
		header.MixDigest = common.Hash{}
		return block.WithSeal(header), nil, nil
	}
	// If we're running a shared PoW, delegate sealing to it
	if elephanthash.shared != nil {
		return elephanthash.shared.Seal(chain, block, stop)
	}
	// Create a runner and the multiple search threads it directs
	abort := make(chan struct{})
	found := make(chan foundResult)

	elephanthash.lock.Lock()
	if elephanthash.rand == nil {
		seed, err := crand.Int(crand.Reader, big.NewInt(math.MaxInt64))
		if err != nil {
			elephanthash.lock.Unlock()
			return nil, nil, err
		}
		elephanthash.rand = rand.New(rand.NewSource(seed.Int64()))
	}
	elephanthash.lock.Unlock()

	var parentTime uint64
	parent := chain.GetHeader(block.Header().ParentHash, block.NumberU64()-1)
	if parent != nil {
		parentTime = parent.Time.Uint64()
	}

	var pend sync.WaitGroup
	pend.Add(1)
	go func(parentTime uint64) {
		defer pend.Done()
		elephanthash.mine(block, abort, found, parentTime)
	}(parentTime)

	// Wait until sealing is terminated or a nonce is found
	var result foundResult
	select {
	case <-stop:
		// Outside abort, stop all miner threads
		close(abort)
	case result = <-found:
		// One of the threads found a block, abort all others
		close(abort)
	case <-elephanthash.update:
		// Thread count was changed on user request, restart
		close(abort)
		pend.Wait()
		return elephanthash.Seal(chain, block, stop)
	}
	// Wait for all miners to terminate and return the block
	pend.Wait()
	return result.Block, result.Stages, nil
}

// mine is the actual proof-of-work miner that searches for a nonce starting from
// seed that results in correct final block difficulty.
func (elephanthash *Elephanthash) mine(block *types.Block, abort chan struct{}, found chan foundResult, parentTime uint64) {
	// Extract some data from the header
	header := block.Header()
	logger := log.New("elephant BFT")
	log.Trace("【*】elephant sealing process start")

	ticker := time.NewTicker(nodeHbft.BlockSealingBeat)
	defer ticker.Stop()
	defer elephanthash.hbftNode.SetBusy(false)

seal:
	for {
		select {
		case <-abort:
			// BFT sealing terminated, update stats and abort
			break seal

		case <-ticker.C:
			var (
				ret        bool
				hbftStages []*types.HBFTStageCompleted
			)
			if !common.GetconsenusBft() {
				seconds := (rand.Int() % 3) + 3
				time.Sleep(time.Second * time.Duration(seconds))
				ret = true
				hbftStages = elephanthash.hbftNode.GetFakeStagesForTest(uint64(block.NumberU64()))
			} else if elephanthash.hbftNode != nil {
				// First check if the node should re-commit new sealing work for the BFT future block
				if future := elephanthash.hbftNode.EleBackend.BFTOldestFutureBlock(); future != nil {
					futureHashNoBft := future.HashNoBft()
					if futures := elephanthash.hbftNode.EleBackend.BFTFutureBlocks(); (len(futures) > 1 && futureHashNoBft.Equal(futures[1].ParentNoBftHash())) ||
						(!futureHashNoBft.Equal(block.ParentNoBftHash())) {
						if _, work := itsTimeToDoHbftWork(block, elephanthash.hbftNode); work {
							header.BftHash = types.EmptyHbftHash
							found <- foundResult{block.WithSeal(header), elephanthash.hbftNode.CurrentState.BuildCompletedStageChain()}
							break seal
						}
					}
				}

				ret = doHbftWork(block, elephanthash.hbftNode)
				if ret {
					ret = elephanthash.hbftNode.BlockSealedCompleted(block.Hash())
				} else {
					continue
				}
				if ret {
					hbftStages, ret = elephanthash.hbftNode.GetSealedBlockStages()
					if !ret {
						header.BftHash = common.Hash{} // represents that HBFT confirm stage failed
						found <- foundResult{block.WithSeal(header), elephanthash.hbftNode.CurrentState.BuildCompletedStageChain()}
						log.Warn("GetSealedBlockStages failed, can not find completed chain of two stages")
						break seal
					}
				} else {
					if elephanthash.hbftNode.GetCurrentStateStage() == PreConfirm {
						header.BftHash = types.EmptyHbftHash // represents that HBFT pre-confirm stage failed
					} else {
						header.BftHash = common.Hash{} // represents that HBFT confirm stage failed
					}
					found <- foundResult{block.WithSeal(header), elephanthash.hbftNode.CurrentState.BuildCompletedStageChain()}
					break seal
				}
			}

			if ret {
				block.SetBftStageComplete(hbftStages)
				header.BftHash = types.CalcBftHash(hbftStages)
				stageChain := make([]*types.HBFTStageCompleted, 0)
				if common.GetconsenusBft() {
					stageChain = elephanthash.hbftNode.CurrentState.BuildCompletedStageChain()
				}

				// Seal and return a block (if still needed)
				select {
				case found <- foundResult{block.WithSeal(header), stageChain}:
					logger.Trace("【*】Elephant block sealed and reported")
				case <-abort:
					logger.Trace("Elephant block sealing abort")
				}
				break seal
			}
			time.Sleep(nodeHbft.BlockMinPeriodHbft)
		}
	}

	// Datasets are unmapped in a finalizer. Ensure that the dataset stays live
	// during sealing so it's not unmapped while being read.
	// runtime.KeepAlive(dataset)
}
