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

// Package ethash implements the ethash proof-of-work consensus engine.
package elephanthash

import (
	"errors"
	"math/big"
	"math/rand"
	"sync"
	"time"
	"unsafe"

	//"github.com/contatract/go-contatract/log"
	"github.com/contatract/go-contatract/bft/nodeHbft"
	"github.com/contatract/go-contatract/consensus"
	"github.com/contatract/go-contatract/rpc"
	"github.com/rcrowley/go-metrics"
)

var ErrInvalidDumpMagic = errors.New("invalid dump magic")

var (
	// maxUint256 is a big integer representing 2^256-1
	maxUint256 = new(big.Int).Exp(big.NewInt(2), big.NewInt(256), big.NewInt(0))

	// sharedEthash is a full instance that can be shared between multiple users.
	sharedEthash = New(Config{ModeNormal, ""}, nil)

	// algorithmRevision is the data structure version used for file naming.
	algorithmRevision = 23

	// dumpMagic is a dataset dump header to sanity check a data dump.
	dumpMagic = []uint32{0xbaddcafe, 0xfee1dead}
)

// isLittleEndian returns whether the local system is running in little or big
// endian byte order.
func isLittleEndian() bool {
	n := uint32(0x01020304)
	return *(*byte)(unsafe.Pointer(&n)) == 0x04
}

// Mode defines the type and amount of PoW verification an ethash engine makes.
type Mode uint

const (
	ModeNormal Mode = iota
	ModeShared
	ModeTest
	ModeFake
	ModeFullFake
)

// Config are the configuration parameters of the ethash.
type Config struct {
	PowMode    Mode
	DatasetDir string
}

// Ethash is a consensus engine based on proot-of-work implementing the ethash
// algorithm.
type Elephanthash struct {
	config Config

	// Mining related fields
	rand *rand.Rand // Properly seeded random source for nonces
	//threads  int           // Number of threads to mine on if mining
	update   chan struct{} // Notification channel to update mining parameters
	hashrate metrics.Meter // Meter tracking the average hashrate

	// The fields below are hooks for testing
	shared    *Elephanthash // Shared PoW verifier to avoid cache regeneration
	fakeFail  uint64        // Block number which fails PoW check even in fake mode
	fakeDelay time.Duration // Time delay to sleep for before returning from verify

	lock sync.Mutex // Ensures thread safety for the in-memory caches and mining fields
	//hbftNode *nodePbft.Node
	hbftNode *nodeHbft.Node
}

// New creates a full sized ethash PoW scheme.
func New(config Config, pbftNode *nodeHbft.Node) *Elephanthash {
	return &Elephanthash{
		config:   config,
		update:   make(chan struct{}),
		hashrate: metrics.NewMeter(),
		hbftNode: pbftNode,
	}
}

// Threads returns the number of mining threads currently enabled. This doesn't
// necessarily mean that mining is running!
//func (elephanthash *Elephanthash) Threads() int {
//	elephanthash.lock.Lock()
//	defer elephanthash.lock.Unlock()
//
//	return elephanthash.threads
//}

// SetThreads updates the number of mining threads currently enabled. Calling
// this method does not start mining, only sets the thread count. If zero is
// specified, the miner will use all cores of the machine. Setting a thread
// count below zero is allowed and will cause the miner to idle, without any
// work being done.
//func (elephanthash *Elephanthash) SetThreads(threads int) {
//	elephanthash.lock.Lock()
//	defer elephanthash.lock.Unlock()
//
//	// If we're running a shared PoW, set the thread count on that instead
//	if elephanthash.shared != nil {
//		elephanthash.shared.SetThreads(threads)
//		return
//	}
//	// Update the threads and ping any running seal to pull in any changes
//	elephanthash.threads = threads
//	select {
//	case elephanthash.update <- struct{}{}:
//	default:
//	}
//}

// APIs implements consensus.Engine, returning the user facing RPC APIs. Currently
// that is empty.
func (elephanthash *Elephanthash) APIs(chain consensus.ChainReaderCtt) []rpc.API {
	return nil
}

// NewTester creates a small sized ethash PoW scheme useful only for testing
// purposes.
func NewTester() *Elephanthash {
	return New(Config{PowMode: ModeTest}, nil)
}
