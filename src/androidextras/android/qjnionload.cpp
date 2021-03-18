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

#include "qandroidbinder.h"
#include "qandroidparcel.h"
#include "qandroidserviceconnection.h"

#include <android/log.h>
#include <QAndroidJniObject>
#include <jni.h>

static jboolean onTransact(JNIEnv */*env*/, jclass /*cls*/, jlong id, jint code, jobject data, jobject reply, jint flags)
{
    if (!id)
        return false;
    return reinterpret_cast<QAndroidBinder*>(id)->onTransact(code, QAndroidParcel(data), QAndroidParcel(reply), QAndroidBinder::CallType(flags));
}

static void onServiceConnected(JNIEnv */*env*/, jclass /*cls*/, jlong id, jstring name, jobject service)
{
    if (!id)
        return;
    return reinterpret_cast<QAndroidServiceConnection *>(id)->onServiceConnected(QAndroidJniObject(name).toString(),
                                                                                  QAndroidBinder(service));
}

static void onServiceDisconnected(JNIEnv */*env*/, jclass /*cls*/, jlong id, jstring name)
{
    if (!id)
        return;
    return reinterpret_cast<QAndroidServiceConnection *>(id)->onServiceDisconnected(QAndroidJniObject(name).toString());
}

static JNINativeMethod methods[] = {
    {"onTransact", "(JILandroid/os/Parcel;Landroid/os/Parcel;I)Z", (void *)onTransact},
    {"onServiceConnected", "(JLjava/lang/String;Landroid/os/IBinder;)V", (void *)onServiceConnected},
    {"onServiceDisconnected", "(JLjava/lang/String;)V", (void *)onServiceDisconnected}
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
    static bool initialized = false;
    if (initialized)
        return JNI_VERSION_1_6;
    initialized = true;

    typedef union {
        JNIEnv *nativeEnvironment;
        void *venv;
    } UnionJNIEnvToVoid;

    UnionJNIEnvToVoid uenv;
    uenv.venv = nullptr;

    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_FATAL, "Qt", "GetEnv failed");
        return -1;
    }

    JNIEnv *env = uenv.nativeEnvironment;
    jclass clazz;
    clazz = env->FindClass("org/qtproject/qt5/android/extras/QtNative");
    if (!clazz) {
        __android_log_print(ANDROID_LOG_FATAL,"Qt", "Can't find \"org/qtproject/qt5/android/extras/QtNative\" class");
        return -1;
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        __android_log_print(ANDROID_LOG_FATAL,"Qt", "RegisterNatives failed");
        return -1;
    }

    return JNI_VERSION_1_6;
}
