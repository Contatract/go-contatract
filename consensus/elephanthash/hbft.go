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
	"time"

	"github.com/contatract/go-contatract/bft/nodeHbft"
	"github.com/contatract/go-contatract/common"
	types "github.com/contatract/go-contatract/core/types_elephant"
	"github.com/contatract/go-contatract/log"
	"github.com/contatract/go-contatract/p2p/discover"
)

type NodeHbftServer struct {
	Address common.Address
	Node    *discover.Node
}

func doHbftWork(block *types.Block, hbftNode *nodeHbft.Node) bool {
	if sealerAddr, work := itsTimeToDoHbftWork(block, hbftNode); work {
		log.Info("【*】Start the process of sealing a new block", "number", block.NumberU64(), "hashNoBft", block.HashNoBft())
		hbftNode.GetRequest(sealerAddr.String(), block)
		return true
	} else {
		return false
	}
}

func itsTimeToDoHbftWork(block *types.Block, hbftNode *nodeHbft.Node) (common.Address, bool) {
	sealers, _ := hbftNode.EleBackend.GetCurRealSealers()
	count := len(sealers)
	if count < nodeHbft.NodeServerMinCountHbft {
		log.Info("insufficient node server", "count", count)
		time.Sleep(nodeHbft.BlockMinPeriodHbft)
		return common.Address{}, false
	}

	sealerAddr := hbftNode.GetCurrentSealer(sealers, true)
	if common.EmptyAddress(sealerAddr) {
		return common.Address{}, false
	}

	coinbase := block.Header().Coinbase
	if !sealerAddr.Equal(coinbase) {
		log.Trace("waiting to be a sealer", "now sealer address", sealerAddr.String(), "my address", coinbase.String())
		return common.Address{}, false
	}

	return sealerAddr, true
}
