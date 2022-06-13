//
// Copyright (c) 2022 Glauco Pacheco <glauco@cuteserver.io>
// All rights reserved
//

#include "FortunesClient.h"
#include <QCoreApplication>


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const auto args = QCoreApplication::arguments();
    QUrl remoteObjectUrl;
    for (const auto &arg : args)
    {
        if (!arg.startsWith(QStringLiteral("--remoteObjectUrl=")))
            continue;
        remoteObjectUrl = QUrl(arg.mid(18));
    }
    if (remoteObjectUrl.isEmpty())
        qFatal("Given remoteObjectUrl is empty. Specify the remote object URL as follows: --remoteObjectUrl=remote_object_url");
    FortunesClient fortunesClient(remoteObjectUrl);
    return QCoreApplication::exec();
}
