/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Item {
    id: button

    property alias source: image.source

    signal clicked

    width: 50; height: 50

    Image {
        id: image

        anchors.centerIn: parent

        // the user must set the source property
        // source: "closemark.png"
        Behavior on opacity { NumberAnimation { duration: 2000; easing.type: "OutExpo" } }
        opacity: 0.5
    }

    SequentialAnimation {
        id: pressAnimation
        PropertyAnimation { target: button; properties: "scale"; to: 0.9; duration: 100 }
        ParallelAnimation {
            PropertyAnimation { target: button; properties: "scale"; to: 1.0; duration: 100 }
            ScriptAction { script: button.clicked() }
        }
    }

    MouseArea {
        anchors.fill: parent
        //hoverEnabled: true
        onClicked: { pressAnimation.start() }
        //onEntered:  { image.opacity = 1 }
        //onExited: { image.opacity = 0.5 }
    }
}
