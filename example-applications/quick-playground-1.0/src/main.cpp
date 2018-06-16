/*
 * Copyright (c) 2011 Nokia Corporation.
 */

#include <QtGui>
#include <QtDeclarative>
#include "qmlcodeprovider.h"
#include "taskswitcher.h"

// Lock orientation in Symbian
#ifdef Q_OS_SYMBIAN
    #include <eikenv.h>
    #include <eikappui.h>
    #include <aknenv.h>
    #include <aknappui.h>
#endif

#ifndef QT_NO_OPENGL
    #include <QGLWidget>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Lock orientation in Symbian
#ifdef Q_OS_SYMBIAN
    CAknAppUi* appUi = dynamic_cast<CAknAppUi*> (CEikonEnv::Static()->AppUi());
    TRAP_IGNORE(
        if(appUi) {
            appUi->SetOrientationL(CAknAppUi::EAppUiOrientationLandscape);
        }
    );
#endif

    QDeclarativeView view;

#ifndef QT_NO_OPENGL
    // Use QGLWidget to get the opengl support in Windows
    QGLFormat format = QGLFormat::defaultFormat();
    format.setSampleBuffers(false);

    QGLWidget *glWidget = new QGLWidget(format);
    glWidget->setAutoFillBackground(false);
    view.setViewport(glWidget);     // ownership of glWidget is taken
#endif

    // use this if the WebView and Particles modules are somewhere else than under the Qt libraries
    view.engine()->addImportPath("./imports");

    QMLCodeProvider codeProvider;

    view.rootContext()->setContextProperty("codeprovider", &codeProvider);
    view.setSource(QUrl("qrc:/demochooser.qml"));
    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);

#if defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    // Set the place where High score list of the SameGame demo is stored in Maemo
    view.engine()->setOfflineStoragePath("/home/user/MyDocs/");
#endif

    QObject *rootObject = dynamic_cast<QObject*>(view.rootObject());

    // Task switcher
    TaskSwitcher taskSwitcher;
    QObject::connect(rootObject, SIGNAL(minimizeApplication()), &taskSwitcher, SLOT(minimizeApplication()));
    QObject::connect((QObject*)view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    // Show application as fullscreen on Symbian and Maemo
/*#if defined(Q_OS_SYMBIAN)
    view.setGeometry(QRect(0, 0, 640, 360));
    view.showFullScreen();
#elif defined(Q_WS_MAEMO_5)*/
    view.setGeometry(QRect(0, 0, 800, 480));
    view.showFullScreen();
/*#elif defined(Q_WS_MAEMO_6)
    view.setGeometry(QRect(0, 0, 854, 480));
    view.showFullScreen();
#else
    view.setGeometry(QRect(100,100,800, 480));
    view.show();
#endif*/

    return app.exec();
}
