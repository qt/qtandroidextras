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
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

public class ActivityUtils {

    private static native void sendToQt(String message);

    private static final String TAG = "ActivityUtils";
    public static final String BROADCAST_NAME_ACTION = "org.qtproject.example.qtandroidservice.broadcast.name";

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BROADCAST_NAME_ACTION);
        context.registerReceiver(serviceMessageReceiver, intentFilter);
        Log.i(TAG, "Registered broadcast receiver");
    }

    private BroadcastReceiver serviceMessageReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.i(TAG, "In OnReceive broadcast receiver");
            if (BROADCAST_NAME_ACTION.equals(intent.getAction())) {
                String name = intent.getStringExtra("name");
                Log.i(TAG, "Service received name: " + name);
                String message = "Hello " + name;
                sendToQt(message);
                Log.i(TAG, "Service sent back message: " + message);
            }
        }
    };
}
