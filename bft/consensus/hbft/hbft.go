package hbft

const (
	SameViewPrimaryErr    = "BFT message from the same view"
	InvalidViewOrSeqIDErr = "the view ID or sequence ID of BFT message is not valid"
	InvalidParentHashErr  = "the hash of the parent completed stage is not valid"
	InvalidSignsCntErr    = "the signatures of the completed stage is not sufficient"
	NoSpecificBlockErr    = "the block in the stage is not received"
	InvalidNewBlockErr    = "new block that the BFT message contained is not valid"
	InvalidCompletedErr   = "the completed stage is not valid"
	ShouldNotHandleErr    = "the message we received should not be handled due to the stage of the node"
)
