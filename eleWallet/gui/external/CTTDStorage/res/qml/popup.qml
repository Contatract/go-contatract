import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3

Window {
    id: popupWindow
    visible: false
    flags: Qt.FramelessWindowHint
    modality: Qt.ApplicationModal
    title: qsTr("为陌云盘")

    property alias tipText: msg.text
    property Item parentItem : Rectangle {}

    width: 360
    height: 200

    Rectangle {
        id: titlePopupWindow
        color: "#BB000000"
        border.color: "transparent"
        x: 0
        y: 0
        width: msgHintDlg.width
        height: 40

        Image {
            x: 15
            y: 10
            width: 20
            height: 20
            source: "qrc:/images/main/icon-space.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: popupWindowTitle
            x: 50
            y: 5
            width: 360
            height: 30
            text: qsTr("为陌云盘")
            font.bold: true
            font.italic: false
            style: Text.Sunken
            font.family: "Times New Roman"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 14
            color: "lightsteelblue"
        }
    }

    Rectangle {
        id: msgHintDlg
        x: 0
        y: titlePopupWindow.height
        width: popupWindow.width
        height: popupWindow.height - titlePopupWindow.height
        border.color: "transparent"
        visible: false

        gradient: Gradient {
            GradientStop{ position: 0; color: "#B4F5C9" }
            GradientStop{ position: 1; color: "#79E89A" }
        }
//        modal: true
//        background: Rectangle {
//            gradient: Gradient {
//                GradientStop{ position: 0; color: "#B4F5C9" }
//                GradientStop{ position: 1; color: "#79E89A" }
//            }
//            anchors.fill: parent
//        }

//        header: Rectangle {
//            width: msgHintDlg.width
//            height: 48
//            border.color: "transparent"
//            color: "transparent"
//            Image {
//                width: 24
//                height: 24
//                anchors.centerIn: parent
//                source: "qrc:/images/popup/icon-send.png"
//            }
//        }

//        contentItem: Rectangle {
        Rectangle {
            x: 30
            y: 10
            width: msgHintDlg.width - 2*x
            height: 90
            border.color: "transparent"
            color: "transparent"
            Text {
                anchors.fill: parent
                anchors.centerIn: parent
                font.family: "Microsoft Yahei"
                color: "black"
                text: tipText
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft

            }
        }

        Button {
            //anchors.centerIn: parent
            x: popupWindow.width - width - height
            y: parent.height - 20 - height
            width: 80
            height: 30
            background: Rectangle {
                anchors.centerIn: parent
                width: 80
                height: 30
                radius: 5
                border.color: "#0f748b"
                border.width: 2
                color: "white"
                Text {
                    anchors.centerIn: parent
                    font.family: "Microsoft Yahei"
                    font.bold: true
                    color: "#0f748b"
                    text: qsTr("好的")
                }
            }
            onClicked: {
                popupWindow.hide();
            }
        }

//        footer: Rectangle {
//            width: msg.width
//            height: 50
//            border.color: "transparent"
//            color: "transparent"
//            Button {
//                anchors.centerIn: parent
//                width: 80
//                height: 30
//                background: Rectangle {
//                    anchors.centerIn: parent
//                    width: 80
//                    height: 30
//                    radius: 5
//                    border.color: "#0f748b"
//                    border.width: 2
//                    color: "white"
//                    Text {
//                        anchors.centerIn: parent
//                        font.family: "Microsoft Yahei"
//                        font.bold: true
//                        color: "#0f748b"
//                        text: qsTr("好的")
//                    }
//                }
//                onClicked: {
//                    popupWindow.hide();
//                }
//            }
//        }
    }

    Rectangle {
        id: waitingDlg
        x: 0
        y: titlePopupWindow.height
        width: popupWindow.width
        height: popupWindow.height - titlePopupWindow.height
        border.color: "transparent"
        visible: false

        gradient: Gradient {
            GradientStop{ position: 0; color: "#B4F5C9" }
            GradientStop{ position: 1; color: "#79E89A" }
        }
//        modal: true
//        background: Rectangle {
//            gradient: Gradient {
//                GradientStop{ position: 0; color: "#B4F5C9" }
//                GradientStop{ position: 1; color: "#79E89A" }
//            }
//            anchors.fill: parent
//        }

//        contentItem: Rectangle {
        Rectangle {
            x: 30
            y: 10
            width: waitingDlg.width - 2*x
            height: 90
            border.color: "transparent"
            color: "transparent"
            Text {
                anchors.fill: parent
                anchors.centerIn: parent
                font.family: "Microsoft Yahei"
                color: "black"
                text: tipText
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft

            }
        }
    }

    Text {
        id: msg
        x: 30
        y: titlePopupWindow.height
        width: titlePopupWindow.width - 2*x
        height: 90
        wrapMode: Text.WordWrap
        objectName: "content"
        visible: false
    }

    function openHintBox() {
        msgHintDlg.visible = true
        //msgHintDlg.open()
    }

    function openWaitingBox() {
        waitingDlg.visible = true
        //waitingDlg.open()
    }

    function closeWaitingBox() {
        waitingDlg.visible = false
        popupWindow.hide()
        //waitingDlg.close()
    }
}
