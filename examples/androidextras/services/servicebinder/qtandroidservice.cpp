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

#include "qtandroidservice.h"

#include <QAndroidIntent>
#include <QAndroidParcel>
#include <QDebug>

const static char TAG[] = "Service app";
QtAndroidService *QtAndroidService::m_instance = nullptr;

void AndroidServiceConnection::onServiceConnected(const QString &name,
                                                  const QAndroidBinder &serviceBinder)
{
    qDebug() << TAG << ": onServiceConnected() " << name;
    m_servieBinder = serviceBinder;
}

void AndroidServiceConnection::onServiceDisconnected(const QString &name)
{
    qDebug() << TAG << ": onServiceDisconnected() " << name;
}

void AndroidServiceConnection::sendToService(const QString &name)
{
    // send name
    QAndroidParcel sendData, replyData;
    sendData.writeBinder(m_servieBinder);
    sendData.writeData(name.toUtf8());
    m_servieBinder.transact(1, sendData, &replyData);
    const QVariant received(replyData.readVariant());
    qDebug() << received;
    emit QtAndroidService::instance()->messageFromService(received.toString());
}

QtAndroidService::QtAndroidService(QObject *parent) : QObject(parent)
{
    m_instance = this;

    QAndroidIntent serviceIntent(QtAndroid::androidActivity(),
                                 "org.qtproject.example.qtandroidservice.QtAndroidService");

    const bool bindResult = QtAndroid::bindService(serviceIntent,
                                                   m_serviceConnection,
                                                   QtAndroid::BindFlag::AutoCreate);
    qDebug() << "Binding to the service..." << bindResult;
}

void QtAndroidService::sendToService(const QString &name)
{
    m_serviceConnection.sendToService(name);
}
