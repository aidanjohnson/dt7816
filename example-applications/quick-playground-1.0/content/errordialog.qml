/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Rectangle {
    id: page

    property Item text: dialogText
    property int lineNumber: 0

    signal closed

    function forceClose() {
        page.closed(lineNumber);
        page.opacity = 0;
    }

    function show(line, txt) {
        page.lineNumber = line
        dialogText.text = txt;
        page.opacity = 1;
    }

    width: dialogText.width + 20; height: dialogText.height + 20
    color: "white"
    border.width: 1
    opacity: 0

    Behavior on opacity { NumberAnimation { duration: 1000 } }

    Text { id: dialogText; anchors.centerIn: parent; text: "Error dialog" }

    MouseArea { anchors.fill: parent; onClicked: forceClose() }
}
