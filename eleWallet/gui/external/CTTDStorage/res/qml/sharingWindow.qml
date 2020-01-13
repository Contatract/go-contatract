import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import ctt.GUIString 1.0

Window {
    id: sharingWindow
    width: 640
    height: 400
    flags: Qt.FramelessWindowHint | Qt.Window
    modality: Qt.ApplicationModal
    visible: false
    title: qsTr("分享文件")

    signal mailFileSharingCreated()

    property int selectedFileIdx: 0
    property int selectedSpaceIdx: 0
    property bool addAttachmentFlag: false
    property string mailReceiver: ""

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

//                sharingWindow.setX(sharingWindow.x+delta.x)
//                sharingWindow.setY(sharingWindow.y+delta.y)
//            }
//        }
//    }

    Rectangle {
        x: 0
        y: 0
        width: sharingWindow.width
        height: sharingWindow.height

        gradient: Gradient {
            GradientStop{ position: 0; color: "#B4F5C9" }
            GradientStop{ position: 1; color: "#79E89A" }
        }

        Rectangle {
            id: titleAreaSharingWin
            color: "#BB000000"
            border.color: "transparent"
            x: 0
            y: 0
            width: sharingWindow.width
            height: 40

            Button {
                id: closeSharingWindow

                x: sharingWindow.width - 35
                y: 5
                width: 25
                height: 25

                background: Rectangle {
                    implicitHeight: closeSharingWindow.height
                    implicitWidth:  closeSharingWindow.width

                    color: "transparent"  //transparent background

                    BorderImage {
                        property string nomerPic: "qrc:/images/login/icon-close.png"
                        property string hoverPic: "qrc:/images/login/icon-close.png"
                        property string pressPic: "qrc:/images/login/icon-close.png"

                        anchors.fill: parent
                        source: closeSharingWindow.hovered ? (closeSharingWindow.pressed ? pressPic : hoverPic) : nomerPic;
                    }
                }

                onClicked: sharingWindow.close()
            }

            Image {
                x: 15
                y: 10
                width: 20
                height: 20
                source: "qrc:/images/main/icon-space.png"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: downloadTitle
                x: 50
                y: 5
                width: 420
                height: 30
                text: qsTr("分享文件: ") + main.getFileNameByIndex(sharingWindow.selectedFileIdx)
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
            id: shareCategoryLine
            color: "#747589"
            border.color: "transparent"
            x: 0
            y: titleAreaSharingWin.height + 39
            width: sharingWindow.width
            height: 1
        }

        SwipeView {
            id: sharingSwipeView
            anchors.top: parent.top
            anchors.topMargin: shareCategoryLine.y + shareCategoryLine.height
            width: sharingWindow.width
            height: sharingWindow.height - titleAreaSharingWin.height - shareCategoryLine.y - shareCategoryLine.height
            currentIndex: 0 //headertabBar.currentIndex

            Page {
                id: shareToAccountPage
                background: Rectangle {
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    Gradient {
                        GradientStop{ position: 0; color: "#487A89" }
                        GradientStop{ position: 1; color: "#54DAB3" }
                    }
                }

                Text {
                    id: shareToWhomLabel
                    x: 50
                    y: 10
                    width: 140
                    height: 30
                    text: qsTr("分享的目标用户的账号: ")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 14
                }

                TextInput {
                    id: shareToWhomEdit
                    x: shareToWhomLabel.x + shareToWhomLabel.width
                    y: shareToWhomLabel.y
                    width: 360
                    height: 30
                    text: sharingWindow.mailReceiver
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    leftPadding: 12
                    font.pixelSize: 14
                }

                Rectangle {
                    color: "#747589"
                    border.color: "transparent"
                    x: shareToWhomLabel.x + shareToWhomLabel.width + 10
                    y: shareToWhomLabel.y + shareToWhomLabel.height
                    width: 360
                    height: 1
                }

                Text {
                    id: timeLimitToShareHintLabel
                    x: 50
                    y: shareToWhomLabel.y + 1.5 * shareToWhomLabel.height
                    width: 60
                    height: 30
                    text: qsTr("有效期: ")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 14
                }

                Rectangle {
                    id: timeLimitToShareBox
                    x: timeLimitToShareHintLabel.x + timeLimitToShareHintLabel.width + (main.getLanguage() === "EN" ? 60 : 0)
                    y: timeLimitToShareHintLabel.y
                    width: 400
                    height: 30
                    color: "transparent"

                    Row {
                        anchors.fill: parent
                        Rectangle {
                            id: sharingTimeStartBox
                            width: 100
                            height: 30
                            color: "transparent"
                            border.color: "#747589" //canApplyForService() ? "#747589" : "transparent"
                            Row {
                                Text {
                                    font.pointSize: 11; text: " "; height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: agentServiceTimeStart1
                                    font.pointSize: 12
                                    width: (sharingTimeStartBox.width-10) / 10 * 4
                                    height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                    validator: IntValidator { bottom: 2019; top: 9999 }
                                    //enabled: canApplyForService()
                                }
                                Text {
                                    font.pointSize: 12; text: "-"; height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: agentServiceTimeStart2
                                    font.pointSize: 12
                                    width: (sharingTimeStartBox.width-10) / 10 * 2
                                    height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                    validator: IntValidator { bottom: 0; top: 12 }
                                    //enabled: canApplyForService()
                                }
                                Text {
                                    font.pointSize: 12; text: "-"; height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: agentServiceTimeStart3
                                    font.pointSize: 12
                                    width: (sharingTimeStartBox.width-10) / 10 * 2
                                    height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                    validator: IntValidator { bottom: 0; top: 12 }
                                    //enabled: canApplyForService()
                                }
                                Text {
                                    font.pointSize: 12; text: " "; height: sharingTimeStartBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
                        Text {
                            text: qsTr(" 到 ")
                            font.pointSize: 11
                            height: 30
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                        Rectangle {
                            id: sharingTimeStopBox
                            width: 100
                            height: 30
                            color: "transparent"
                            border.color: "#747589" //canApplyForService() ? "#747589" : "transparent"
                            Row {
                                Text {
                                    font.pointSize: 11; text: " "; height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: agentServiceTimeStop1
                                    font.pointSize: 12
                                    width: (sharingTimeStopBox.width-10) / 10 * 4
                                    height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                    validator: IntValidator { bottom: 2019; top: 9999 }
                                    //enabled: canApplyForService()
                                }
                                Text {
                                    font.pointSize: 12; text: "-"; height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: agentServiceTimeStop2
                                    font.pointSize: 12
                                    width: (sharingTimeStopBox.width-10) / 10 * 2
                                    height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                    validator: IntValidator { bottom: 0; top: 12 }
                                    //enabled: canApplyForService()
                                }
                                Text {
                                    font.pointSize: 12; text: "-"; height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: agentServiceTimeStop3
                                    font.pointSize: 12
                                    width: (sharingTimeStopBox.width-10) / 10 * 2
                                    height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignLeft
                                    validator: IntValidator { bottom: 0; top: 12 }
                                    //enabled: canApplyForService()
                                }
                                Text {
                                    font.pointSize: 12; text: " "; height: sharingTimeStopBox.height
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
                    }
                }

                Text {
                    id: sharingPriceHintLabel
                    x: 50
                    y: timeLimitToShareBox.y + 1.5 * timeLimitToShareBox.height
                    width: 70
                    height: 30
                    text: qsTr("分享价格: ")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 14
                }

                TextInput {
                    id: sharingPriceEdit
                    x: sharingPriceHintLabel.x + sharingPriceHintLabel.width
                    y: sharingPriceHintLabel.y
                    width: 60
                    height: 30
                    text: ""
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    leftPadding: 4
                    font.pixelSize: 14
                }

                Rectangle {
                    color: "#747589"
                    border.color: "transparent"
                    x: sharingPriceHintLabel.x + sharingPriceHintLabel.width
                    y: sharingPriceHintLabel.y + sharingPriceHintLabel.height
                    width: 60
                    height: 1
                }

                Text {
                    id: sharingCodeHintLabel
                    x: 50
                    y: sharingPriceHintLabel.y + 1.5 * sharingPriceHintLabel.height
                    width: 60
                    height: 30
                    visible: (sharingCode.text !== "")
                    text: qsTr("分享码: ")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 14
                }

                Text {
                    id: sharingCode
                    x: 50
                    y: sharingCodeHintLabel.y + sharingCodeHintLabel.height - 5
                    width: sharingWindow.width - x - 30
                    height: 90
                    text: ""
                    wrapMode: Text.Wrap
                    font.pixelSize: 12
                    visible: !addAttachmentFlag
                }

                Button {
                    id: createSharingCode
                    x: 380
                    y: sharingWindow.height - shareCategoryLine.y - shareCategoryLine.height - 60
                    width: 100
                    height: 30
                    enabled: (sharingCode.text === "")

                    Text {
                        text: addAttachmentFlag ? qsTr("确定") : qsTr("创建分享")
                        font.pointSize: 10
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: (createSharingCode.enabled) ? (createSharingCode.pressed ? "#747589" : (createSharingCode.hovered ? "white" : "black")) : "#747589"
                    }

                    background: Rectangle {
                        color: "transparent"
                        border.color:"#747589"
                    }

                    onClicked: shareFileToAccount()
                }

                Button {
                    id: sharingCancel
                    x: createSharingCode.x + createSharingCode.width + 30
                    y: createSharingCode.y
                    width: 100
                    height: 30

                    Text {
                        text: addAttachmentFlag ? qsTr("取消") : ((sharingCode.text !== "") ? qsTr("关闭") : qsTr("取消分享"))
                        font.pointSize: 10
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: sharingCancel.pressed ? "#747589" : (sharingCancel.hovered ? "white" : "black")
                    }

                    background: Rectangle {
                        color: "transparent"
                        border.color:"#747589"
                    }

                    onClicked: sharingWindow.close()
                }

                Button {
                    id: copySharingCode
                    x: createSharingCode.x - createSharingCode.width - 30
                    y: createSharingCode.y
                    width: 100
                    height: 30
                    visible: (sharingCode.text !== "" && !addAttachmentFlag)
                    enabled: (sharingCode.text !== "" && !addAttachmentFlag)

                    Text {
                        text: qsTr("复制分享码")
                        font.pointSize: 10
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: (copySharingCode.enabled) ? (copySharingCode.pressed ? "#747589" : (copySharingCode.hovered ? "white" : "black")) : "#747589"
                    }

                    background: Rectangle {
                        color: "transparent"
                        border.color:"#747589"
                    }

                    onClicked: {
                        if (sharingCode !== "") {
                            main.copyToClipboard(sharingCode.text)
                        }
                    }
                }
            }

            Page {
                background: Rectangle {
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    Gradient {
                        GradientStop{ position: 0; color: "#487A89" }
                        GradientStop{ position: 1; color: "#54DAB3" }
                    }
                }

                Label {
                    text: qsTr("分享给公众(待实现)")
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    font.italic: true
                    color: "yellow"
                }
            }
        }
    }

    Connections {
        target: main
        onSharingCodeChanged: {
            sharingCode.text = main.sharingCode
        }
    }

    function shareFileToAccount() {
        if (shareToWhomEdit.text !== "" && sharingPriceEdit.text !== "" &&
                agentServiceTimeStart1.text != "" && agentServiceTimeStart2.text != "" &&
                agentServiceTimeStart3.text != "" && agentServiceTimeStop1.text != "" &&
                agentServiceTimeStop2.text != "" && agentServiceTimeStop3.text != "") {
            if (agentServiceTimeStart2.text.length == 1) {
                agentServiceTimeStart2.text = "0" + agentServiceTimeStart2.text
            }
            if (agentServiceTimeStart3.text.length == 1) {
                agentServiceTimeStart3.text = "0" + agentServiceTimeStart3.text
            }
            if (agentServiceTimeStop2.text.length == 1) {
                agentServiceTimeStop2.text = "0" + agentServiceTimeStop2.text
            }
            if (agentServiceTimeStop3.text.length == 1) {
                agentServiceTimeStop3.text = "0" + agentServiceTimeStop3.text
            }

            var timeStart = agentServiceTimeStart1.text + "-" + agentServiceTimeStart2.text + "-" +
                    agentServiceTimeStart3.text + " 00:00:00"
            var timeStop = agentServiceTimeStop1.text + "-" + agentServiceTimeStop2.text + "-" +
                    agentServiceTimeStop3.text + " 23:59:59"
            var ret = main.shareFileToAccount(sharingWindow.selectedSpaceIdx, sharingWindow.selectedFileIdx,
                                              shareToWhomEdit.text, timeStart, timeStop, sharingPriceEdit.text)
            if (addAttachmentFlag) {
                sharingWindow.close()
            }
            if (ret !== guiString.sysMsgs(GUIString.OkMsg)) {
                main.showMsgBox(ret, GUIString.HintDlg)
            } else {
                sharingWindow.mailFileSharingCreated()
            }
        }
    }
}
