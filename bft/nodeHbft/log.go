package nodeHbft

import (
	"fmt"

	"github.com/contatract/go-contatract/log"
)

func LogStage(info string, isDone bool) {
	if isDone {
		log.Info(fmt.Sprintf("【*】[STAGE-DONE] %s", info))
	} else {
		log.Info(fmt.Sprintf("【*】[STAGE-BEGIN] %s", info))
	}
}

func LogStageReset() {
	log.Info("【*】[STAGE-RESET] Current state reset")
}

func Trace(msg string, ctx ...interface{}) {
	log.Trace(msg, ctx...)
}

func Info(msg string, ctx ...interface{}) {
	log.Info(msg, ctx...)
}

func Warn(msg string, ctx ...interface{}) {
	log.Warn(msg, ctx...)
}

func Error(msg string, ctx ...interface{}) {
	log.Error(msg, ctx...)
}

func HBFTDebugInfo(msg string) {
	//log.Info("===HBFT Debug===%s", msg)
}
