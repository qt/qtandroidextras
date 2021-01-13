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

package org.qtproject.example.qtandroidservice;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.os.IBinder;
import org.qtproject.qt5.android.bindings.QtService;
import android.content.IntentFilter;


public class QtAndroidService extends QtService
{
    private static final String TAG = "QtAndroidService";

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Creating Service");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Destroying Service");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int ret = super.onStartCommand(intent, flags, startId);

        String name = new String(intent.getByteArrayExtra("name"));
        Intent sendToUiIntent = new Intent();
        sendToUiIntent.setAction(ActivityUtils.BROADCAST_NAME_ACTION);
        sendToUiIntent.putExtra("name", name);
        Log.i(TAG, "Service sending broadcast");
        sendBroadcast(sendToUiIntent);

        return ret;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return super.onBind(intent);
    }
}
