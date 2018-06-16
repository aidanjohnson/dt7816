/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Rectangle {
    id: container

    function initialize() {}

    color: "black"
    anchors.fill: parent

    Flickable {
        id: flickable

        anchors.fill: parent
        clip: true
        contentWidth: imageContainer.width; contentHeight: imageContainer.height

        Item {
            id: imageContainer

            width: Math.max(bigImage.width * bigImage.scale, flickable.width)
            height: Math.max(bigImage.height * bigImage.scale, flickable.height)

            Image {
                id: bigImage;

                scale: slider.value
                anchors.centerIn: parent
                smooth: !flickable.moving
                asynchronous: true
                onStatusChanged: { slider.minimum = Math.min(flickable.width / width, flickable.height / height) }
            }
        }
    }

    Text {
        id: imageName

        anchors { bottomMargin: 10; bottom: picker.top; horizontalCenter: container.horizontalCenter }
        color: "black"
        opacity: 0.8
        text: bigImage.source
        font.bold: true
        style: Text.Outline; styleColor: "white"
    }

    Slider {
        id: slider

        anchors.right: parent.right; anchors.rightMargin: 18
        anchors.top: parent.top; anchors.topMargin: 20
        anchors.bottom: hider.top; anchors.bottomMargin: 40

        Behavior on opacity { NumberAnimation { } }
        opacity: 0.8
        value: 1.2  // zoom a little when FancyPicker is opened to better demonstrate flicking
    }

    Rectangle {
        id: picker

        width: container.width; height: 100
        anchors.bottom: container.bottom

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#CC343434" }
            GradientStop { position: 1.0; color: "#66000000" }
        }

        ListModel {
            id: imageModel

            ListElement { name: "qtqp_back1.jpg" }
            ListElement { name: "qtqp_back2.jpg" }
            ListElement { name: "qtqp_back3.jpg" }
        }

        Component {
            id: imageDelegate

            Item {
                id: wrapper
                width: 80; height: 80
                Rectangle {
                    id: pickerItem

                    x: 10; y: 10
                    width: 80; height: 80
                    focus: true

                    opacity: 0.5
                    radius: 3
                    border.width: 2; border.color: "#AA444444"
                    color: "white"

                    Image {
                        id: image

                        x: 1; y: 1
                        width: pickerItem.width - 2; height: pickerItem.height - 2
                        source: name
                        asynchronous: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { view.currentIndex = index }
                    }

                    states: [
                        State {
                            name: "selected"
                            when: wrapper.ListView.isCurrentItem
                            PropertyChanges { target: image; opacity: 1 }
                            PropertyChanges { target: pickerItem; opacity: 1; border.color: "black" }
                            StateChangeScript { script: bigImage.source = image.source }
                        }
                    ]

                    transitions: Transition {
                        from: "*"
                        to: "selected"
                        reversible: true
                        NumberAnimation { duration: 500; easing.type: "OutCirc"; properties: "opacity,rotation" }
                    }
                }
            }
        }

        ListView {
            id: view

            anchors.fill: parent; anchors.rightMargin: 200
            model: imageModel
            delegate: imageDelegate
            spacing: 10
            orientation: "Horizontal"
        }

        states: State {
            name: "hidden"
            when: hider.hidden
            PropertyChanges { target: picker; opacity: 0.1; height: 0 }
            PropertyChanges { target: imageName; opacity: 0 }
        }

        transitions: Transition {
            from: "*"; to: "hidden"; reversible: true
            NumberAnimation { easing.type: "InOutQuad"; properties: "opacity, height"; duration: 1000 }
        }
    }

    Rectangle {
        id: hider

        property bool hidden: false

        width: 60; height: 60
        anchors { right: parent.right; bottom: parent.bottom; rightMargin: 4; bottomMargin: 13 }
        radius: 5
        border.color: "#AA444444"; border.width: 1

        Behavior on opacity { NumberAnimation { } }

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#AA999999" }
            GradientStop { position: 1.0; color: "#AA333333" }
        }

        Text {
            id: hiderText
            anchors.centerIn: parent
            text: "Hide"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: { hider.hidden = !hider.hidden }
        }

        states: State {
            name: "hidden"
            when: hider.hidden
            PropertyChanges { target: hiderText; text: "Show" }
            PropertyChanges { target: hider; opacity: 0.4 }
            PropertyChanges { target: slider; opacity: 0.4 }
        }
    }
}
