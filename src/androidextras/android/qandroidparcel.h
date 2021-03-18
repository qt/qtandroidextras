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

#ifndef QANDROIDPARCEL_H
#define QANDROIDPARCEL_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QSharedPointer>
#include <QVariant>

QT_BEGIN_NAMESPACE
class QAndroidBinder;
class QAndroidJniObject;
class QAndroidParcelPrivate;
class Q_ANDROIDEXTRAS_EXPORT QAndroidParcel
{
public:
    QAndroidParcel();
    explicit QAndroidParcel(const QAndroidJniObject& parcel);
    virtual ~QAndroidParcel();

    void writeData(const QByteArray &data) const;
    void writeVariant(const QVariant &value) const;
    void writeBinder(const QAndroidBinder &binder) const;
    void writeFileDescriptor(int fd) const;

    QByteArray readData() const;
    QVariant readVariant() const;
    QAndroidBinder readBinder() const;
    int readFileDescriptor() const;

    QAndroidJniObject handle() const;

private:
    friend class QAndroidParcelPrivate;
    friend class QAndroidBinder;
    QSharedPointer<QAndroidParcelPrivate> d;
};

QT_END_NAMESPACE

#endif // QANDROIDPARCEL_H
