import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import ctt.GUIString 1.0

Window {
    id: newAccWindow
    width: 360
    height: 210
    flags: Qt.FramelessWindowHint | Qt.Window
    modality: Qt.ApplicationModal
    title: qsTr("创建新账号 ")

    signal newAccCreated(string msg)

//    MouseArea {
//        anchors.fill: parent
//        acceptedButtons: Qt.LeftButton
//        property point clickPosSetting: "0, 0"
//        onPressed: {
//            clickPosSetting = Qt.point(mouse.x, mouse.y)
//        }
//        onPositionChanged: {
//            if (pressed) {
//                var delta = Qt.point(mouse.x-clickPosSetting.x, mouse.y-clickPosSetting.y)

//                newAccWindow.setX(newAccWindow.x+delta.x)
//                newAccWindow.setY(newAccWindow.y+delta.y)
//            }
//        }
//    }

    Rectangle {
        x: 0
        y: 0
        width: newAccWindow.width
        height: newAccWindow.height

        gradient: Gradient {
            GradientStop{ position: 0; color: "#B4F5C9" }
            GradientStop{ position: 1; color: "#79E89A" }
        }

        Button {
            id: closeNewAccBtn

            x: newAccWindow.width - 40
            y: 10
            width: 30
            height: 30

            background: Rectangle {
                implicitHeight: closeNewAccBtn.height
                implicitWidth:  closeNewAccBtn.width

                color: "transparent"  //transparent background

                BorderImage {
                    property string nomerPic: "qrc:/images/login/icon-close.png"
                    property string hoverPic: "qrc:/images/login/icon-close.png"
                    property string pressPic: "qrc:/images/login/icon-close.png"

                    anchors.fill: parent
                    source: closeNewAccBtn.hovered ? (closeNewAccBtn.pressed ? pressPic : hoverPic) : nomerPic;
                }
            }

            onClicked: newAccWindow.close()
        }

        Text {
            id: pwdTitle
            x: 75
            y: 20
            width: 210
            height: 38
            text: qsTr("请输入要创建账号的密码 ")
            fontSizeMode: Text.Fit
            font.italic: false
            style: Text.Sunken
            font.family: "Times New Roman"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 52
        }

        Image {
            x: 75
            y: 65
            width: 20
            height: 20
            source: "qrc:/images/login/icon-user.png"
            fillMode: Image.PreserveAspectFit
        }

        TextInput {
            id: newAccPwd1Edit
            x: 75
            y: 60
            width: 210
            height: 30
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            leftPadding: 40
            font.pixelSize: 14
            echoMode: TextInput.Password
        }

        Rectangle {
            color: "#747589"
            border.color: "transparent"
            x: 75
            y: 90
            width: 210
            height: 1
        }

        Image {
            x: 75
            y: 105
            width: 20
            height: 20
            source: "qrc:/images/login/icon-user.png"
            fillMode: Image.PreserveAspectFit
        }

        TextInput {
            id: newAccPwd2Edit
            x: 75
            y: 100
            width: 210
            height: 30
            text: ""
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            leftPadding: 40
            font.pixelSize: 14
            echoMode: TextInput.Password
        }

        Rectangle {
            color: "#747589"
            border.color: "transparent"
            x: 75
            y: 130
            width: 210
            height: 1
        }

        Button {
            id: accountNewBtn
            x: 60
            y: 150
            width: 80
            height: 30

            Text {
                text: qsTr("创建")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: accountNewBtn.hovered ? "white" : "black"
            }

            background: Rectangle {
                //radius: height/2
                color: "transparent"
                border.color:"#747589"
            }

            onClicked: newAccWithPwd()
        }

        Button {
            id: accountCancelBtn
            x: 220
            y: 150
            width: 80
            height: 30

            Text {
                text: qsTr("取消")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: accountCancelBtn.hovered ? "white" : "black"
            }

            background: Rectangle {
                //radius: height/2
                color: "transparent"
                border.color:"#747589"
            }

            onClicked: newAccWindow.close()
        }
    }

    function newAccWithPwd() {
        if (newAccPwd1Edit.text !== "" && newAccPwd1Edit.text === newAccPwd2Edit.text) {
            //var params = [newAccPwd1Edit.text]
            //var ret = rpcBackend.sendOperationCmdThread(GUIString.NewAccountCmd, params)
            newAccWindow.close()
            main.showMsgBox("waiting...", GUIString.WaitingDlg)
            var ret = main.newAccount(newAccPwd1Edit.text)
            if (ret !== "") {
                //newAccWindow.newAccCreated(ret)
                main.closeMsgBox()
                main.showMsgBox(ret, GUIString.HintDlg)
            } else {
                //TODO: main.showMsgBox(ret, GUIString.HintDlg)
            }
        } else {
            //TODO: main.showMsgBox(ret, GUIString.HintDlg)
        }
    }
}
