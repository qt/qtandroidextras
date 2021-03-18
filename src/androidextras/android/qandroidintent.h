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

#ifndef QANDROIDINTENT_H
#define QANDROIDINTENT_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QtAndroidExtras/qandroidjniobject.h>

QT_BEGIN_NAMESPACE
class QAndroidJniObject;
class Q_ANDROIDEXTRAS_EXPORT QAndroidIntent
{
public:
    QAndroidIntent();
    virtual ~QAndroidIntent();
    explicit QAndroidIntent(const QAndroidJniObject &intent);
    explicit QAndroidIntent(const QString &action);
    explicit QAndroidIntent(const QAndroidJniObject &packageContext, const char *className);

    void putExtra(const QString &key, const QByteArray &data);
    QByteArray extraBytes(const QString &key);

    void putExtra(const QString &key, const QVariant &value);
    QVariant extraVariant(const QString &key);

    QAndroidJniObject handle() const;

private:
    QAndroidJniObject m_handle;
};
QT_END_NAMESPACE

#endif // QANDROIDINTENT_H
