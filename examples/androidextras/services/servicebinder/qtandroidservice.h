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

#include <QAndroidBinder>
#include <QAndroidServiceConnection>
#include <QtAndroid>

class AndroidServiceConnection : public QAndroidServiceConnection
{
public:
    void onServiceConnected(const QString &name, const QAndroidBinder &serviceBinder) override;

    void onServiceDisconnected(const QString &name) override;

    void sendToService(const QString &name);

private:
    QAndroidBinder m_servieBinder;
};

class QtAndroidService : public QObject
{
    Q_OBJECT

public:
    explicit QtAndroidService(QObject *parent = nullptr);
    static QtAndroidService *instance() { return m_instance; }
    Q_INVOKABLE void sendToService(const QString &name);

signals:
    void messageFromService(const QString &message);

private:
    static QtAndroidService *m_instance;
    AndroidServiceConnection m_serviceConnection;
};
