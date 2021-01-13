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

#ifndef QANDROIDFUNCTIONS_H
#define QANDROIDFUNCTIONS_H

#if 0
#pragma qt_class(QtAndroid)
#endif

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QtAndroidExtras/qandroidjniobject.h>

#include <functional>

QT_BEGIN_NAMESPACE

class QAndroidActivityResultReceiver;
class QAndroidServiceConnection;
class QAndroidIntent;

namespace QtAndroid
{
    Q_ANDROIDEXTRAS_EXPORT QAndroidJniObject androidActivity();
    Q_ANDROIDEXTRAS_EXPORT QAndroidJniObject androidService();
    Q_ANDROIDEXTRAS_EXPORT QAndroidJniObject androidContext();
    Q_ANDROIDEXTRAS_EXPORT int androidSdkVersion();

    Q_ANDROIDEXTRAS_EXPORT void startIntentSender(const QAndroidJniObject &intentSender,
                                                  int receiverRequestCode,
                                                  QAndroidActivityResultReceiver *resultReceiver = nullptr);
    Q_ANDROIDEXTRAS_EXPORT void startActivity(const QAndroidJniObject &intent,
                                              int receiverRequestCode,
                                              QAndroidActivityResultReceiver *resultReceiver = nullptr);
    Q_ANDROIDEXTRAS_EXPORT void startActivity(const QAndroidIntent &intent,
                                              int receiverRequestCode,
                                              QAndroidActivityResultReceiver *resultReceiver = nullptr);
    Q_ANDROIDEXTRAS_EXPORT void startActivity(const QAndroidJniObject &intent,
                                              int receiverRequestCode,
                                              std::function<void(int, int, const QAndroidJniObject &data)> callbackFunc);

    enum class BindFlag {
        None                = 0x00000000,
        AutoCreate          = 0x00000001,
        DebugUnbind         = 0x00000002,
        NotForeground       = 0x00000004,
        AboveClient         = 0x00000008,
        AllowOomManagement  = 0x00000010,
        WaivePriority       = 0x00000020,
        Important           = 0x00000040,
        AdjustWithActivity  = 0x00000080,
        ExternalService     = -2147483648 // 0x80000000

    };
    Q_DECLARE_FLAGS(BindFlags, BindFlag)

    Q_ANDROIDEXTRAS_EXPORT bool bindService(const QAndroidIntent &serviceIntent,
                                            const QAndroidServiceConnection &serviceConnection,
                                            BindFlags flags = BindFlag::None);

    typedef std::function<void()> Runnable;
    Q_ANDROIDEXTRAS_EXPORT void runOnAndroidThread(const Runnable &runnable);
    Q_ANDROIDEXTRAS_EXPORT void runOnAndroidThreadSync(const Runnable &runnable, int timeoutMs = INT_MAX);

    Q_ANDROIDEXTRAS_EXPORT void hideSplashScreen(); // ### Qt6: merge with next overload
    Q_ANDROIDEXTRAS_EXPORT void hideSplashScreen(int duration);

    enum class PermissionResult {
        Granted,
        Denied
    };
    typedef QHash<QString, PermissionResult> PermissionResultMap;
    typedef std::function<void(const PermissionResultMap &)> PermissionResultCallback;
    Q_ANDROIDEXTRAS_EXPORT void requestPermissions(const QStringList &permissions, const PermissionResultCallback &callbackFunc);
    Q_ANDROIDEXTRAS_EXPORT PermissionResultMap requestPermissionsSync(const QStringList &permissions, int timeoutMs = INT_MAX);
    Q_ANDROIDEXTRAS_EXPORT PermissionResult checkPermission(const QString &permission);
    Q_ANDROIDEXTRAS_EXPORT bool shouldShowRequestPermissionRationale(const QString &permission);
}

QT_END_NAMESPACE

#endif // QANDROIDFUNCTIONS_H
