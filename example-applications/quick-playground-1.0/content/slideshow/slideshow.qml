/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7

Rectangle {
    id: slideShow

    function initialize() { }

    color: "black"
    anchors.fill: parent

    // This model information might be better in XML file.
    ListModel {
        id: slidesModel
        ListElement {
            image: "../fancypicker/qtqp_back1.jpg"
            text1: "The Qt Quick Playground demonstrates the features of the Qt Quick"
            text2: "Watch specially for the animations and effects"
            text3: "Check also the QML source code of each demo"
            logo: ""
        }
        ListElement {
            image: "../fancypicker/qtqp_back2.jpg"
            text1: "Most of the code is QML"
            text2: "Some of the logic is made with Javascript"
            text3: "Added with some pieces of Qt"
            logo: ""
        }
        ListElement {
            image: "../fancypicker/qtqp_back3.jpg"
            text1: "Play around"
            text2: "Get to know what Qt Quick offers"
            text3: "Have fun with Qt Quick Playground!"
            logo: ""
        }
        ListElement {
            image: ""
            text1: ""
            text2: ""
            text3: ""
            logo: "Forum_Nokia_03_RGB_strap.gif"
        }
    }

    Component {
        id: delegate
        Item {
            id: slide

            property int fadeDuration: 2000
            property int textAnimationDuration: 2000
            property int textPixelSize: height / 15

            // the slide will cover whole screen
            width: slideShow.width + 1; height: slideShow.height

            Rectangle {
                anchors.fill: parent
                color: "white"

                Image {
                    id: background

                    source: image
                    anchors.fill: parent
                    fillMode: "Stretch"
                    clip: true

                    Text {
                        id: t1
                        Behavior on x  { NumberAnimation { duration: slide.textAnimationDuration; easing.type: "OutCubic" } }
                        x: 100
                        anchors.top: parent.top; anchors.topMargin: parent.height / 8
                        width: parent.width - 100
                        wrapMode: "WordWrap"
                        text: text1

                        color: "white"
                        font.bold: true
                        font.pixelSize: slide.textPixelSize
                        style: Text.Raised
                        Behavior on opacity { NumberAnimation { duration: slide.fadeDuration } }
                        opacity: 0
                    }

                    Text {
                        id: t2
                        Behavior on x  { NumberAnimation { duration: slide.textAnimationDuration; easing.type: "OutCubic" } }
                        x: 100
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 100
                        wrapMode: "WordWrap"
                        text: text2

                        color: "white"
                        font.bold: true
                        font.pixelSize: slide.textPixelSize
                        style: Text.Raised
                        Behavior on opacity { NumberAnimation { duration: slide.fadeDuration } }
                        opacity: 0
                    }

                    Text {
                        id: t3
                        Behavior on x  { NumberAnimation { duration: slide.textAnimationDuration; easing.type: "OutCubic"  } }
                        x: 100
                        anchors.bottom: parent.bottom; anchors.bottomMargin: parent.height / 8
                        width: parent.width - 100
                        wrapMode: "WordWrap"
                        text: text3

                        color: "white"
                        font.bold: true
                        font.pixelSize: slide.textPixelSize
                        style: Text.Raised
                        Behavior on opacity { NumberAnimation { duration: slide.fadeDuration } }
                        opacity: 0
                    }

                    Image {
                        id: l
                        source: logo
                        width: 367; height: 149
                        anchors.centerIn: parent
                    }

                    Timer {
                        id: timer

                        property int timerPosition: 0

                        interval: 2000
                        running: true
                        repeat: true
                        onTriggered: {
                            timer.timerPosition = timer.timerPosition + 1
                            if(timer.timerPosition == 1)      { t1.x = 50; t1.opacity = 1.0 }
                            else if(timer.timerPosition == 2) { t2.x = 50; t2.opacity = 2.0 }
                            else if(timer.timerPosition == 3) { t3.x = 50; t3.opacity = 3.0 }
                            else if(timer.timerPosition == 5) {
                                timer.running = false
                                t1.opacity = 0
                                t2.opacity = 0
                                t3.opacity = 0
                                if(view.currentIndex == 3) {
                                    // We will close the slide show when it is done
                                    sidePanel.closeClicked()
                                }
                                else {
                                    view.incrementCurrentIndex()  // Change the slide
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ListView {
        id: view
        anchors.fill: parent
        delegate: delegate
        model: slidesModel
        snapMode: "SnapToItem"
        keyNavigationWraps: true
        orientation: "Horizontal"
        cacheBuffer: 0
        interactive: false
    }
}
