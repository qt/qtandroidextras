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

#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QtDebug>

QtAndroidService *QtAndroidService::m_instance = nullptr;

static void receivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    emit QtAndroidService::instance()->messageFromService(env->GetStringUTFChars(value, nullptr));
}

QtAndroidService::QtAndroidService(QObject *parent) : QObject(parent)
{
    m_instance = this;

    JNINativeMethod methods[] {{"sendToQt", "(Ljava/lang/String;)V", reinterpret_cast<void *>(receivedFromAndroidService)}};
    QAndroidJniObject javaClass("org/qtproject/example/qtandroidservice/QtAndroidService");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void QtAndroidService::sendToService(const QString &name)
{
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                        "org/qtproject/example/qtandroidservice/QtAndroidService");
    serviceIntent.putExtra("name", name.toUtf8());
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
}
