#include <iostream>
#include <QApplication>
#include <QtQml>
#include "eleWalletBackRPC.h"
#include "mainLoop.h"
#include "uiConfig.h"

using namespace std;

#define DEFAULTRPCPORT 10309

bool InitConnection(EleWalletBackRPCCli* rpc)
{
    bool HasConnection = false;
    rpc->ConnectBackend(&HasConnection);
    clock_t now = clock();
    while(clock() - now < 1000)
    {
        if (HasConnection)
            break;
        QApplication::processEvents(QEventLoop::AllEvents, 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return HasConnection;
}

bool CheckDataDir(EleWalletBackRPCCli* rpc, UiConfig* cfg)
{
    QString qDataDir = cfg->Get(CTTUi::WalletSettings, CTTUi::DataDir).toString();
    if (qDataDir.isEmpty())
        return false;
    else
    {
        rpc->SendOperationCmd(GUIString::SetDataDirCmd, std::vector<QString>{qDataDir});
        return true;
    }
}

bool SetDataDir(EleWalletBackRPCCli* rpc, UiConfig* cfg)
{
    // Check if data directory has been set
    if (CheckDataDir(rpc, cfg))
        return true;

    QString dataDir = QCoreApplication::applicationDirPath() + "/data";
    QVariant value(dataDir);
    UiConfig().Set(CTTUi::WalletSettings, CTTUi::DataDir, value);
    rpc->SendOperationCmd(GUIString::SetDataDirCmd, std::vector<QString>{dataDir});

    // TODO : Set default data directory
//    m_DataDir = QCoreApplication::applicationDirPath().toStdString();

//    // Set data directory dialog
//    DataDirDlg dataDirDlg(&m_DataDir, m_LangENFlag, this);
//    dataDirDlg.setModal(true);
//    dataDirDlg.setFixedSize(dataDirDlgSize);
//    dataDirDlg.setWindowTitle(QString::fromStdString(m_StringsTable[Ui::dataDirDlgTitle]));
//    dataDirDlg.move((QApplication::desktop()->width() - dataDirDlg.width())/2,
//                    (QApplication::desktop()->height() - dataDirDlg.height())/2);

//    if (dataDirDlg.exec() == QDialog::Accepted)
//    {
//        QVariant value(QString::fromStdString(m_DataDir));
//        UiConfig().Set(Ui::WalletSettings, Ui::DataDir, value);
//        m_BackRPC.SendOperationCmd(m_Cmds[Ui::setDataDirCmd], vector<QString>{QString::fromStdString(m_DataDir)});
//    }
//    else
//    {
//        dataDirDlg.close();
//        return false;
//    }

    return true;
}

int main(int argc, char *argv[])
{
    quint16 port = DEFAULTRPCPORT;
    if (argc > 1)
        port = quint16(atoi(argv[1]));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("Contatract");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<GUIString>("ctt.GUIString", 1, 0, "GUIString");
    EleWalletBackRPCCli* rpcBack = new EleWalletBackRPCCli("127.0.0.1", port);

    if (!InitConnection(rpcBack))
        return -1;

    UiConfig* config = new UiConfig();
    if (!SetDataDir(rpcBack, config))
        return -1;

    // translate
    QTranslator translator;
//    translator.load(":/lang/en_US.qm");
//    //translator.load(":/zh_CN.qm");
//    app.installTranslator(&translator);
//    engine.retranslate();

    MainLoop* mainLoop = new MainLoop(rpcBack, &app, &engine, &translator);
    GUIString* guiStr = GUIString::GetSingleton();
    mainLoop->setLanguage("");

    engine.rootContext()->setContextProperty("uiConfig", config);
    engine.rootContext()->setContextProperty("main", mainLoop);
    engine.rootContext()->setContextProperty("rpcBackend", rpcBack);
    engine.rootContext()->setContextProperty("guiString", guiStr);
    engine.rootContext()->setContextProperty("agentInfo", mainLoop->GetAgentsModel());
    engine.rootContext()->setContextProperty("spaceListModel", mainLoop->GetSpaceListModel());
    engine.rootContext()->setContextProperty("fileListModel", mainLoop->GetFileListModel());
    engine.rootContext()->setContextProperty("mailListModel", mainLoop->GetMailListModel());

    engine.load(QUrl(QStringLiteral("qrc:/qml/login.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/agentConn.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/mainWindow.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/downloadDlg.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/popup.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *loginWin = engine.rootObjects().at(0);
    QObject *agentWin = engine.rootObjects().at(1);
    QObject *mainWin = engine.rootObjects().at(2);
    QObject *downloadDlg = engine.rootObjects().at(3);
    QObject *msgBox = engine.rootObjects().at(4);
    mainLoop->SetLoginWindow(loginWin);
    mainLoop->SetAgentWindow(agentWin);
    mainLoop->SetMainWindow(mainWin);
    mainLoop->SetDownloadDlg(downloadDlg);
    mainLoop->SetMsgDialog(msgBox);
    mainLoop->InitAccounts();
    rpcBack->SetMsgDialog(msgBox);

    int ret = app.exec();

    delete config;
    delete rpcBack;
    delete guiStr;
    return ret;
}
