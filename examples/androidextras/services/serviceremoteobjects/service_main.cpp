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
#include "qtandroidservice_ro.h"

#include <QDebug>
#include <QAndroidService>

int main(int argc, char *argv[])
{
    qWarning() << "QtAndroidService starting from separate .so";
    QAndroidService app(argc, argv);

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
    QtAndroidService qtAndroidService;
    srcNode.enableRemoting(&qtAndroidService);

    return app.exec();
}
