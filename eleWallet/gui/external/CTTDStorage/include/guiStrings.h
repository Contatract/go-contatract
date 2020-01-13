#ifndef STRINGS_H
#define STRINGS_H

#include <map>
#include <vector>
#include <QObject>
#include <QString>

#define Bytes 1
#define KB_Bytes 1024
#define MB_Bytes (1024 * KB_Bytes)
#define GB_Bytes (1024 * MB_Bytes)

class GUIString : public QObject
{
    Q_OBJECT

public:
    static QString Spec;

    enum MsgDlgType {
        HintDlg = 0,
        SelectionDlg,
        WaitingDlg
    };
    Q_ENUMS(MsgDlgType)

    enum RpcCmds {
        SetDataDirCmd = 0,
        ShowAccountsCmd,
        GetAgentsInfoCmd,
        ExitExternGUICmd,
        NewAccountCmd,
        RemoteIPCmd,
        LoginAccountCmd,
        GetObjInfoCmd,
        BlizReadCmd,
        BlizReadFileCmd,
        BlizWriteCmd,
        BlizWriteFileCmd,
        CreateObjCmd,
        AddObjStorageCmd,
        GetCurAgentAddrCmd,
        GetSignedAgentInfoCmd,
        GetAccTBalanceCmd,
        GetAccBalanceCmd,
        GetTransactionCmd,
        SignAgentCmd,
        CancelAgentCmd,
        WaitTXCompleteCmd,
        GetSignatureCmd,
        CheckSignatureCmd,
        GetSharingCodeCmd,
        PayForSharedFileCmd,
        SendTransactionCmd,
        GetMailsCmd,
        SendMailCmd,
    };
    Q_ENUMS(RpcCmds)

    enum SysMessages {
        OkMsg,
        ErrorMsg,
        OpRspMsg,
        RateMsg,
        OpTimedOutMsg,
        NoAnyAccountMsg,
        FNameduplicatedMsg,
        ParseAgentsFailedMsg,
        SharingSpaceLabel,
        NeedMoreFlow,
    };
    Q_ENUMS(SysMessages)

    enum UIHints {
        IncorrecctPasswdHint,
        NotAvailableHint,
        WaitingForCompleteHint,
        WaitingTXCompleteHint,
        TXTimedoutHint,
        AgentApplyStartedHint,
        AgentCancelStartedHint,
        AgentInvalidHint,
        ConnFailedHint,
        GetAccTBalanceErrHint,
        GetAccBalanceErrHint,
        OperationFailedHint,
        TxReturnErrorHint,
        GetAgentDetailsErrHint,
        ParseAgentDetailsErrHint,
        CreateSpaceSuccessHint,
        CreateSpaceFailedHint,
        GetObjInfoErrHint,
        ParseObjErrHint,
        ReadMetaDataErrHint,
        ParseMetaErrHint,
        FileInfoNotFoundHint,
        NeedMoreFlowHint,
        DownloadFileFailedHint,
        NotEnoughSpaceToUpHint,
        WriteMetaDataErrHint,
        GenSharingCodeFailedHint,
        GetSignatureFailedHint,
        PayForSharingSuccHint,
        PayForSelfSharingHint,
        TxAmountExceededHint,
        TxSuccessfullySentHint,
        TxSentFailedHint,
        GetMailsErrorHint,
    };
    Q_ENUMS(UIHints)

    enum UIStatus {
        CreatingSpaceText,
        CreatingSpaceStatus,
        DownloadingStatus,
        UploadingStatus,
        TxSendedStatus,
        TxConfirmedStatus,
    };
    Q_ENUMS(UIStatus)

public:
    Q_INVOKABLE QString rpcCmds(RpcCmds cmd);

    Q_INVOKABLE QString sysMsgs(SysMessages msg);

    Q_INVOKABLE QString uiHints(UIHints hint, bool cn=true);

    Q_INVOKABLE QString uiStatus(UIStatus status, bool cn=true);

public:
    GUIString();
    ~GUIString();
    static GUIString* GetSingleton();
    size_t RPCCmdLength();

private:
    static GUIString* m_TheSingleton;
    std::map<RpcCmds, std::string> m_RPCCommands;
    std::map<SysMessages, std::string> m_SysMessages;
    std::map<UIHints, std::string> m_UIHintsCN;
    std::map<UIHints, std::string> m_UIHintsEN;
    std::map<UIStatus, std::string> m_UIStatusCN;
    std::map<UIStatus, std::string> m_UIStatusEN;
};


namespace CTTUi {

const QString spec = QString("/");
//const std::string unAuthAgentAddr = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

}

#endif // STRINGS_H
