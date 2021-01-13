/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/
#include "rep_qtandroidservice_replica.h"
#include "qtandroidservice_ro.h"

#include <QAndroidIntent>
#include <QtAndroid>
#include <QAndroidService>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

void startService()
{
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                        "org/qtproject/example/qtandroidservice/QtAndroidService");
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;

        startService();

        QRemoteObjectNode repNode;
        repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
        QSharedPointer<QtAndroidServiceReplica> rep(repNode.acquire<QtAndroidServiceReplica>());
        engine.rootContext()->setContextProperty("qtAndroidService", rep.data());
        bool res = rep->waitForSource();
        Q_ASSERT(res);
        rep->sendToService("Qt");

        engine.load(QUrl(QLatin1String("qrc:/main.qml")));

        return app.exec();

    } else if (argc > 1 && strcmp(argv[1], "-service") == 0) {
        qWarning() << "QtAndroidService starting from same .so";
        QAndroidService app(argc, argv);

        QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
        QtAndroidService qtAndroidService;
        srcNode.enableRemoting(&qtAndroidService);

        return app.exec();

    } else {
        qWarning() << "Unrecognized command line argument";
        return -1;
    }
}
