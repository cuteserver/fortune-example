//
// Copyright (c) 2022 Glauco Pacheco <glauco@cuteserver.io>
// All rights reserved
//

#ifndef FORTUNES_CLIENT_H
#define FORTUNES_CLIENT_H

#include <CuteClient.h>

using namespace Cute::Client;

class FortunesClient : public QObject
{
Q_OBJECT
public:
    explicit FortunesClient(const QUrl &remoteObjectUrl)
            : m_fortunes("Fortunes", remoteObjectUrl)
    {
        // Establish remote signal-slot connection
        RemoteObject::connect(&m_fortunes,
                              SIGNAL(newFortune(QString)),
                              this,
                              SLOT(onNewFortune(QString)));
    }

public slots:
    // Remote signal-slot connections require public slots.
    void onNewFortune(QString fortune)
    {
        qWarning("Received new fortune: %s", fortune.toUtf8().constData());
    }

private:
    RemoteObject m_fortunes;
};

#endif // FORTUNES_CLIENT_H
