#include "guiStrings.h"

GUIString* GUIString::m_TheSingleton;
QString GUIString::Spec = QString("/");

GUIString::GUIString()
{

}

GUIString::~GUIString()
{

}

GUIString* GUIString::GetSingleton()
{
    if (m_TheSingleton == nullptr)
    {
        m_TheSingleton = new GUIString();

        m_TheSingleton->m_RPCCommands =
        {
            {SetDataDirCmd, "gui_setDataDir"},
            {ShowAccountsCmd, "ele_accounts"},
            {GetAgentsInfoCmd, "gui_getAgentsInfo"},
            {ExitExternGUICmd, "gui_close"},
            {NewAccountCmd, "personal_newAccount"},
            {LoginAccountCmd, "gui_setAccountInUse"},
            {RemoteIPCmd, "gui_setRemoteIP"},
            {GetObjInfoCmd, "blizcs_getObjectsInfo"},
            {BlizReadCmd, "blizcs_read"},
            {BlizReadFileCmd, "blizcs_readFile"},
            {BlizWriteCmd, "blizcs_write"},
            {BlizWriteFileCmd, "blizcs_writeFile"},
            {CreateObjCmd, "blizcs_createObject"},
            {AddObjStorageCmd, "blizcs_addObjectStorage"},
            {GetCurAgentAddrCmd, "gui_getCurAgentAddress"},
            {GetSignedAgentInfoCmd, "elephant_getSignedCs"},
            {GetAccTBalanceCmd, "elephant_getTotalBalance"},
            {GetAccBalanceCmd, "elephant_getBalance"},
            {GetTransactionCmd, "elephant_checkTx"},
            {SignAgentCmd, "elephant_signCs"},
            {CancelAgentCmd, "elephant_cancelCs"},
            {WaitTXCompleteCmd, "gui_waitTx"},
            {GetSignatureCmd, "gui_getSignature"},
            {CheckSignatureCmd, "gui_checkSignature"},
            {GetSharingCodeCmd, "gui_getSharingCode"},
            {PayForSharedFileCmd, "gui_payForSharedFile"},
            {SendTransactionCmd, "elephant_sendTransaction"},
            {SendMailCmd, "elephant_sendMail"},
            {GetMailsCmd, "elephant_getMails"},
        };

        m_TheSingleton->m_SysMessages =
        {
            {OkMsg, "OK"},
            {ErrorMsg, "Error"},
            {OpRspMsg, "OpRsp"},
            {RateMsg, "Rate"},
            {OpTimedOutMsg, "Operation timed out"},
            {NoAnyAccountMsg, "No any accounts"},
            {FNameduplicatedMsg, "Duplicated file name"},
            {ParseAgentsFailedMsg, "Parse agent servers failed"},
            {SharingSpaceLabel, "Sharings"},
            {NeedMoreFlow, "Not enough flow"},
        };

        m_TheSingleton->m_UIHintsCN =
        {
            {IncorrecctPasswdHint, "密码错误"},
            {NotAvailableHint, "不可用 "},
            {WaitingForCompleteHint, "等待中‧‧‧"},
            {WaitingTXCompleteHint, "等待事务处理中‧‧‧"},
            {TXTimedoutHint, "事务处理超时, 请稍后再查看"},
            {AgentApplyStartedHint, "开始申请代理服务‧‧‧"},
            {AgentCancelStartedHint, "开始取消代理服务‧‧‧"},
            {AgentInvalidHint, "您似乎还没有购买目前所连接代理服务器的数据服务，需要先申请至少一个代理服务商的服务才能才能使用软件功能"},
            {ConnFailedHint, "连接到该代理商服务器失败，请重试"},
            {GetAccTBalanceErrHint, "获取总余额失败"},
            {GetAccBalanceErrHint, "获取余额失败"},
            {OperationFailedHint, "操作失败"},
            {TxReturnErrorHint, "操作返回的交易解析失败"},
            {GetAgentDetailsErrHint, "获取代理商服务器详细信息失败"},
            {ParseAgentDetailsErrHint, "解析代理商服务器详细信息失败"},
            {CreateSpaceSuccessHint, "创建空间已完成"},
            {CreateSpaceFailedHint, "创建空间失败"},
            {GetObjInfoErrHint, "获取存储空间信息失败"},
            {ParseObjErrHint, "存储空间解析失败"},
            {ReadMetaDataErrHint, "空间存储元数据获取失败"},
            {ParseMetaErrHint, "空间存储元数据解析失败"},
            {FileInfoNotFoundHint, "错误: 未找到所需要的文件相关信息, 尝试重新启动程序修复此问题"},
            {NeedMoreFlowHint, "对不起, 下载文件所需要的流量超出代理商服务的剩余流量, 请申请更多的代理商流量或变更代理商服务"},
            {DownloadFileFailedHint, "错误: 下载文件失败"},
            {NotEnoughSpaceToUpHint, "对不起, 该空间的大小不足以上传该文件"},
            {WriteMetaDataErrHint, "空间存储元数据上传写入失败"},
            {GenSharingCodeFailedHint, "生成分享码失败, 请检查填入的各项参数是否正确"},
            {GetSignatureFailedHint, "获取签名失败, 尝试重新启动程序修复此问题"},
            {PayForSharingSuccHint, "已经成功获取分享的文件, 请稍等片刻, 待事务处理完毕后可以在文件的空间列表中的\"来自分享\"分类里看到该文件以便下载, 但注意不要再重复执行获取分享的操作"},
            {PayForSelfSharingHint, "无法获取自己给自己的文件分享"},
            {TxAmountExceededHint, "转账数额大于余额, 无法发起转账"},
            {TxSuccessfullySentHint, "发起转账成功, 待事务处理完毕对方方可收到转账"},
            {TxSentFailedHint, "发起转账失败, 请稍后重试"},
            {GetMailsErrorHint, "获取邮件列表及内容失败, 请稍后重试"},
        };

        m_TheSingleton->m_UIHintsEN =
        {
            {WaitingTXCompleteHint, "‧‧‧"},
            {AgentInvalidHint, ""},
            {ConnFailedHint, ""},
            {GetAccTBalanceErrHint, ""},
            {GetAccBalanceErrHint, ""},
            {GetAgentDetailsErrHint, ""},
            {ParseAgentDetailsErrHint, ""},
            {GetObjInfoErrHint, ""},
            {ParseObjErrHint, ""},
            {ReadMetaDataErrHint, ""},
            {ParseMetaErrHint, ""},
            {FileInfoNotFoundHint, ""},
            {NeedMoreFlowHint, ""}
        };

        m_TheSingleton->m_UIStatusCN =
        {
            {CreatingSpaceText, "创建空间"},
            {CreatingSpaceStatus, "正在格式化新空间‧‧‧"},
            {DownloadingStatus, "正在下载文件‧‧‧"},
            {UploadingStatus, "正在上传文件‧‧‧"},
            {TxSendedStatus, "事务请求已发送, 等待处理"},
            {TxConfirmedStatus, "事务处理已完成"},
        };

        m_TheSingleton->m_UIStatusEN =
        {
            {CreatingSpaceText, ""},
            {CreatingSpaceStatus, ""},
            {DownloadingStatus, ""},
            {UploadingStatus, ""},
            {TxSendedStatus, ""},
            {TxConfirmedStatus, ""},
        };
    }

    return m_TheSingleton;
}

size_t GUIString::RPCCmdLength()
{
    return m_TheSingleton->m_RPCCommands.size();
}

QString GUIString::rpcCmds(RpcCmds cmd)
{
    return QString::fromStdString(m_TheSingleton->m_RPCCommands[cmd]);
}

QString GUIString::sysMsgs(SysMessages msg)
{
    return QString::fromStdString(m_TheSingleton->m_SysMessages[msg]);
}

QString GUIString::uiHints(UIHints hint, bool cn)
{
    if (cn)
        return QString::fromStdString(m_TheSingleton->m_UIHintsCN[hint]);
    else
        return QString::fromStdString(m_TheSingleton->m_UIHintsEN[hint]);
}

QString GUIString::uiStatus(UIStatus status, bool cn)
{
    if (cn)
        return QString::fromStdString(m_TheSingleton->m_UIStatusCN[status]);
    else
        return QString::fromStdString(m_TheSingleton->m_UIStatusEN[status]);
}
