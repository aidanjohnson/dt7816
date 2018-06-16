/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7
import "content"

Item {
    id: demoChooser


    signal minimizeApplication()    // called when task switcher button is pressed

    property int selectedIndex: -1  // no selection at the beginning
    property int maxDemoIndex: 5    // used by for loops in javascript

    function hideUnselectedDemos() {
        for(var i=0; i<=maxDemoIndex; i++) {
            if(i != selectedIndex) {
                resolveDemoItem(i).hide()
            }
        }
    }

    function showAllDemos() {
        for(var i=0; i<=maxDemoIndex; i++) {
            resolveDemoItem(i).show()
        }
    }

    function resolveDemoItem(index) {
        if(index == 0) return slideShow
        if(index == 1) return sameGame
        if(index == 2) return memoryGame
        if(index == 3) return fancyPicker
        if(index == 4) return webcontent
        if(index == 5) return helloWorld
        return NULL
    }

    function demoStartRequest(index) {
        // Allow demo to get started if no demo is selected or the current demo is in code editor mode
        if((selectedIndex == index) || (selectedIndex == -1)) {
            selectedIndex = index
            hideUnselectedDemos()
            resolveDemoItem(index).state = "maximizedState"
        }
    }

    function codeEditorRequest(index) {
        // Allow demo to go to code editor only if current demo is maximized or no demo is currently started
        if((selectedIndex == index) || (selectedIndex == -1)) {
            selectedIndex = index
            resolveDemoItem(index).state = "inCodeEditorState"
            hideUnselectedDemos()
        }
    }

    function closed(index) {
        // Demo is closed from maximized or code editor, the state of the demo is changed to default state
        workAroundForHarmattan.closeSoftwareInputPanel();
        resolveDemoItem(index).state = "default"
        selectedIndex = -1
        showAllDemos()
    }

    Component.onCompleted: {
        if(codeprovider.getOSType() != 3) {
            // Task Switcher button is visible only in Maemo5
            taskSwitcher.visible = true
        }
        if(codeprovider.getOSType() == 6) {
            // Task Switcher button is visible only in Maemo6
            exitButton.visible = true
        }
    }

    anchors.fill: parent    // the size is set in Qt code

    // Workaround for Harmattan to close VKB
    TextInput {
        id: workAroundForHarmattan
        opacity: 0
    }

    Image {
        id: backgroundImage

        anchors.fill: parent
        source: "back_gray.png"
        fillMode: "PreserveAspectCrop"

        Image {
            id: header

            anchors { left: parent.left; right: parent.right; top: parent.top }
            source: "back_header.png"
            fillMode: "PreserveAspectCrop"

            Button {
                id: taskSwitcher

                anchors { left: parent.left; leftMargin: 40; verticalCenter: parent.verticalCenter }
                source: "content/btn_taskbutton.png"; onClicked: demoChooser.minimizeApplication()
            }
/*
            Image {
                id: title

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: { if(taskSwitcher.visible == true) { return taskSwitcher.right } else { return parent.left } }
                anchors.leftMargin: 20
                source: "qtpl-title.png"
            }*/

            Image {
                id: logos

                anchors.left: title.right; anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                source: "logos.png"
            }
        
            Button {
                id: exitButton

                anchors { right: parent.right; rightMargin: 50; verticalCenter: parent.verticalCenter }
                source: "content/exit.png"; onClicked: Qt.quit()
            }
        }

        Grid {
            id: demoGrid

            property int demoWidth: demoGrid.width / demoGrid.columns - demoGrid.spacing
            property int demoHeight: demoGrid.height / demoGrid.rows - demoGrid.spacing

            anchors { top: header.bottom; topMargin: 10; bottom: parent.bottom; bottomMargin: 10 }
            anchors { left: parent.left; leftMargin: 25; right: parent.right; rightMargin: 25 }
            rows: 2; columns: 3; spacing: 10

            DemoItem {
                id: slideShow; index: 0; qmlFolder: "./slideshow/"
                width: demoGrid.demoWidth; height: demoGrid.demoHeight
                qmlCode: codeprovider.loadQMLCode(":/content/slideshow/slideshow.qml")
                thumbnail: "qrc:/content/icon_slideshow.png"
                onStartSignal:  { demoChooser.demoStartRequest(index) }
                onCodeEditorSignal: { demoChooser.codeEditorRequest(index) }
                onCloseSignal: { demoChooser.closed(index) }
                codeTemplateModel: modelSlideShow
                ListModel {
                    id: modelSlideShow
                    ListElement { titleText: "Slide change interval"; searchText: "interval: " }
                }
            }

            DemoItem {
                id: sameGame; index: 1; qmlFolder: "./samegame/"
                width: demoGrid.demoWidth; height: demoGrid.demoHeight
                qmlCode: codeprovider.loadQMLCode(":/content/samegame/samegame.qml")
                thumbnail: "qrc:/content/icon_samegame.png"
                onStartSignal: { demoChooser.demoStartRequest(index) }
                onCodeEditorSignal: { demoChooser.codeEditorRequest(index) }
                onCloseSignal: { demoChooser.closed(index) }
                codeTemplateModel: modelSameGame
                ListModel {
                    id: modelSameGame
                    ListElement { titleText: "Ball size"; searchText: "blockSize: " }
                }
            }

            DemoItem {
                id: memoryGame; index: 2; qmlFolder: "./memorygame/"
                width: demoGrid.demoWidth; height: demoGrid.demoHeight
                qmlCode: codeprovider.loadQMLCode(":/content/memorygame/memorygame.qml")
                thumbnail: "qrc:/content/icon_memorygame.png"
                onStartSignal: { demoChooser.demoStartRequest(index) }
                onCodeEditorSignal: { demoChooser.codeEditorRequest(index) }
                onCloseSignal: { demoChooser.closed(index) }
                codeTemplateModel: modelMemoryGame
                ListModel {
                    id: modelMemoryGame
                    ListElement { titleText: "Amount of cards"; searchText: "cards: " }
                    ListElement { titleText: "Amount of card columns"; searchText: "columns: " }
                    ListElement { titleText: "Amount of card rows"; searchText: "rows: " }
                }
            }

            DemoItem {
                id: fancyPicker; index: 3; qmlFolder: "./fancypicker/"
                width: demoGrid.demoWidth; height: demoGrid.demoHeight
                qmlCode: codeprovider.loadQMLCode(":/content/fancypicker/fancypicker.qml")
                thumbnail: "qrc:/content/icon_fancypicker.png"
                onStartSignal: { demoChooser.demoStartRequest(index) }
                onCodeEditorSignal: { demoChooser.codeEditorRequest(index) }
                onCloseSignal: { demoChooser.closed(index) }
            }

            DemoItem {
                id: webcontent; index: 4; qmlFolder: "./webcontent/"
                width: demoGrid.demoWidth; height: demoGrid.demoHeight
                qmlCode: codeprovider.loadQMLCode(":/content/webcontent/webcontent.qml")
                thumbnail: "qrc:/content/icon_webcontent.png"
                onStartSignal: { demoChooser.demoStartRequest(index) }
                onCodeEditorSignal: { demoChooser.codeEditorRequest(index) }
                onCloseSignal: { demoChooser.closed(index) }
            }

            DemoItem { id: helloWorld; index: 5; qmlFolder: "./helloworld/"
                width: demoGrid.demoWidth; height: demoGrid.demoHeight
                qmlCode: codeprovider.loadQMLCode(":/content/helloworld/hello.qml")
                thumbnail: "qrc:/content/icon_helloworld.png"
                onStartSignal: { demoChooser.demoStartRequest(index) }
                onCodeEditorSignal: { demoChooser.codeEditorRequest(index) }
                onCloseSignal: { demoChooser.closed(index) }
                codeTemplateModel: modelHelloWorld
                ListModel {
                    id: modelHelloWorld
                    ListElement { titleText: "Rotation speed"; searchText: "duration: " }
                }
            }
        }
    }
}

