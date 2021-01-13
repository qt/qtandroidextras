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

#ifndef QANDROIDACTIVITYRESULTRECEIVER_P_H
#define QANDROIDACTIVITYRESULTRECEIVER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qhash.h>
#include <QtCore/private/qjnihelpers_p.h>
#include "qandroidactivityresultreceiver.h"

QT_BEGIN_NAMESPACE

class QAndroidActivityResultReceiverPrivate: public QtAndroidPrivate::ActivityResultListener
{
public:
    QAndroidActivityResultReceiver *q;
    mutable QHash<int, int> localToGlobalRequestCode;
    mutable QHash<int, int> globalToLocalRequestCode;

    int globalRequestCode(int localRequestCode) const;
    bool handleActivityResult(jint requestCode, jint resultCode, jobject data);

    static QAndroidActivityResultReceiverPrivate *get(QAndroidActivityResultReceiver *publicObject)
    {
        return publicObject->d.data();
    }
};

QT_END_NAMESPACE

#endif // QANDROIDACTIVITYRESULTRECEIVER_P_H
