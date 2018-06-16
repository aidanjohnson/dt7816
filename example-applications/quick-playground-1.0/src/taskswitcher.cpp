/*
 * Copyright (c) 2011 Nokia Corporation.
 */

#include "taskswitcher.h"

// Task Switcher for maemo
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    #include <QtDBus/QtDBus>
#endif

TaskSwitcher::TaskSwitcher()
{
}


void TaskSwitcher::minimizeApplication()
{
    // TODO: What should happen in symbian and in other OS?

#if defined(Q_WS_MAEMO_5)
    // Uses DBus to minimize application in Maemo
    QDBusConnection connection = QDBusConnection::sessionBus();
    QDBusMessage message = QDBusMessage::createSignal("/","com.nokia.hildon_desktop","exit_app_view");
    connection.send(message);
#endif
}
