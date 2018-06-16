/*
 * Copyright (c) 2011 Nokia Corporation.
 */

#include <QFile>
#include <QApplication>
#include "qmlcodeprovider.h"


QMLCodeProvider::QMLCodeProvider()
{
}


QString QMLCodeProvider::loadQMLCode(const QString &filename)
{
    if(filename == "") {
        return "";
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        return tr("Failed to open file");
    }

    return file.readAll();
}


bool QMLCodeProvider::saveQMLCode(const QString &filename, const QString &code)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Truncate)) {
        return false;
    }

    file.write(code.toAscii());

    return true;
}


unsigned int QMLCodeProvider::getOSType()
{
    OS_TYPE os_type = UNKNOWN;
/*#ifdef Q_WS_WIN
    os_type = WINDOWS;
#endif

#ifdef Q_WS_X11
    os_type = X11;
#endif

#if defined(Q_WS_MAEMO_5) 
    os_type = MAEMO5;
#endif

#ifdef Q_OS_SYMBIAN
    os_type = SYMBIAN;
#endif

#ifdef Q_WS_MAC
    os_type = MAC;
#endif
#if defined(Q_WS_MAEMO_6) 
    os_type = MAEMO6;
#endif*/
    os_type = X11;
    return os_type;
}
