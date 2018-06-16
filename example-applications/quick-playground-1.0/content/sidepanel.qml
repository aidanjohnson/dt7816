/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Image {
    id: sidePanel

    signal closeClicked
    signal codeEditorClicked

    Button {
        id: itemCloser
        anchors { top: parent.top; topMargin: 5; left: parent.left; leftMargin: 11 }
        source: "btn_mainmenu.png"

        onClicked: { closeClicked() }
    }

    Button {
        id: editorAccess

        anchors { top: itemCloser.bottom; topMargin: 15; horizontalCenter: parent.horizontalCenter }
        source: "btn_code.png"

        onClicked: { codeEditorClicked() }
    }
}
