import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import ctt.GUIString 1.0

Window {
    id: loginWindow
    visible: true
    width: 480
    height: 280
    flags: Qt.FramelessWindowHint | Qt.Window
    title: qsTr("为陌云盘-登陆")

    MouseArea { //为窗口添加鼠标事件
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0, 0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            if (mouse.x > 0 && mouse.y > 0)
            {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                var newX = loginWindow.x + delta.x
                var newY = loginWindow.y + delta.y
                if (newX < Screen.desktopAvailableWidth-loginWindow.width &&
                        newY < Screen.desktopAvailableHeight-loginWindow.height &&
                        newX > 0 && newY > 0)
                {
                    loginWindow.setX(newX)
                    loginWindow.setY(newY)
                }
            }
        }
    }

    Rectangle {
        x: 0
        y: 0
        width: loginWindow.width
        height: loginWindow.height

        gradient: Gradient {
            GradientStop{ position: 0; color: "#B4F5C9" }
            GradientStop{ position: 1; color: "#79E89A" }
        }

        Component.onCompleted: init()

        Button {
            id: loginQuitBtn

            x: loginWindow.width - 40
            y: 10
            width: 30
            height: 30

            background: Rectangle {
                implicitHeight: loginQuitBtn.height
                implicitWidth:  loginQuitBtn.width

                color: "transparent"  //transparent background

                BorderImage {
                    property string nomerPic: "qrc:/images/login/icon-close.png"
                    property string hoverPic: "qrc:/images/login/icon-close.png"
                    property string pressPic: "qrc:/images/login/icon-close.png"

                    anchors.fill: parent
                    source: loginQuitBtn.hovered ? (loginQuitBtn.pressed ? pressPic : hoverPic) : nomerPic;
                }
            }

            onClicked: quitProgram()
        }

        Button {
            id: langSelectionBtn

            x: loginWindow.width - 2*40 - 10
            y: 10
            width: 40
            height: 30

            background: Rectangle {
                implicitHeight: langSelectionBtn.height
                implicitWidth:  langSelectionBtn.width
                color: "transparent"
                border.color: langSelectionBtn.pressed ? "#747589" : (langSelectionBtn.hovered ? "lightsteelblue" : "transparent")
                radius: 2

                Text {
                    id: lang
                    text: main.getLanguage() === "CN" ? qsTr("EN") : qsTr("中文")
                    font.pointSize: 12
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            onClicked: {
                var langSet = ""
                if (lang.text === "中文") {
                    langSet = "CN"
                } else {
                    langSet = "EN"
                }
                main.setLanguage(langSet)
            }
        }

        Text {
            id: progTitle
            x: 90
            y: 30
            width: 300
            height: 40
            text: qsTr("为陌云盘")
            fontSizeMode: Text.Fit
            font.bold: true
            font.italic: false
            style: Text.Sunken
            font.family: "Times New Roman"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 72
        }

        Image {
            id: imageUserName
            x: 80
            y: 100
            width: 20
            height: 20
            source: "qrc:/images/login/icon-user.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: imagePassword
            x: 80
            y: 140
            width: 20
            height: 20
            source: "qrc:/images/login/icon-user.png"
            fillMode: Image.PreserveAspectFit
        }

        ComboBox {
            id: accountList
            x: 80
            y: 95
            width: 340
            height: 30
            font.pointSize: 10
            font.bold: true

            delegate: ItemDelegate {
                id: itemDlgt
                width: accountList.width
                height: 25

                contentItem: Text {
                    id: textItem
                    text: modelData
                    color: hovered ? "#54DAB3" : "black"
                    font: accountList.font
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    leftPadding: 10
                }

                background: Rectangle {
                    //radius: height/2
                    color: itemDlgt.hovered ? "#747589" : "white";
                    anchors.left: itemDlgt.left
                    anchors.leftMargin: 0
                    width: itemDlgt.width-2
                }

                //onPressed: console.log(itemDlgt.height+" "+rectDlgt.height)
            }

            //the list of elements and their style when the combobox is open
            popup: Popup {
                id: comboPopup
                y: accountList.height - 1
                width: accountList.width
                height: contentItem.implicitHeigh
                padding: 1

                contentItem: ListView {
                    id: listView
                    implicitHeight: contentHeight
                    model: accountList.popup.visible ? accountList.delegateModel : null

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                background: Rectangle {
                    //radius: accountList.height/2
                    border.width: 1
                    border.color:"#95A4A8"
                }
            }

            //the text in the combobox
            contentItem: Text {
                leftPadding: 30
                rightPadding: 0 //accountList.indicator.width + accountList.spacing

                text: accountList.displayText
                font: accountList.font
                color: "black"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: "transparent"
                border.color: "transparent"
                //radius: height/2
            }

            //model: [ "Banana", "Apple", "Coconut" ]
        }

        Rectangle {
            color: "#747589"
            border.color: "transparent"
            x: 80
            y: 125
            width: 320
            height: 1
        }

        TextInput {
            id: passwdEdit
            x: 100
            y: 135
            width: 300
            height: 30
            text: ""
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            leftPadding: 10
            font.pixelSize: 14
            echoMode: TextInput.Password
        }

        Rectangle {
            color: "#747589"
            border.color: "transparent"
            x: 80
            y: 165
            width: 320
            height: 1
        }

        Button {
            id: loginBtn
            x: 120
            y: 180
            width: 240
            height: 30
            font.bold: true
            font.pointSize: 12

            Text {
                text: qsTr("登  陆")
                font.pointSize: 12
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: loginBtn.hovered ? "black" : "white"
            }

            background: Rectangle {
                //radius: 20
                color: loginBtn.hovered ? "white" : "#747589"
                border.width: 1
                border.color: "#95A4A8"
            }

            onClicked: login()
        }

        Button {
            id: newAccountBtn
            x: 40
            y: 225
            width: 110
            height: 30

            Text {
                text: qsTr("建立新账号")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: newAccountBtn.hovered ? "white" : "black"
            }

            background: Rectangle {
                //radius: height/2
                color: "transparent"
                border.color: "#747589"
            }

            onClicked: newAccount()
        }

        Button {
            id: importAccountBtn
            x: 185
            y: 225
            width: 110
            height: 30

            Text {
                text: qsTr("导入新账号")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: importAccountBtn.hovered ? "white" : "black"
            }

            background: Rectangle {
                //radius: height/2
                color: "transparent"
                border.color: "#747589"
            }

            onClicked: fds.open()
        }

        Button {
            id: forgetPwdBtn
            x: 330
            y: 225
            width: 110
            height: 30

            Text {
                text: qsTr("忘记密码")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: forgetPwdBtn.hovered ? "white" : "black"
            }

            background: Rectangle {
                //radius: height/2
                color: "transparent"
                border.color: "#747589"
            }

            //onClicked: console.log("forget password")
        }
    }

    FileDialog {
        id: fds
        title: qsTr("选择要导入的账号文件")
        folder: shortcuts.desktop
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        //nameFilters: ["json文件 (*.json)"]
        onAccepted: {
            console.log("You chose: " + fds.fileUrl);
        }
    }

    Connections {
        target: main
        onAccountsChanged: {
            accountList.model = main.accounts;
            if (count >= 4) {
                comboPopup.height = 100
            }
        }
    }

    function init() {
        var getAgentInfoRet = main.getAgentInfo()
        if (getAgentInfoRet !== guiString.sysMsgs(GUIString.OkMsg)) {
            // TODO: show message box and refresh as well as disable login function
            console.log("Error: get agent infomation failed, ", getAgentInfoRet)
            //loginBtn.enabled = false
        }
    }

    function newAccount() {
        var page = Qt.createComponent("qrc:/qml/newAcc.qml");

        if (page.status === Component.Ready) {
            var newAccWin = page.createObject()
            newAccWin.newAccCreated.connect(setAccount)

            newAccWin.show();
        }
    }

    function setAccount(account) {
        //comboPopup.height = contentItem.implicitHeigh > 100 ? 100 : contentItem.implicitHeigh
    }

    function login() {
        var account = accountList.currentText
        if (account === "") {
            //TODO: dlg
            return
        }

        var passwd = passwdEdit.text
        if (passwd === "") {
            //TODO: dlg
            return
        }

        loginWindow.hide()
        if (!main.verifyPassword(account, passwd)) {
            //TODO: dlg
            loginWindow.show()
            return
        }

        if (!main.connectedServ && main.getAutoConnectAgentServ() !== "") {
            main.autoConnectAgent(main.getAutoConnectAgentServ())
            //connectAgentServ(main.getAutoConnectAgentServ())
        } else {
            main.showAgentConnWindow()
        }
    }

    function quitProgram() {
        var params = []
        main.setDefaultAccount(accountList.currentText)
        rpcBackend.sendOperationCmdThread(GUIString.ExitExternGUICmd, params)
        Qt.quit()
    }
}
