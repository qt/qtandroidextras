/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QtAndroidExtras/QJNIEnvironment>

class tst_QJNIEnvironment : public QObject
{
    Q_OBJECT

private slots:
    void jniEnv();
    void javaVM();

public:
    static JavaVM *m_javaVM;
};

JavaVM *tst_QJNIEnvironment::m_javaVM = 0;

void tst_QJNIEnvironment::jniEnv()
{
    QVERIFY(m_javaVM);

    {
        QJNIEnvironment env;

        // JNI environment should now be attached to the current thread
        JNIEnv *jni = 0;
        QCOMPARE(m_javaVM->GetEnv((void**)&jni, JNI_VERSION_1_6), JNI_OK);

        JNIEnv *e = env;
        QVERIFY(e);

        QCOMPARE(env->GetVersion(), JNI_VERSION_1_6);

        // try to find an existing class
        QVERIFY(env->FindClass("java/lang/Object"));
        QVERIFY(!env->ExceptionCheck());

        // try to find a nonexistent class
        QVERIFY(!env->FindClass("this/doesnt/Exist"));
        QVERIFY(env->ExceptionCheck());
        env->ExceptionClear();
    }

    // The environment should automatically be detached when QJNIEnvironment goes out of scope
    JNIEnv *jni = 0;
    QCOMPARE(m_javaVM->GetEnv((void**)&jni, JNI_VERSION_1_6), JNI_EDETACHED);
}

void tst_QJNIEnvironment::javaVM()
{
    QVERIFY(m_javaVM);

    QJNIEnvironment env;
    QCOMPARE(env.javaVM(), m_javaVM);

    JavaVM *vm = 0;
    QCOMPARE(env->GetJavaVM(&vm), JNI_OK);
    QCOMPARE(env.javaVM(), vm);
}

Q_DECL_EXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    Q_UNUSED(reserved)
    tst_QJNIEnvironment::m_javaVM = vm;
    return JNI_VERSION_1_6;
}

QTEST_APPLESS_MAIN(tst_QJNIEnvironment)

#include "tst_qjnienvironment.moc"
