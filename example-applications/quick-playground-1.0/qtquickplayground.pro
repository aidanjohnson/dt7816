# Copyright (c) 2011 Nokia Corporation.

QT       += core gui opengl
QT       += declarative

TARGET = qtquickplayground
TEMPLATE = app

VERSION = 1.4.1

SOURCES += src/main.cpp\
           src/qmlcodeprovider.cpp \
           src/taskswitcher.cpp

HEADERS  += src/qmlcodeprovider.h \
            src/taskswitcher.h

OTHER_FILES += demochooser.qml \
               content/button.qml \
               content/demoitem.qml \
               content/sidepanel.qml \
               content/texteditor.qml \
               content/demoitemcore.js \
               content/codebutton.qml \
               content/fancypicker/fancypicker.qml \
               content/fancypicker/slider.qml \
               content/helloworld/hello.qml \
               content/memorygame/memorygame.js \
               content/memorygame/memorygame.qml \
               content/samegame/samegame.qml \
               content/samegame/SameGameCore/boomblock.qml \
               content/samegame/SameGameCore/button.qml \
               content/samegame/SameGameCore/dialog.qml \
               content/samegame/SameGameCore/samegame.js \
               content/slideshow/slideshow.qml \
               content/webcontent/webcontent.qml \
               content/memorygame/card.qml \
               content/errordialog.qml \ 

RESOURCES =    resources.qrc

win32: !simulator {
    RC_FILE = qtquickplayground.rc
}


unix:!symbian {
    BINDIR = /opt/usr/bin
    DATADIR =/usr/share
    DEFINES += DATADIR=\\\"$$DATADIR\\\" \
        PKGDATADIR=\\\"$$PKGDATADIR\\\"
    INSTALLS += target \
        desktop \
        iconxpm \
        icon26 \
        icon40 \
        icon64

    target.path = $$BINDIR

    iconxpm.path = $$DATADIR/pixmap
    iconxpm.files += icons/xpm/qtquickplayground.xpm

    icon26.path = $$DATADIR/icons/hicolor/26x26/apps
    icon26.files += icons/26x26/qtquickplayground.png

    icon40.path = $$DATADIR/icons/hicolor/40x40/apps
    icon40.files += icons/40x40/qtquickplayground.png

    icon64.path = $$DATADIR/icons/hicolor/64x64/apps
    icon64.files += icons/64x64/qtquickplayground.png
    
    maemo5{
    	desktop.path = $$DATADIR/applications/hildon
    	desktop.files += qtc_packaging/debian_fremantle/$${TARGET}.desktop
    }
    else {
    	DEFINES += Q_WS_MAEMO_6
	desktop.path = $$DATADIR/applications
	desktop.files += qtc_packaging/debian_harmattan/$${TARGET}.desktop
     }		 
}

symbian {
    TARGET = QtQuickPlayground

    !contains(SYMBIAN_VERSION, Symbian3) {
        message(Symbian^1)
        # In Symbian^1 we don't have OpenGL available
        QT -= opengl
        DEFINES += QT_NO_OPENGL
    }

    ICON = icons/qtqpg.svg

    # To lock the application to landscape orientation
    LIBS += -lcone -leikcore -lavkon

    # WebView demo requires access to network
    TARGET.CAPABILITY = NetworkServices

    # Increase heap and stack size, FancyPicker consumes lots of memory
    # when viewing images
    TARGET.EPOCHEAPSIZE = 0x100000 0x2000000
    TARGET.EPOCSTACKSIZE = 0x14000
}
