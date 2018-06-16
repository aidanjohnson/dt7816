/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7
import Qt.labs.particles 1.0

Image {
    id: background

    function initialize() { anim.start() }

    anchors.fill: parent
    source: "./frostyfield800x480.jpg"
    fillMode: "Stretch"

    Text {
        id: text

        property real rotationSpeed: 0

        font.bold: true
        text: "Hello World!"
        style: Text.Raised
        color: "steelblue"
        font.pixelSize: if(background.width / 15 < 1) { 1 } else { background.width / 15 }
        anchors.centerIn: parent

        opacity: 0.8

        PropertyAnimation {
            id: anim
            target: text
            running: false
            property: "rotation"
            from: 0
            to: 360
            duration: 10000
        }

        MouseArea {
            anchors.fill: parent
            onClicked: { anim.start() }
        }
    }

    Particles {
        anchors.fill: parent
        anchors.margins: 30
        source: "snowflake.png"
        opacity: 0.5
        lifeSpan: 5000
        emissionRate: 10
        lifeSpanDeviation: 200
        count: 50
        angle: 70
        angleDeviation: 45
        velocity: 30
        velocityDeviation: 10
        ParticleMotionWander {
            xvariance: 30
            pace: 100
        }
    }
}
