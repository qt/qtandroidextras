/****************************************************************************
**
** Copyright (C) 2017 BogDan Vatra <bogdan@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
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
****************************************************************************/

#ifndef QTANDROIDSERVICECONNECTION_H
#define QTANDROIDSERVICECONNECTION_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QAndroidJniObject>

QT_BEGIN_NAMESPACE
class QAndroidBinder;
class Q_ANDROIDEXTRAS_EXPORT QAndroidServiceConnection
{
public:
    QAndroidServiceConnection();
    explicit QAndroidServiceConnection(const QAndroidJniObject &serviceConnection);
    virtual ~QAndroidServiceConnection();

    virtual void onServiceConnected(const QString &name, const QAndroidBinder &serviceBinder) = 0;
    virtual void onServiceDisconnected(const QString &name) = 0;

    QAndroidJniObject handle() const;
private:
    Q_DISABLE_COPY(QAndroidServiceConnection)
    QAndroidJniObject m_handle;
};

QT_END_NAMESPACE

#endif // QTANDROIDSERVICECONNECTION_H
