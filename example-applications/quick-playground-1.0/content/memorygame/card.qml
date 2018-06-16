/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Item {
    id: card

    property int index              // used to calculate the card position
    property int hgap: 10           // horizontal gap between cards
    property int vgap: 10           // vertical gap between cards
    property int number             // contains the number of the card
    property bool turned
    property bool vanished: false

    signal cardSelected(int index)

    function calWidth() {
        return (game.width - hgap) / game.columns - hgap
    }

    function calHeight() {
        return (game.height - vgap) / game.rows - vgap
    }

    function calX() {
        var xcell = index % game.columns
        return hgap + xcell * (width + hgap)
    }

    function calY() {
        return vgap + Math.floor(index / game.columns) * (height + vgap)
    }

    function born() {
        startAnimation.start()
    }

    function vanish() {
        vanished = true
        card.z = 0
        vanishAnimation.start()
    }

    function die() {
        vanishAnimation.stop()
        dieAnimation.start()
    }

    x: hgap; y: vgap
    width: calWidth(); height: calHeight()

    Flipable {
        property int angle: 0

        id: flipable
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: { if(vanished == false) game.handleClick(index) }
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width / 2; origin.y: flipable.height / 2
            axis.x: 0; axis.y: 1; axis.z: 0     // rotate around y-axis
            angle: flipable.angle
        }

        front: Image { anchors.fill: parent; source: "card_back.png" }
        back: Image {
            anchors.fill: parent; source: "card_front.png"
            Text {
                text: number
                anchors.centerIn: parent
                font.bold: true; font.pixelSize: parent.width * 0.60
                color: "#FF202020"
            }
        }

        SequentialAnimation {
            id: startAnimation
            ParallelAnimation {
                PropertyAnimation { target: card; property: "x"; to: calX(); easing.type: "InOutCubic"; duration: 2000 }
                PropertyAnimation { target: card; property: "y"; to: calY(); easing.type: "InOutCubic"; duration: 2000 }
            }
        }

        SequentialAnimation {
            id: vanishAnimation
            PauseAnimation { duration: 500 }
            ParallelAnimation {
                PropertyAnimation { target: card; property: "rotation"; to: 900; easing.type: "InCubic"; duration: 3000 }
                PropertyAnimation { target: card; property: "x"; to: game.width * 2; easing.type: "InOutCubic"; duration: 4000 }
            }
        }

        SequentialAnimation {
            id: dieAnimation
            ParallelAnimation {
                PropertyAnimation { target: card; property: "rotation"; to: 0; easing.type: "InOutCubic"; duration: 2500 }
                PropertyAnimation { target: card; property: "x"; to: calX(); easing.type: "InOutCubic"; duration: 3000 }
            }
            ScriptAction { script: { turned = false } }
            PauseAnimation { duration: 1000 }
            ParallelAnimation {
                PropertyAnimation { target: card; property: "x"; to: hgap; easing.type: "InOutCubic"; duration: 2000 }
                PropertyAnimation { target: card; property: "y"; to: vgap; easing.type: "InOutCubic"; duration: 2000 }
            }
            ScriptAction { script: { game.initialize() } }
        }

        states: State {
            name: "back"
            when: turned
            PropertyChanges { target: flipable; angle: 180 }
        }

        transitions: Transition {
            NumberAnimation { property: "angle"; duration: 500 }
        }
    }
}
