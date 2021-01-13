/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#ifndef QANDROIDACTIVITYRESULTRECEIVER_H
#define QANDROIDACTIVITYRESULTRECEIVER_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QtAndroidExtras/qandroidjniobject.h>

QT_BEGIN_NAMESPACE

class QAndroidActivityResultReceiverPrivate;
class Q_ANDROIDEXTRAS_EXPORT QAndroidActivityResultReceiver
{
public:
    QAndroidActivityResultReceiver();
    virtual ~QAndroidActivityResultReceiver();
    virtual void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data) = 0;

private:
    friend class QAndroidActivityResultReceiverPrivate;
    Q_DISABLE_COPY(QAndroidActivityResultReceiver)

    QScopedPointer<QAndroidActivityResultReceiverPrivate> d;
};

QT_END_NAMESPACE

#endif // QANDROIDACTIVITYRESULTRECEIVER_H
