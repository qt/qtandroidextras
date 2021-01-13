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

#ifndef QANDROIDJNIENVIRONMENT_H
#define QANDROIDJNIENVIRONMENT_H

#include <jni.h>
#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QtCore/qglobal.h>
#include <QtCore/qscopedpointer.h>

QT_BEGIN_NAMESPACE

class QJNIEnvironmentPrivate;

class Q_ANDROIDEXTRAS_EXPORT QAndroidJniEnvironment
{
public:
    QAndroidJniEnvironment();
    ~QAndroidJniEnvironment();
    static JavaVM *javaVM();
    JNIEnv *operator->();
    operator JNIEnv*() const;
    jclass findClass(const char *className);

private:
    Q_DISABLE_COPY(QAndroidJniEnvironment)
    QScopedPointer<QJNIEnvironmentPrivate> d;
};

class Q_ANDROIDEXTRAS_EXPORT QAndroidJniExceptionCleaner
{
public:
    enum class OutputMode {
        Silent,
        Verbose
    };

public:
    explicit QAndroidJniExceptionCleaner(OutputMode outputMode = OutputMode::Silent);
    ~QAndroidJniExceptionCleaner();

    void clean();
private:
    OutputMode m_outputMode;
};

QT_END_NAMESPACE

#endif // QANDROIDJNIENVIRONMENT_H
