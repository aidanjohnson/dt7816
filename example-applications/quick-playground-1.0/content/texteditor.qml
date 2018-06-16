/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Item {
    id: textEditor

    property alias text: sourceText.text
    property alias codeTemplateModel: codeButtonList.model

    signal tryDemoClicked()
    signal backClicked()

    function flickToLine(line) {
        // Calculate the line position in pixels, we take 5 lines too up so that the selection
        // would be a little lower than the top of the window, it seems that the space between
        // rows is 3 pixels...
        var ypos = (line - 5) * (sourceText.font.pixelSize + 3)
        if(ypos < 0) { ypos = 0 }

        view.contentY = ypos
    }

    function getPosByLFCount(beginPos, lines) {
        var lineCount = 0

        if(lines <= 0) { return beginPos }

        for (var i = beginPos; i<sourceText.text.length; i++) {
            if(sourceText.text.charAt(i) == '\n') {
                lineCount++;
                if(lineCount == lines) { return i + 1}
            }
        }

        return i
    }

    function selectLine(lineNumber) {
        var lineBeginPos = -1
        var lineEndPos = -1

        lineBeginPos = getPosByLFCount(0, lineNumber - 1)
        lineEndPos = getPosByLFCount(lineBeginPos, 1) - 1

        flickToLine(lineNumber)

        editButton.pressed = true

        sourceText.select(lineBeginPos, lineEndPos)
        sourceText.cursorVisible = true
        sourceText.focus = true
    }

    function findCode(string) {
        // Finds given code in editor, flicks it to visible and selects then code right after the selection ending to \n

        var index = sourceText.text.indexOf(string)
        if(index == -1) {
            return  // string was not found
        }

        var beginPos = index + string.length
        var endPos = sourceText.text.indexOf('\n', beginPos)
        var lineCount = 0

        // Calculates the row count, this does not take account the word wrapping!!!
        for (var i=0; i<index; i++) {
            if(sourceText.text.charAt(i) == '\n') {
                lineCount++;
            }
        }

        flickToLine(lineCount)

        editButton.pressed = true

        sourceText.select(beginPos, endPos)
        sourceText.cursorVisible = true
        sourceText.focus = true
    }

    anchors.fill: parent
    clip: true

    Image {
        anchors.centerIn: parent
        source: "qtqp_codeview.png"
    }

    Flickable {
        id: view
        anchors.fill: parent
        anchors.rightMargin: parent.width / 4
        clip: true

        contentWidth: sourceText.width
        contentHeight: sourceText.height

        TextEdit {
            id: sourceText
            x: 7; y: 5; z:1
            width: view.width
            color: "white"
            wrapMode: "WrapAtWordBoundaryOrAnywhere"
            readOnly: true
            activeFocusOnPress: true
            selectedTextColor: color
            selectionColor: "#00000000"
            font.pixelSize: 13
        }
    }

    Rectangle {
        id: scrollBar
        anchors.right: view.right
        y: view.visibleArea.yPosition * view.height
        width: 6; height: view.visibleArea.heightRatio * view.height
        opacity: 0.5
    }

    Button {
        id: editButton

        property bool pressed: false

        anchors { top: parent.top; topMargin: 16; left: view.right; leftMargin: 16 }
        width: 100; height: 60
        opacity: 0.4

        onPressedChanged: {
            if (pressed) {
                sourceText.openSoftwareInputPanel();
            }
            else {
                sourceText.closeSoftwareInputPanel();
            }
        }

        Image { id: btn_pen; source: "btn_editbrowse_pen.png"; opacity: 0.4 }
        Image { id: btn_edit; source: "btn_editbrowse_edit.png"; anchors.left: btn_pen.right; opacity: 0.4 }
        Image { id: btn_slash; source: "btn_editbrowse_slash.png"; anchors.left: btn_edit.right; opacity: 0.4 }
        Image { id: btn_browse; source: "btn_editbrowse_browse.png"; anchors.left: btn_pen.right; anchors.top: btn_edit.bottom; opacity: 1.0 }

        MouseArea { anchors.fill: parent;  onClicked: { editButton.pressed = !editButton.pressed } }

        states: State {
            name: "EditMode"
            when: editButton.pressed
            PropertyChanges { target: btn_pen; opacity: 1.0 }
            PropertyChanges { target: btn_edit; opacity: 1.0 }
            PropertyChanges { target: btn_slash; opacity: 1.0 }
            PropertyChanges { target: btn_browse; opacity: 0.4 }
            PropertyChanges { target: view; interactive: false }
            PropertyChanges { target: sourceText; readOnly: false }
            PropertyChanges { target: sourceText; selectionColor: "blue" }
        }
    }

    Button {
        id: backButton
        anchors { top: parent.top; topMargin: 5; right: parent.right; rightMargin: 10 }
        source: "btn_mainmenu.png"
        onClicked: {
            sourceText.closeSoftwareInputPanel()
            backClicked(index)
        }
    }

    Button {
        id: startDemoButton
        anchors { top: backButton.bottom; topMargin: 15; right: parent.right; rightMargin: 10 }
        source: "btn_trydemo.png"
        onClicked: {
            sourceText.closeSoftwareInputPanel()
            tryDemoClicked()
        }
    }

    Component {
        id: drawer
        Item {
            width: codeButtonList.width
            height: 60
            CodeButton {
                width: parent.width - 5; height: parent.height - 10
                title: titleText
                search: searchText
            }
        }
    }

    ListView {
        id: codeButtonList

        anchors.top: startDemoButton.bottom; anchors.topMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        anchors.left: view.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10
        delegate: drawer
        orientation: "Vertical"
        interactive: false
    }
}
