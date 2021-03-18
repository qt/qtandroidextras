/****************************************************************************
**
** Copyright (C) 2021 BogDan Vatra <bogdan@kde.org>
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

#ifndef QANDROIDBINDER_H
#define QANDROIDBINDER_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QSharedPointer>

#include <jni.h>

QT_BEGIN_NAMESPACE
class QAndroidBinderPrivate;
class QAndroidParcel;
class QAndroidJniObject;

class Q_ANDROIDEXTRAS_EXPORT QAndroidBinder
{
public:
    enum class CallType {
        Normal = 0,
        OneWay = 1
    };

public:
    explicit QAndroidBinder();
    QAndroidBinder(const QAndroidJniObject &binder);

    virtual ~QAndroidBinder();

    virtual bool onTransact(int code, const QAndroidParcel &data, const QAndroidParcel &reply, CallType flags);
    bool transact(int code, const QAndroidParcel &data, QAndroidParcel *reply = nullptr, CallType flags = CallType::Normal) const;

    QAndroidJniObject handle() const;

private:
    friend class QAndroidBinderPrivate;
    friend class QAndroidParcelPrivate;
    friend class QAndroidServicePrivate;
    QSharedPointer<QAndroidBinderPrivate> d;
};
QT_END_NAMESPACE

#endif // QANDROIDBINDER_H
