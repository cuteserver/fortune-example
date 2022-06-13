//
// Copyright (c) 2022 Glauco Pacheco <glauco@cuteserver.io>
// All rights reserved
//

#ifndef FORTUNES_H
#define FORTUNES_H

// QObject-derived classes with signals and slots tagged as remote
// are mapped to endpoints on the server upon registration
#include <CuteServer.h>
#include <QTimer>
#include <QStringList>
#include <QRandomGenerator>

class Fortunes : public QObject
{
Q_OBJECT
public:
    // Constructor takes a single argument
    Fortunes(QSharedPointer<Cute::IConnectionInformation> connInfo)
    {
        Q_UNUSED(connInfo);
        m_fortunes << tr("You will learn a magnificent new way to develop network apps.")
                   << tr("Affordable. Reliable. Fast. You will have all three at once.")
                   << tr("You will never develop network apps like before.")
                   << tr("Don't give up. Network development will finally become fun.")
                   << tr("You will become a much better network apps developer.");
        m_timer.setInterval(5*1000);
        QObject::connect(&m_timer, &QTimer::timeout, this, &Fortunes::emitNewFortune);
        m_timer.start();
    }

    ~Fortunes() override = default;

signals:
    // Remote signals are tagged with the REMOTE_SIGNAL macro
    REMOTE_SIGNAL void newFortune(QString fortune);

private slots:
    void emitNewFortune()
    {
        emit newFortune(m_fortunes[QRandomGenerator::global()->bounded(m_fortunes.size())]);
    }

private:
    QTimer m_timer;
    QStringList m_fortunes;
};

#endif // FORTUNES_H
