/*
 * Copyright (c) 2011 Nokia Corporation.
 */

#ifndef QMLCODEPROVIDER_H
#define QMLCODEPROVIDER_H

#include <QObject>

class QMLCodeProvider : public QObject
{
    Q_OBJECT
public:
    enum OS_TYPE {
        UNKNOWN = 0,
        WINDOWS = 1,
        X11     = 2,
        MAEMO5  = 3,
        SYMBIAN = 4,
        MAC     = 5,
        MAEMO6  = 6
    };

    QMLCodeProvider();

    Q_INVOKABLE QString loadQMLCode(const QString &filename);
    Q_INVOKABLE bool saveQMLCode(const QString &filename, const QString &code);
    Q_INVOKABLE unsigned int getOSType();
};

#endif // QMLCODEPROVIDER_H
