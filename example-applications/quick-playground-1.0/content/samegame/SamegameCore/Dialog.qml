/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Rectangle {
    id: page

    property Item text: dialogText

    signal closed();
    signal clicked();

    function forceClose() {
        page.closed();
        page.opacity = 0;
    }

    function show(txt) {
        dialogText.text = txt;
        page.opacity = 1;
    }

    width: dialogText.width + 20; height: dialogText.height + 20
    color: "#373737"
    border.width: 1
    opacity: 0

    Behavior on opacity {
        NumberAnimation { duration: 1000 }
    }

    Text { id: dialogText; anchors.centerIn: parent; color: "white"; text: "Hello World!" }

    MouseArea {
        anchors.fill: parent
        onClicked: page.clicked()
    }
}
