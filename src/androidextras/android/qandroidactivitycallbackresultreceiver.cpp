/****************************************************************************
**
** Copyright (C) 2021 Klaralvdalens Datakonsult AB (KDAB).
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

#include "qandroidactivitycallbackresultreceiver_p.h"

QAndroidActivityCallbackResultReceiver * QAndroidActivityCallbackResultReceiver::s_instance = nullptr;

QAndroidActivityCallbackResultReceiver::QAndroidActivityCallbackResultReceiver()
    : QAndroidActivityResultReceiver()
    , callbackMap()
{
}

void QAndroidActivityCallbackResultReceiver::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &intent)
{
    callbackMap[receiverRequestCode](receiverRequestCode, resultCode, intent);
    callbackMap.remove(receiverRequestCode);
}

QAndroidActivityCallbackResultReceiver * QAndroidActivityCallbackResultReceiver::instance() {
    if (!s_instance) {
        s_instance = new QAndroidActivityCallbackResultReceiver();
    }
    return s_instance;
}

void QAndroidActivityCallbackResultReceiver::registerCallback(int receiverRequestCode, std::function<void(int, int, const QAndroidJniObject &data)> callbackFunc)
{
    callbackMap.insert(receiverRequestCode, callbackFunc);
}
