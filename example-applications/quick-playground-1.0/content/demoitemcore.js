/*
 * Copyright (c) 2011 Nokia Corporation.
 */

// Holds the dynamically loaded demo, only one demo can be loaded at the time.
// This way resources usage is kept as low as possible.
var loadedDemo = null;

function loadDemo() {
    if(loadedDemo != null) {
        console.log("Demo was not null! There is something wrong in QML code!!! Calling unloadDemo!")
        unloadDemo()
    }

    try {
        loadedDemo = Qt.createQmlObject(gridItem.qmlCode, demoHolder, qmlFolder)
        //loadedDemo = createQmlObject(gridItem.qmlCode, demoHolder, qmlFolder)
    }
    catch(err) {
        errorDialog.show(err.qmlErrors[0].lineNumber, 'Error on line ' + err.qmlErrors[0].lineNumber + '\n' + err.qmlErrors[0].message)
    }
}

function startDemo() {
    if(loadedDemo != null) {
        loadedDemo.initialize()
    }
}

function unloadDemo() {
    if(loadedDemo != null) {
        loadedDemo.destroy()
        loadedDemo = null
    }
}
