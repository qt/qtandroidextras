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

#include "androidbinder.h"

#include <QDebug>

const static char TAG[] = "Service process";

bool AndroidBinder::onTransact(int code,
                               const QAndroidParcel &data,
                               const QAndroidParcel &reply,
                               QAndroidBinder::CallType flags)
{
    qDebug() << TAG << ": onTransact(), code " << code << ", flags " << int(flags);

    switch (code) {
    case 1: {
        QAndroidBinder binder = data.readBinder();

        const QString name(data.readData());
        qDebug() << TAG << ": onTransact() received name " << name;

        reply.writeVariant("Hello " + name);
    } break;
    default:
        QAndroidBinder binder = data.readBinder();

        qDebug() << TAG << ": onTransact() received non-name data" << data.readVariant();
        reply.writeVariant(QVariant("Cannot process this!"));

        // send back message
        QAndroidParcel sendData, replyData;
        sendData.writeVariant(QVariant("Send me only names!"));
        binder.transact(0, sendData, &replyData);
        qDebug() << TAG << ": onTransact() received " << replyData.readData();

        break;
    }
    return true;
}
