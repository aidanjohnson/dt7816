/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7
import "SamegameCore"
import "SamegameCore/samegame.js" as Logic

Rectangle {
    id: screen

    function initialize() {
        Logic.startNewGame()
    }

    anchors.fill: parent

    SystemPalette { id: activePalette }

    Item {
        width: parent.width
        anchors { top: toolBar.bottom; bottom: parent.bottom }

        Image {
            id: background
            anchors.fill: parent
            source: "SamegameCore/pics/background.png"
            fillMode: Image.PreserveAspectCrop
        }

        Item {
            id: gameCanvas

            property int score: 0
            property int blockSize: 40

            z: 20; anchors.centerIn: parent
            width: parent.width - (parent.width % blockSize);
            height: parent.height - (parent.height % blockSize);

            MouseArea {
                anchors.fill: parent; onClicked: Logic.handleClick(mouse.x,mouse.y);
            }
        }
    }

    Dialog {
        id: dialog

        anchors {
            centerIn: parent
            horizontalCenterOffset: -10  // To allow the score show beside the dialog
        }
        z: 21
        onClicked: forceClose()
    }

    MouseArea {
        id: nameInputDialogExitMouseArea

        anchors.fill: parent
        enabled: nameInputDialog.opacity == 1
        onClicked: nameInputDialog.acceptText()

        Dialog {
            id: nameInputDialog

            property int initialWidth: 0


            function acceptText() {
                if (nameInputText.text != "")
                    Logic.saveHighScore(nameInputText.text);
                nameInputText.closeSoftwareInputPanel();
                nameInputDialog.forceClose();
            }


            function rejectText() {
                nameInputText.closeSoftwareInputPanel();
                nameInputDialog.forceClose();
            }


            function updateWidth() {
                var newWidth = nameInputText.width + dialogText.width + 40;
                if ( (newWidth > nameInputDialog.width && newWidth < screen.width)
                        || (nameInputDialog.width > nameInputDialog.initialWidth) )
                    nameInputDialog.width = newWidth;
            }

            anchors.centerIn: parent
            anchors.verticalCenterOffset: -40
            height: dialogText.height + okButton.height + 65
            z: 22;

            onClicked: {
                nameInputText.focus = true;
                nameInputText.openSoftwareInputPanel();
            }

            Behavior on width {
                NumberAnimation {}
                enabled: nameInputDialog.initialWidth != 0
            }

            Text {
                id: dialogText

                anchors {
                    top: parent.top; topMargin: 20
                    left: nameInputDialog.left; leftMargin: 20
                }

                text: "You won! Please enter your name: "
                color: "white"
            }

            Rectangle {
                anchors.fill: nameInputText
                opacity: 0.3
                color: "gray"
            }

            TextInput {
                id: nameInputText

                anchors {
                    top: dialogText.top
                    left: dialogText.right
                }

                focus: nameInputDialog.opacity == 1 ? true : false
                maximumLength: 20
                color: "white"

                onTextChanged: nameInputDialog.updateWidth()
                onAccepted: nameInputDialog.acceptText()
            }

            Row {
                anchors {
                    top: nameInputText.bottom; topMargin: 20
                    horizontalCenter: parent.horizontalCenter
                }

                spacing: 20

                Button {
                    id: okButton

                    height: 20
                    text: " OK "
                    onClicked: {
                        nameInputDialog.acceptText()
                    }
                }

                Button {
                    id: cancelButton

                    height: 20
                    text: " Cancel "
                    onClicked: nameInputDialog.rejectText()
                }
            }
        }
    }

    Rectangle {
        id: toolBar

        width: parent.width; height: 60
        color: activePalette.window
        anchors.top: screen.top

        Button {
            id: newGameButton
            anchors { left: parent.left; leftMargin: 3; verticalCenter: parent.verticalCenter }
            text: "New Game"
            onClicked: Logic.startNewGame()
        }

        Text {
            id: score
            anchors { right: parent.right; rightMargin: 80; verticalCenter: parent.verticalCenter }
            text: "Score: " + gameCanvas.score
            font.bold: true
            color: activePalette.windowText
        }
    }
}
