/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7
import QtWebKit 1.0

Item {
    id: container

    function initialize() {}

    anchors.fill: parent

    SystemPalette { id: activePalette }

    Rectangle {
        id: topbar

        z: 10
        width: parent.width; height: 60
        anchors.top: parent.top
        color: activePalette.window

        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightgray" }
            GradientStop { position: 1.0; color: "gray" }
        }

        Rectangle {
            id: textEdit

            anchors { left: parent.left; leftMargin: 10; right: goButton.left; rightMargin: 10; verticalCenter: parent.verticalCenter }
            height: 34
            color: "white"
            radius: 2

            TextInput {
                id: editUrl

                text: view.url
                anchors { left: parent.left; margins: 10; verticalCenter: parent.verticalCenter; right: parent.right }
                color: "black"
                font.pixelSize: parent.height - 13
            }
        }


        Rectangle {
            id: goButton

            width: 60; height: textEdit.height
            anchors { verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: 10 }
            border { width: 2; color: activePalette.dark }
            color: activePalette.button
            radius: 4

            gradient: Gradient {
                GradientStop { position: 0.0; color: "lightgray" }
                GradientStop { position: 1.0; color: "gray" }
            }

            Text {
                font { pixelSize: 12; bold: true }
                text: "Go"
                color: activePalette.buttonText
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.url = editUrl.text
                    pressAnimation.start()
                    editUrl.closeSoftwareInputPanel()
                }
            }

            SequentialAnimation {
                id: pressAnimation
                PropertyAnimation { target: goButton; properties: "scale"; to: 0.9; duration: 100 }
                PropertyAnimation { target: goButton; properties: "scale"; to: 1.0; duration: 100 }
            }
        }
    }

    Flickable {
        anchors { left: parent.left; right: parent.right; top: topbar.bottom; bottom: parent.bottom }
        contentWidth: view.width
        contentHeight: view.height


        WebView {
            id: view
            url: "http://maemo.org/"

            onLoadStarted: { progressIndicator.opacity = 0.7 }
            onLoadFinished: { progressIndicator.opacity = 0 }
            onLoadFailed: { progressIndicator.opacity = 0 }
        }
    }

    Rectangle {
        id: progressIndicator

        property real progress: view.progress

        anchors.bottom: parent.bottom; anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 20; height: 40
        color: "white"
        Behavior on opacity { NumberAnimation { duration: 700; easing.type: "InOutCubic" } }
        opacity: 0

        Rectangle {
            x: 4
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height - 8
            Behavior on width { NumberAnimation { duration: 200 } }
            width: progressIndicator.progress * progressIndicator.width - 8
            color: "black"
            radius: 3
        }

        Text {
            anchors.centerIn: parent
            text: parseInt(progressIndicator.progress * 100) + ' %'
            font.bold: true
            font.pixelSize: parent.height / 2
            style: Text.Raised
            color: "#DDDDDD"
        }
    }
}

