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
#ifndef MULTIACTIVITY_H
#define MULTIACTIVITY_H

#include <QtAndroid>

class ActivityHandler : public QObject
{
    Q_OBJECT

public:
    ActivityHandler(QObject *parent = nullptr);
    static ActivityHandler *instance() { return m_instance; }

    Q_INVOKABLE void showSecondActivity();
    void activityReceiver(int requestCode, int resultCode, const QAndroidJniObject &data);

signals:
    void receiveFromActivityResult(const QString &message);

private:
    static ActivityHandler *m_instance;
};

#endif // MULTIACTIVITY_H
