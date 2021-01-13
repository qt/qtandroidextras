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

#ifndef QTANDROIDSERVICE_H
#define QTANDROIDSERVICE_H

#include <QObject>
#include <QtAndroid>
#include <QAndroidIntent>

class QtAndroidService : public QObject
{
    Q_OBJECT

public:
    QtAndroidService(QObject *parent = nullptr);

    static QtAndroidService *instance() { return m_instance; }
    Q_INVOKABLE void sendToService(const QString &name);

signals:
    void messageFromService(const QString &message);

private:
    void registerNatives();
    void registerBroadcastReceiver();

    static QtAndroidService *m_instance;
};

#endif // QTANDROIDSERVICE_H
