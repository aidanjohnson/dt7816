/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7
import "demoitemcore.js" as Core

Item {
    id: gridItem

    property string qmlFolder                                       // the path to demo qml
    property alias qmlCode: textEditor.text                         // the QML sourcecode
    property alias thumbnail: skin.source                           // the thumbnail of the demo
    property alias codeTemplateModel: textEditor.codeTemplateModel
    property int index                                              // index of demo item in demo chooser

    signal startSignal(int index)                                   // signaled when demo item is clicked
    signal codeEditorSignal(int index)                              // signaled when entering to code editor
    signal closeSignal(int index)                                   // signaled when exiting from demo and code editor

    function hide() { hideAnimation.start() }
    function show() { showAnimation.start() }

    state: "default"

    Rectangle {
        id: container

        width: parent.width; height: parent.height
        color: "#373737"; clip: true; radius: 10

        // mouse area which does nothing to prevent item under gridItem to receive clicks
        MouseArea { anchors.fill: parent }


        TextEditor {
            id: textEditor

            anchors.fill: parent
            onTryDemoClicked: { startSignal(index) }
            onBackClicked: { closeSignal(index) }
        }

        Image {
            id: skin

            width: parent.width; height: parent.height; smooth: true

            MouseArea {
                anchors.fill: parent
                onClicked: { startSignal(index) }
                onPressAndHold: { codeEditorSignal(index) }
            }

            Rectangle {
                width: parent.width / 4
                height: parent.height / 4
                anchors { right: parent.right; bottom: parent.bottom }
                color: "gray"; radius: 6; opacity: 0.3

                MouseArea {
                    id: mouseCorner

                    property int xpressed
                    property int ypressed

                    anchors.fill: parent

                    onPressed: { xpressed = mouseX; ypressed = mouseY }

                    onPositionChanged: {
                        if(gridItem.state == "inCodeEditorState") { return }

                        var relX = xpressed - mouseX
                        var relY = ypressed - mouseY
                        var relMax = Math.max(relX, relY)

                        // Only allow skin to be moved to upper left direction
                        if((skin.x - relMax) <= 0) { skin.x = skin.x - relMax; skin.y = skin.y - relMax }
                        if(skin.x < (gridItem.width / -5)) { codeEditorSignal(index) }
                    }

                    onReleased: { if(gridItem.state != "inCodeEditorState") { skin.x = 0; skin.y = 0 } }
                }
            }
        }

        // This will hold the dynamically loaded demo
        Item {
            id: demoHolder

            anchors { left: parent.left; top: parent.top; bottom: parent.bottom; right: sidePanel.left }
            opacity: 0

            ErrorDialog { id: errorDialog; anchors.centerIn: parent; onClosed: { textEditor.selectLine(lineNumber); codeEditorSignal(index) } }
        }

        SidePanel {
            id: sidePanel

            opacity: 0; width: 70
            source: "sidebar.png"
            anchors { right: parent.right; top: parent.top; bottom: parent.bottom }

            onCloseClicked: { if(errorDialog.opacity != 0) errorDialog.forceClose(); closeSignal(index) }
            onCodeEditorClicked: { if(errorDialog.opacity != 0) errorDialog.forceClose(); codeEditorSignal(index) }
        }
    }

    // These two animations are used to hide (and show) "the other" demos when the user selected demo is started or to it's code editor is entered
    // by this way the performance of the application will be a lot greater!
    SequentialAnimation {
        id: hideAnimation
        alwaysRunToEnd: true
        PropertyAction { target: textEditor; properties: "visible"; value: false }
        PropertyAnimation { target: container; properties: "opacity"; to: 0; duration: 500 }
    }

    SequentialAnimation {
        id: showAnimation
        alwaysRunToEnd: true
        PauseAnimation { duration: 1500 }
        PropertyAnimation { target: container; properties: "opacity"; to: 1; duration: 500 }
        PropertyAction { target: textEditor; properties: "visible"; value: true }
    }

    states: [
    State {
        name: "default" //default

        PropertyChanges { target: skin; x: 0; y: 0 }
        StateChangeScript { name: "scriptUnloadDemo"; script: Core.unloadDemo() }
    },
    State {
        name: "maximizedState"

        PropertyChanges { target: gridItem; z: 1 }
        ParentChange { target: container; parent: demoChooser }
        PropertyChanges { target: container; x: 0; y: 0; width: parent.width; height: parent.height; opacity: 1; radius: 0; color: "black" }
        PropertyChanges { target: skin; x: 0; y: 0; opacity: 0.0 }
        StateChangeScript { name: "scriptLoadDemo"; script: Core.loadDemo() }
        PropertyChanges { target: demoHolder; opacity: 1 }
        PropertyChanges { target: sidePanel; opacity: 1}
        PropertyChanges { target: textEditor; opacity: 0 }
        StateChangeScript { name: "scriptStartDemo"; script: Core.startDemo() }
    },
    State {
        name: "inCodeEditorState"

        ParentChange { target: container; parent: demoChooser }
        PropertyChanges { target: skin; x: -1 * container.width; y: -1 * container.height; opacity: 0.0 }
        PropertyChanges { target: gridItem; z: 1 }
        PropertyChanges { target: container; x:0; y: 0; width: parent.width; height: parent.height; radius: 0 }
        StateChangeScript { name: "scriptUnloadDemo"; script: Core.unloadDemo() }
    }
    ]

    transitions: [
    Transition {
        from: "default"
        to: "maximizedState"
        reversible: false
        SequentialAnimation {
            PauseAnimation { duration: 500 }
            PropertyAction { target: textEditor; property: "opacity" }
            PropertyAction { target: gridItem; property: "z" }
            ParentAnimation {
                target: container
                PropertyAnimation { target: container; properties: "x,y,width,height,radius"; duration: 1000; easing.type: "InOutCubic" }
                PropertyAnimation { target: skin; property: "opacity" }
            }
            ScriptAction { scriptName: "scriptLoadDemo" }
            ParallelAnimation {
                PropertyAnimation { target: demoHolder; property: "opacity"; duration: 1000 }
                PropertyAnimation { target: sidePanel; property: "opacity"; duration: 1000 }
            }
            PauseAnimation { duration: 100 }
            ScriptAction { scriptName: "scriptStartDemo" }
        }
    },
    Transition {
        from: "maximizedState"
        to: "default"
        reversible: false
        SequentialAnimation {
            PropertyAnimation { target: demoHolder; property: "opacity"; duration: 500 }
            ScriptAction { scriptName: "scriptUnloadDemo" }
            ParentAnimation {
                target: container
                PropertyAnimation { target: container; properties: "x,y,width,height,opacity,radius"; duration: 1000; easing.type: "InOutCubic" }
            }
            PropertyAnimation { target: skin; property: "opacity" }
            PropertyAction { target: container; property: "color" }
            PropertyAction { target: textEditor; property: "opacity" }
            PropertyAction { target: gridItem; property: "z" }
        }
    },
    Transition {
        from: "default"
        to: "inCodeEditorState"
        reversible: false
        SequentialAnimation {
            PropertyAnimation { target: skin; properties: "x,y,opacity"; duration: 700 }
            ParentAnimation {
                target: container
                PropertyAnimation { target: textEditor; property: "radius"; duration: 1000 }
                PropertyAnimation { target: container; properties: "x,y,width,height,radius"; duration: 1000; easing.type: "InOutCubic" }
            }
        }
    },
    Transition {
        from: "inCodeEditorState"
        to: "default"
        reversible: false
        SequentialAnimation {
            ParentAnimation {
                target: container
                PropertyAnimation { target: container; properties: "x,y,width,height,opacity,radius"; duration: 1000; easing.type: "InOutCubic" }
            }
            PropertyAnimation { target: skin; properties: "x,y,opacity"; duration: 500 }
            PropertyAction { target: gridItem; property: "z" }
        }
    },
    Transition {
        from: "inCodeEditorState"
        to: "maximizedState"
        reversible: false
        SequentialAnimation {
            ParallelAnimation {
                PropertyAnimation { target: textEditor; property: "opacity"; duration: 1000 }
                ColorAnimation { target: container; duration: 1000 }
            }
            ScriptAction { scriptName: "scriptLoadDemo" }
            ParallelAnimation {
                PropertyAnimation { target: demoHolder; property: "opacity"; duration: 1000 }
                PropertyAnimation { target: sidePanel; property: "opacity"; duration: 1000 }
            }
            PauseAnimation { duration: 100 }
            ScriptAction { scriptName: "scriptStartDemo" }
        }
    },
    Transition {
        from: "maximizedState"
        to: "inCodeEditorState"
        reversible: false
        SequentialAnimation {
            PropertyAction { target: skin; properties: "x,y" }
            ParallelAnimation {
                PropertyAnimation { target: sidePanel; property: "opacity"; duration : 1000 }
                PropertyAnimation { target: demoHolder; property: "opacity"; duration: 1000 }
            }

            ScriptAction { scriptName: "scriptUnloadDemo" }
            ParallelAnimation {
                ColorAnimation { target: container; duration: 200 }
                PropertyAnimation { target: textEditor; property: "opacity"; duration: 1000 }
            }
        }
    }
    ]
}
