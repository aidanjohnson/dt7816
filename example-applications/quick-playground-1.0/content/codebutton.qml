/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Rectangle {
    id: codeButton

    property alias title: titleText.text
    property string search

    width: titleText.width + 10; height: 50
    opacity: 1
    color: "#999999"//"darkgray"
    radius: 6
    clip: true

    SequentialAnimation {
        id: pressAnimation
        PropertyAnimation { target: codeButton; properties: "scale"; to: 0.9; duration: 100 }
        ParallelAnimation {
            PropertyAnimation { target: codeButton; properties: "scale"; to: 1.0; duration: 100 }
            ScriptAction { script: textEditor.findCode(codeButton.search) }
        }
    }

    Text {
        id: titleText
        anchors.centerIn: parent
        text: codeButton.title
        color: "white"
        font.pixelSize: 13
    }

    MouseArea {
        anchors.fill: parent
        onClicked: { pressAnimation.start() }
    }
}
