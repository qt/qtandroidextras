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
import org.qtproject.qt5.android.bindings.QtService;
import android.util.Log;

public class QtAndroidService extends QtService
{
    private static final String TAG = "QtAndroidService";

    @Override
    public void onCreate() {
        Log.i(TAG, "Creating Service");
        super.onCreate();
    }

    @Override
    public void onDestroy() {
        Log.i(TAG, "Destroying Service");
        super.onDestroy();
    }
}
