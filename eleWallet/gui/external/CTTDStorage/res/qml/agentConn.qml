import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.10
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import ctt.GUIString 1.0

Window {
    id: agentConnWindow
    width: 640
    height: 400
    flags: Qt.FramelessWindowHint | Qt.Window
    modality: Qt.ApplicationModal
    visible: false
    title: qsTr("代理商服务器")

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

//                agentConnWindow.setX(agentConnWindow.x+delta.x)
//                agentConnWindow.setY(agentConnWindow.y+delta.y)
//            }
//        }
//    }

    Rectangle {
        x: 0
        y: 0
        width: agentConnWindow.width
        height: agentConnWindow.height

        gradient: Gradient {
            GradientStop{ position: 0; color: "#B4F5C9" }
            GradientStop{ position: 1; color: "#79E89A" }
        }

        Text {
            id: agentSelTitle
            x: 200 - (main.getLanguage() === "EN" ? 30 : 0)
            y: 20
            width: 240 + (main.getLanguage() === "EN" ? 60 : 0)
            height: 40
            text: qsTr(" 代理商服务器查询和操作 ")
            fontSizeMode: Text.Fit
            font.bold: true
            font.italic: false
            style: Text.Sunken
            font.family: "Times New Roman"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 48
        }

        Button {
            id: agentQuitBtn

            x: agentConnWindow.width - 40
            y: 10
            width: 30
            height: 30

            background: Rectangle {
                implicitHeight: agentQuitBtn.height
                implicitWidth:  agentQuitBtn.width

                color: "transparent"  //transparent background

                BorderImage {
                    property string nomerPic: "qrc:/images/login/icon-close.png"
                    property string hoverPic: "qrc:/images/login/icon-close.png"
                    property string pressPic: "qrc:/images/login/icon-close.png"

                    anchors.fill: parent
                    source: agentQuitBtn.hovered ? (agentQuitBtn.pressed ? pressPic : hoverPic) : nomerPic;
                }
            }

            onClicked: {
                if (main.mainShowed) {
                    agentConnWindow.hide()
                } else {
                    quitProgram()
                }
            }
        }

        Text {
            id: agentSelHint
            x: 50
            y: 55
            width: 540
            height: 40
            text: qsTr("我们在使用为陌云盘的时候需要通过代理服务器来访问链端上的数据，并让其帮我们完成文件及其数据的检索和缓存，以便我们能够快速访问和下载")
            wrapMode: Text.WordWrap
            fontSizeMode: Text.FixedSize
            font.bold: false
            font.italic: false
            style: Text.Sunken
            //font.family: "Microsoft Yahei"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 13
        }

        Rectangle {
            color: "#747589"
            border.color: "transparent"
            x: 0
            y: 100
            width: 640
            height: 1
        }

        Rectangle {
            color: "#747589"
            border.color: "transparent"
            x: 239
            y: 100
            width: 1
            height: 300
        }

        Rectangle {
            id: agentInfoArea
            x: 25
            y: 110
            width: 190
            height: 235
            color: "transparent"

            Column {
                Row {
                    Text {
                        text: qsTr("服务器账号")
                        font.pointSize: 12
                        height: 25
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        id: agentServiceState
                        text: setAgentServiceState()
                        font.pointSize: 12
                        height: 25
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Text {
                    id: agentServAccount
                    text: ""
                    font.pointSize: 11
                    width: 215
                    height: 25
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    leftPadding: 10
                }

                Text {
                    text: qsTr("付费方式: ")
                    font.pointSize: 12
                    height: 25
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                }

                Row {
                    leftPadding: 10
                    CheckBox {
                        id: paymentTimeCheckBox
                        width: 100
                        height: 30
                        text: qsTr("按时间")
                        font.pointSize: 11
                        display: AbstractButton.TextBesideIcon
                        enabled: canApplyForService()
                        //checkState: main.getAutoConnectAgentServ() !== "" ? Qt.Checked : Qt.Unchecked
                        onClicked: {
                            if (paymentTimeCheckBox.checkState === Qt.Checked) {
                                paymentFlowCheckBox.checked = false
                            } else {
                                paymentFlowCheckBox.checked = true
                            }
                        }
                    }

                    CheckBox {
                        id: paymentFlowCheckBox
                        width: 100
                        height: 30
                        text: qsTr("按流量")
                        font.pointSize: 11
                        display: AbstractButton.TextBesideIcon
                        enabled: canApplyForService()
                        //checkState: main.getAutoConnectAgentServ() !== "" ? Qt.Checked : Qt.Unchecked
                        onClicked: {
                            if (paymentFlowCheckBox.checkState === Qt.Checked) {
                                paymentTimeCheckBox.checked = false
                            } else {
                                paymentTimeCheckBox.checked = true
                            }
                        }
                    }
                }

                Text {
                    text: qsTr("服务起止时间: ")
                    font.pointSize: 12
                    height: 25
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                }

                Row {
                    Text {
                        text: qsTr("从: ")
                        font.pointSize: 11
                        height: 25
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        leftPadding: 10
                    }

                    Text {
                        id: agentServiceTimeStart
                        visible: false
                        font.pointSize: 11
                        height: agentServiceTimeStartBox.height
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                    }

                    Rectangle {
                        id: agentServiceTimeStartBox
                        visible: canApplyForService()
                        width: 100
                        height: 25
                        color: "transparent"
                        border.color: "#747589" //canApplyForService() ? "#747589" : "transparent"
                        Row {
                            Text {
                                font.pointSize: 11; text: " "; height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextInput {
                                id: agentServiceTimeStart1
                                font.pointSize: 11
                                width: (agentServiceTimeStartBox.width-10) / 10 * 4
                                height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                validator: IntValidator { bottom: 2019; top: 9999 }
                                //enabled: canApplyForService()
                            }
                            Text {
                                font.pointSize: 11; text: "-"; height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextInput {
                                id: agentServiceTimeStart2
                                font.pointSize: 11
                                width: (agentServiceTimeStartBox.width-10) / 10 * 2
                                height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                validator: IntValidator { bottom: 0; top: 12 }
                                //enabled: canApplyForService()
                            }
                            Text {
                                font.pointSize: 11; text: "-"; height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextInput {
                                id: agentServiceTimeStart3
                                font.pointSize: 11
                                width: (agentServiceTimeStartBox.width-10) / 10 * 2
                                height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                validator: IntValidator { bottom: 0; top: 12 }
                                //enabled: canApplyForService()
                            }
                            Text {
                                font.pointSize: 11; text: " "; height: agentServiceTimeStartBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }

                Row {
                    Text {
                        text: qsTr("到: ")
                        font.pointSize: 11
                        height: 25
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        leftPadding: 10
                    }

                    Text {
                        id: agentServiceTimeStop
                        visible: false
                        font.pointSize: 11
                        height: agentServiceTimeStartBox.height
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                    }

                    Rectangle {
                        id: agentServiceTimeStopBox
                        visible: canApplyForService()
                        width: 100
                        height: 25
                        color: "transparent"
                        border.color: "#747589" //canApplyForService() ? "#747589" : "transparent"
                        Row {
                            Text {
                                font.pointSize: 11; text: " "; height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextInput {
                                id: agentServiceTimeStop1
                                font.pointSize: 11
                                width: (agentServiceTimeStopBox.width-10) / 10 * 4
                                height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                validator: IntValidator { bottom: 2019; top: 9999 }
                                //enabled: canApplyForService()
                            }
                            Text {
                                font.pointSize: 11; text: "-"; height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextInput {
                                id: agentServiceTimeStop2
                                font.pointSize: 11
                                width: (agentServiceTimeStopBox.width-10) / 10 * 2
                                height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                validator: IntValidator { bottom: 0; top: 12 }
                                //enabled: canApplyForService()
                            }
                            Text {
                                font.pointSize: 11; text: "-"; height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                            TextInput {
                                id: agentServiceTimeStop3
                                font.pointSize: 11
                                width: (agentServiceTimeStopBox.width-10) / 10 * 2
                                height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                validator: IntValidator { bottom: 0; top: 12 }
                                //enabled: canApplyForService()
                            }
                            Text {
                                font.pointSize: 11; text: " "; height: agentServiceTimeStopBox.height
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }

                Row {
                    Text {
                        id: agentServerFlowLabel
                        text: qsTr("服务流量总计: ")
                        font.pointSize: 12
                        height: 25
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                    }

                    Rectangle {
                        id: agentServiceFlowBox
                        width: 45
                        height: 25
                        color: "transparent"
                        border.color: canApplyForService() ? "#747589" : "transparent"
                        TextInput {
                            id: agentServiceFlow
                            text: "10"
                            font.pointSize: 12
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            width: parent.width
                            height: parent.height
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            enabled: canApplyForService()
                        }
                    }

//                    Text {
//                        id: agentServiceFlowUnit
//                        text: qsTr(" GB")
//                        font.pointSize: 12
//                        height: 25
//                        verticalAlignment: Text.AlignVCenter
//                        horizontalAlignment: Text.AlignLeft
//                    }
                }

                Row {
                    Text {
                        text: qsTr("服务流量剩余: ")
                        font.pointSize: 12
                        height: 25
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                    }

                    Text {
                        id: agentServiceFlowRemain
                        text: "8"
                        font.pointSize: 12
                        width: 30
                        height: 25
                        leftPadding: 5
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                    }

//                    Text {
//                        id: agentServiceFlowRemainUnit
//                        text: qsTr(" GB")
//                        font.pointSize: 12
//                        height: 25
//                        verticalAlignment: Text.AlignVCenter
//                        horizontalAlignment: Text.AlignLeft
//                    }
                }

            }
        }

        Button {
            id: applyForServBtn
            x: 25
            y: 358
            width: 80
            height: 30
            enabled: canApplyForService()

            Text {
                text: qsTr("申请服务")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: (applyForServBtn.pressed || (!applyForServBtn.enabled)) ? "#747589" : (applyForServBtn.hovered ? "white" : "black")
            }

            background: Rectangle {
                radius: height/2
                color: "transparent"
                border.color:"#747589"
            }

            onClicked: applyForAgentService()
        }

        Button {
            id: cancelServBtn
            x: 135
            y: 358
            width: 80
            height: 30
            enabled: canCancelService()

            Text {
                text: qsTr("取消服务")
                font.pointSize: 10
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: (cancelServBtn.pressed || !cancelServBtn.enabled) ? "#747589" : (cancelServBtn.hovered ? "white" : "black")
            }

            background: Rectangle {
                radius: height/2
                color: "transparent"
                border.color:"#747589"
            }

            onClicked: cancelAgentService()
        }

        ListModel {
            id: agentModelTest
            ListElement {
                ip: "127.0.0.1"
                price: "20/200"
                payment: "0"
            }
            ListElement {
                ip: "118.89.165.39"
                price: "20"
                payment: "1"
            }
            ListElement {
                ip: "212.129.144.237"
                price: "200"
                payment: "2"
            }
        }

        Rectangle {
            color: "#AA000000"
            border.color: "transparent"
            x: 245
            y: 105
            width: 390
            height: 240

            Rectangle {
                id: agentListTitle
                width: parent.width - 5 - scrollbar.width
                height: 25
                color: "#747589"
                Row {
                    Rectangle {
                        id: agentListTitle1
                        width: 130; height: 25
                        color: agentListTitle.color
                        Text {
                            verticalAlignment: Text.AlignVCenter
                            width: agentListTitle1.width
                            height: agentListTitle1.height
                            text: qsTr("  网络IP地址")
                            font.pointSize: 13
                        }
                        MouseArea { anchors.fill: parent; onClicked: { } }
                    }

                    Rectangle {
                        id: agentListTitle2
                        width: 100; height: 25
                        color: agentListTitle.color
                        Text {
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            width: agentListTitle2.width
                            height: agentListTitle2.height
                            text: qsTr(" 单价")
                            font.pointSize: 13
                        }
                        MouseArea { anchors.fill: parent; onClicked: { } }
                    }

                    Rectangle {
                        id: agentListTitle3
                        width: 140; height: 25
                        color: agentListTitle.color
                        Text {
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            width: agentListTitle3.width
                            height: agentListTitle3.height
                            text: qsTr("付费方式")
                            font.pointSize: 13
                        }
                        MouseArea { anchors.fill: parent; onClicked: { } }
                    }
                }
            }

            ListView {
                id: agentList
                x: 5
                y: 27
                width: parent.width - x - scrollbar.width - x
                height: parent.height - y - y
                model: agentInfo
                highlightFollowsCurrentItem: true
                highlightMoveDuration: 0
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                clip: true
                focus: true

                delegate: Row {
                    id: agentListRow
                    Rectangle {
                        width: ipAddressText.width
                        height: ipAddressText.height
                        color: "transparent"
                        Text {
                            id: ipAddressText; width: 130; height: 25
                            verticalAlignment: Text.AlignVCenter
                            text: " " + ip
                            font.pointSize: 12
                            color: agentListRow.ListView.isCurrentItem ? "black" : "lightsteelblue"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                agentListRow.ListView.view.currentIndex = index
                                onAgentSelect()
                            }
                        }
                    }

                    Rectangle {
                        width: priceText.width
                        height: priceText.height
                        color: "transparent"
                        Text {
                            id: priceText; width: 100; height: 25
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: price
                            font.pointSize: 12
                            color: agentListRow.ListView.isCurrentItem ? "black" : "lightsteelblue"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                agentListRow.ListView.view.currentIndex = index
                                onAgentSelect()
                            }
                        }
                    }

                    Rectangle {
                        width: paymentText.width
                        height: paymentText.height
                        color: "transparent"
                        Text {
                            id: paymentText; width: 140; height: 25
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: payment === "0" ? "时间(天)/流量(MB)" : (payment === "1" ? "时间(天)" : "流量(MB)")
                            font.pointSize: 12
                            color: agentListRow.ListView.isCurrentItem ? "black" : "lightsteelblue"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                agentListRow.ListView.view.currentIndex = index
                                onAgentSelect()
                            }
                        }
                    }
                }

                Component.onCompleted: {
                    showAgentInfo()
                }
            }

            Rectangle {
                id: scrollbar
                width: 6
                x: parent.width - width - 1;
                y: 1
                height: parent.height - 2
                radius: width/2
                clip: true

                Rectangle {
                    id: dragButton
                    x: 0
                    y: agentList.visibleArea.yPosition * scrollbar.height
                    width: parent.width
                    height: agentList.visibleArea.heightRatio * scrollbar.height;
                    color: "#818b81"
                    radius: width
                    clip: true

                    MouseArea {
                        id: mouseArea
                        anchors.fill: dragButton
                        drag.target: dragButton
                        drag.axis: Drag.YAxis
                        drag.minimumY: 0
                        drag.maximumY: scrollbar.height - dragButton.height

                        onMouseYChanged: {
                            agentList.contentY = dragButton.y / scrollbar.height * agentList.contentHeight
                        }
                    }
                }
            }
        }

        CheckBox {
            id: autoConnCheckBox
            x: 240
            y: 360
            width: 100
            height: 25
            text: qsTr("自动连接")
            font.pointSize: 10
            display: AbstractButton.TextBesideIcon
            checkState: main.getAutoConnectAgentServ() !== "" ? Qt.Checked : Qt.Unchecked
            onClicked: setAutoConnectAgent()
        }

        Button {
            id: agentConnBtn
            x: 345
            y: 358
            width: 80
            height: 30
            font.bold: true
            font.pointSize: 12
            enabled: !main.connectedServ

            Text {
                text: qsTr("连接")
                font.pointSize: 12
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: agentConnBtn.enabled ? (agentConnBtn.hovered ? "black" : "white") : "#747589"
            }

            background: Rectangle {
                radius: 20
                color: agentConnBtn.enabled ? (agentConnBtn.hovered ? "white" : "#747589") : "transparent"
                border.width: 1
                border.color: "#95A4A8"
            }

            onClicked: connectAgentServByList()
        }

        Button {
            id: agentDisconnBtn
            x: 445
            y: 358
            width: 80
            height: 30
            font.bold: true
            font.pointSize: 12

            Text {
                text: qsTr("断开")
                font.pointSize: 12
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: agentDisconnBtn.hovered ? "black" : "white"
            }

            background: Rectangle {
                radius: 20
                color: agentDisconnBtn.hovered ? "white" : "#747589"
                border.width: 1
                border.color: "#95A4A8"
            }

            //onClicked: login()
        }

        Button {
            id: agentRefreshBtn
            x: 545
            y: 358
            width: 80
            height: 30
            font.bold: true
            font.pointSize: 12

            Text {
                text: qsTr("刷新")
                font.pointSize: 12
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: agentRefreshBtn.hovered ? "black" : "white"
            }

            background: Rectangle {
                radius: 20
                color: agentRefreshBtn.hovered ? "white" : "#747589"
                border.width: 1
                border.color: "#95A4A8"
            }

            onClicked: refreshAgentServ()
        }

//        Component.onCompleted: {
//            if (!main.connectedServ && main.getAutoConnectAgentServ() !== "") {
//                connectAgentServ(main.getAutoConnectAgentServ())
//            }
//        }
    }

    Connections {
        target: main
        onServiceStateChanged: {
            showAgentInfo()
            enableElements()
        }
    }

    function enableElements() {
        applyForServBtn.enabled = canApplyForService()
        cancelServBtn.enabled = canCancelService()
        agentConnBtn.enabled = !main.connectedServ
    }

    function setPaymentDefaultCheckState() {
        if (main.getAgentAvailablePayment(agentList.currentIndex) === "0" ||
                main.getAgentAvailablePayment(agentList.currentIndex) === "1") {
            paymentTimeCheckBox.checkState = Qt.Checked
            paymentFlowCheckBox.checkState = Qt.Unchecked
        } else {
            paymentTimeCheckBox.checkState = Qt.Unchecked
            paymentFlowCheckBox.checkState = Qt.Checked
        }
    }

    function canApplyForService() {
        return ((!main.atService) && main.connectedServ)
    }

    function canCancelService() {
        return !((!main.connectedServ) || (!main.atService) || (agentList.currentIndex < 0))
    }

    function showAgentInfo() {
        if (agentList.currentIndex >= 0) {
            agentServAccount.text = main.getAgentAccount(agentList.currentIndex, true)
        }

        setAgentServiceState()
        setAgentServicePayment()
        setAgentServiceTimeLimit()
        setAgentServiceFlowInfo()
    }

    function setAgentServiceState() {
        if (!main.connectedServ) {
            return qsTr(":")
        }

        if (agentList.currentIndex >= 0 && main.getCurrAgentAccount() === main.getAgentAccount(agentList.currentIndex)) {
            if (main.currAgentPayment === guiString.uiHints(GUIString.WaitingTXCompleteHint)) {
                agentServiceState.text = qsTr("(等待交易完成‧‧‧):")
            } else {
                agentServiceState.text = main.atService ? qsTr("(服务中):") : qsTr("(未提供服务):")
            }
        } else {
            agentServiceState.text = qsTr("(未提供服务):")
        }
    }

    function setAgentServicePayment() {
        if (!main.connectedServ) {
            return
        }

        paymentTimeCheckBox.enabled = canApplyForService()
        paymentFlowCheckBox.enabled = canApplyForService()

        if (agentList.currentIndex >= 0 && main.getCurrAgentAccount() === main.getAgentAccount(agentList.currentIndex)) {
            if (main.currAgentPayment === "0") {
                paymentTimeCheckBox.checkState = Qt.Checked
                paymentFlowCheckBox.checkState = Qt.Unchecked
            } else if (main.currAgentPayment === "1") {
                paymentTimeCheckBox.checkState = Qt.Unchecked
                paymentFlowCheckBox.checkState = Qt.Checked
            } else {
                if (canApplyForService()) {
                    setPaymentDefaultCheckState()
                } else {
                    paymentTimeCheckBox.checkState = Qt.Unchecked
                    paymentFlowCheckBox.checkState = Qt.Unchecked
                }
            }
        } else if(agentList.currentIndex >= 0) {
            setPaymentDefaultCheckState()
            paymentTimeCheckBox.enabled = false
            paymentFlowCheckBox.enabled = false
        } else {
            paymentTimeCheckBox.checkState = Qt.Unchecked
            paymentFlowCheckBox.checkState = Qt.Unchecked
        }
    }

    function setAgentServiceTimeLimit() {
        if (!main.connectedServ) {
            agentServiceTimeStartBox.visible = false
            agentServiceTimeStart.visible = true
            agentServiceTimeStart.text = "N/A"

            agentServiceTimeStopBox.visible = false
            agentServiceTimeStop.visible = true
            agentServiceTimeStop.text = "N/A"
            return
        }

        if (agentList.currentIndex >= 0 && main.getCurrAgentAccount() === main.getAgentAccount(agentList.currentIndex) &&
                (!canApplyForService())) {
            agentServiceTimeStartBox.visible = false
            agentServiceTimeStart.visible = true
            agentServiceTimeStart.text = main.currAgentTStart

            agentServiceTimeStopBox.visible = false
            agentServiceTimeStop.visible = true
            agentServiceTimeStop.text = main.currAgentTStop
        } else if((agentList.currentIndex >= 0 && main.getCurrAgentAccount() === main.getAgentAccount(agentList.currentIndex) &&
                  canApplyForService()) || (agentList.currentIndex >= 0 && canApplyForService())) {
            agentServiceTimeStartBox.visible = true
            agentServiceTimeStart.visible = false
            agentServiceTimeStart.text = ""

            agentServiceTimeStopBox.visible = true
            agentServiceTimeStop.visible = false
            agentServiceTimeStop.text = ""
        }
    }

    function setAgentServiceFlowInfo() {
        if (!main.connectedServ) {
            agentServiceFlow.text = "N/A"
            agentServiceFlowRemain.text = "N/A"
            return
        }

        agentServiceFlowBox.border.color = canApplyForService() ? "#747589" : "transparent"
        agentServiceFlow.enabled = canApplyForService()

        if (agentList.currentIndex >= 0 && main.getCurrAgentAccount() === main.getAgentAccount(agentList.currentIndex) &&
                (!canApplyForService())) {
            agentServiceFlow.text = main.currAgentFlow
            agentServiceFlowRemain.text = main.currAgentFlowRemain
        } else if((agentList.currentIndex >= 0 && main.getCurrAgentAccount() === main.getAgentAccount(agentList.currentIndex) &&
                  canApplyForService()) || (agentList.currentIndex >= 0 && canApplyForService())) {
            agentServiceFlow.text = ""
            agentServiceFlowRemain.text = ""
        }
    }

    function setAutoConnectAgent() {
        if (autoConnCheckBox.checkState === Qt.Checked && agentList.currentIndex >= 0) {
            main.setAutoConnectAgentServ(main.getAgentIP(agentList.currentIndex))
        } else {
            main.unsetAutoConnectAgentServ()
        }
    }

    function onAgentSelect() {
        showAgentInfo()
    }

    function connectAgentServ(ipAddress) {
        var currentAgentIndex = agentList.currentIndex
        main.showMsgBox(qsTr("正在连接中, 请稍后..."), GUIString.WaitingDlg)
        var ret = main.connectAgentServ(ipAddress)
        agentList.currentIndex = currentAgentIndex
        main.closeMsgBox()

        if (ret !== guiString.sysMsgs(GUIString.OkMsg)) {
            main.showMsgBox(ret, GUIString.HintDlg)
        } else {
            console.log("Connected agent server and get service successfully")
            agentConnWindow.hide()
        }
        main.showMainWindow()

        if (main.atService) {
            main.showMsgBox(qsTr("正在获取文件列表, 请稍后..."), GUIString.WaitingDlg)
            ret = main.updateFileList()
            if (ret !== guiString.sysMsgs(GUIString.OkMsg)) {
                main.closeMsgBox()
                main.showMsgBox(ret, GUIString.HintDlg)
            } else {
                main.closeMsgBox()
            }
        } else {
            showAgentInfo()
            enableElements()
        }
    }

    function connectAgentServByList() {
        if (agentList.currentIndex >= 0) {
            setAutoConnectAgent()
            connectAgentServ(main.getAgentIP(agentList.currentIndex))
        }
    }

    function refreshAgentServ() {
        var getAgentInfoRet = main.getAgentInfo()
        if (getAgentInfoRet !== guiString.sysMsgs(GUIString.OkMsg)) {
            // TODO: show message box and refresh as well as disable login function
            console.log("get agent infomation failed, ", getAgentInfoRet)
        }

        showAgentInfo()
        //enableElements()
    }

    function applyForAgentService() {
        if (!canApplyForService() && agentList.currentIndex >= 0) {
            return;
        }

        //main.applyForAgentService(main.getAgentAccount(agentList.currentIndex))
        var ret = main.applyForAgentService(main.getAgentAccount(agentList.currentIndex))
        if (ret === guiString.sysMsgs(GUIString.OkMsg)) {
            main.showMsgBox(ret, GUIString.HintDlg)
        }
    }

    function cancelAgentService() {
        if (!canCancelService() && agentList.currentIndex >= 0) {
            return;
        }

        //main.cancelAgentService(main.getAgentAccount(agentList.currentIndex))
        var ret = main.cancelAgentService(main.getAgentAccount(agentList.currentIndex))
        if (ret !== guiString.sysMsgs(GUIString.OkMsg)) {
            main.showMsgBox(ret, GUIString.HintDlg)
        }
    }

    function quitProgram() {
        var params = []
        main.setDefaultAccount(accountList.currentText)
        rpcBackend.sendOperationCmdThread(GUIString.ExitExternGUICmd, params)
        Qt.quit()
    }
}
