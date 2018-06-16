/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Item {
    id: slider

    width: 50; height: 200

    // value is read/write.
    property real value: minimum
    property real maximum: 2
    property real minimum: 1
    property int yMax: slider.height - handle.height

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 10
        width: parent.width / 3; height: parent.height - 20

        border.color: "#AA444444"; border.width: 1; radius: 4

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#66343434" }
            GradientStop { position: 1.0; color: "#66000000" }
        }
    }

    Rectangle {
        id: handle

        anchors.horizontalCenter: parent.horizontalCenter
        y: (value - minimum) * slider.yMax / (maximum - minimum)
        width: slider.width - 3; height: 30

        radius: 3; smooth: true
        border.color: "#AA444444"; border.width: 1

        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightgray" }
            GradientStop { position: 1.0; color: "gray" }
        }

        MouseArea {
            anchors.fill: parent

            drag.target: parent
            drag.axis: "YAxis"; drag.minimumY: 0; drag.maximumY: slider.yMax

            onPositionChanged: { value = (maximum - minimum) * (handle.y) / slider.yMax + minimum; }
        }
    }
}
