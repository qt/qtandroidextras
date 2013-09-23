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

#include <QString>
#include <QtTest>
#include <QtAndroidExtras/QJNIObject>
#include <QtAndroidExtras/QJNIEnvironment>

class tst_QJNIObject : public QObject
{
    Q_OBJECT

public:
    tst_QJNIObject();

private slots:
    void initTestCase();

    void ctor();
    void callMethodTest();
    void callObjectMethodTest();
    void stringConvertionTest();
    void compareOperatorTests();
    void callStaticObjectMethodClassName();
    void callStaticObjectMethod();
    void callStaticBooleanMethodClassName();
    void callStaticBooleanMethod();
    void callStaticCharMethodClassName();
    void callStaticCharMethod();
    void callStaticIntMethodClassName();
    void callStaticIntMethod();
    void callStaticByteMethodClassName();
    void callStaticByteMethod();
    void callStaticDoubleMethodClassName();
    void callStaticDoubleMethod();
    void callStaticFloatMethodClassName();
    void callStaticFloatMethod();
    void callStaticLongMethodClassName();
    void callStaticLongMethod();
    void callStaticShortMethodClassName();
    void callStaticShortMethod();
    void getStaticObjectFieldClassName();
    void getStaticObjectField();
    void getStaticIntFieldClassName();
    void getStaticIntField();
    void getStaticByteFieldClassName();
    void getStaticByteField();
    void getStaticLongFieldClassName();
    void getStaticLongField();
    void getStaticDoubleFieldClassName();
    void getStaticDoubleField();
    void getStaticFloatFieldClassName();
    void getStaticFloatField();
    void getStaticShortFieldClassName();
    void getStaticShortField();
    void getStaticCharFieldClassName();
    void getStaticCharField();
    void getBooleanField();
    void getIntField();

    void cleanupTestCase();

public:
    static jclass m_activityDelegateClass;
};

jclass tst_QJNIObject::m_activityDelegateClass = 0;

tst_QJNIObject::tst_QJNIObject()
{
}

void tst_QJNIObject::initTestCase()
{
}

void tst_QJNIObject::cleanupTestCase()
{
}

void tst_QJNIObject::ctor()
{
    {
        QJNIObject object;
        QVERIFY(!object.isValid());
    }

    {
        QJNIObject object("java/lang/String");
        QVERIFY(object.isValid());
    }

    {
        QJNIObject string = QJNIObject::fromString(QLatin1String("Hello, Java"));
        QJNIObject object("java/lang/String", "(Ljava/lang/String;)V", string.object<jstring>());
        QVERIFY(object.isValid());
        QCOMPARE(string.toString(), object.toString());
    }

    {
        QJNIEnvironment env;
        jclass javaStringClass = env->FindClass("java/lang/String");
        QJNIObject string(javaStringClass);
        QVERIFY(string.isValid());
    }

    {
        QJNIEnvironment env;
        const QString qString = QLatin1String("Hello, Java");
        jclass javaStringClass = env->FindClass("java/lang/String");
        QJNIObject string = QJNIObject::fromString(qString);
        QJNIObject stringCpy(javaStringClass, "(Ljava/lang/String;)V", string.object<jstring>());
        QVERIFY(stringCpy.isValid());
        QCOMPARE(qString, stringCpy.toString());
    }
}

void tst_QJNIObject::callMethodTest()
{
    {
        QJNIObject jString1 = QJNIObject::fromString(QLatin1String("Hello, Java"));
        QJNIObject jString2 = QJNIObject::fromString(QLatin1String("hELLO, jAVA"));
        QVERIFY(jString1 != jString2);

        const jboolean isEmpty = jString1.callMethod<jboolean>("isEmpty");
        QVERIFY(!isEmpty);

        const jint ret = jString1.callMethod<jint>("compareToIgnoreCase",
                                                   "(Ljava/lang/String;)I",
                                                   jString2.object<jstring>());
        QVERIFY(0 == ret);
    }

    {
        jlong jLong = 100;
        QJNIObject longObject("java/lang/Long", "(J)V", jLong);
        jlong ret = longObject.callMethod<jlong>("longValue");
        QCOMPARE(ret, jLong);
    }
}

void tst_QJNIObject::callObjectMethodTest()
{
    const QString qString = QLatin1String("Hello, Java");
    QJNIObject jString = QJNIObject::fromString(qString);
    const QString qStringRet = jString.callObjectMethod<jstring>("toUpperCase").toString();
    QCOMPARE(qString.toUpper(), qStringRet);

    QJNIObject subString = jString.callObjectMethod("substring",
                                                    "(II)Ljava/lang/String;",
                                                    0, 4);
    QCOMPARE(subString.toString(), qString.mid(0, 4));
}

void tst_QJNIObject::stringConvertionTest()
{
    const QString qString(QLatin1String("Hello, Java"));
    QJNIObject jString = QJNIObject::fromString(qString);
    QVERIFY(jString.isValid());
    QString qStringRet = jString.toString();
    QCOMPARE(qString, qStringRet);
}

void tst_QJNIObject::compareOperatorTests()
{
    QString str("hello!");
    QJNIObject stringObject = QJNIObject::fromString(str);

    jobject jobj = stringObject.object<jobject>();
    jstring jsobj = stringObject.object<jstring>();

    QVERIFY(jobj == stringObject);
    QVERIFY(stringObject == jobj);
    QVERIFY(jsobj == stringObject);
    QVERIFY(stringObject == jsobj);

    QJNIObject stringObject3 = stringObject.object<jstring>();
    QVERIFY(stringObject3 == stringObject);

    QJNIObject stringObject2 = QJNIObject::fromString(str);
    QVERIFY(stringObject != stringObject2);

    jstring jstrobj = 0;
    QJNIObject invalidStringObject;
    QVERIFY(invalidStringObject == jstrobj);

    QVERIFY(jstrobj != stringObject);
    QVERIFY(stringObject != jstrobj);
    QVERIFY(!invalidStringObject.isValid());
}

void tst_QJNIObject::callStaticObjectMethodClassName()
{
    QJNIObject formatString = QJNIObject::fromString(QLatin1String("test format"));
    QVERIFY(formatString.isValid());

    QVERIFY(QJNIObject::isClassAvailable("java/lang/String"));
    QJNIObject returnValue = QJNIObject::callStaticObjectMethod("java/lang/String",
                                                                "format",
                                                                "(Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;",
                                                                formatString.object<jstring>(),
                                                                jobjectArray(0));
    QVERIFY(returnValue.isValid());

    QString returnedString = returnValue.toString();

    QCOMPARE(returnedString, QString::fromLatin1("test format"));
}

void tst_QJNIObject::callStaticObjectMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/String");
    QVERIFY(cls != 0);

    QJNIObject formatString = QJNIObject::fromString(QLatin1String("test format"));
    QVERIFY(formatString.isValid());

    QJNIObject returnValue = QJNIObject::callStaticObjectMethod(cls,
                                                                "format",
                                                                "(Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;",
                                                                formatString.object<jstring>(),
                                                                jobjectArray(0));
    QVERIFY(returnValue.isValid());

    QString returnedString = returnValue.toString();

    QCOMPARE(returnedString, QString::fromLatin1("test format"));
}

void tst_QJNIObject::callStaticBooleanMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Boolean");
    QVERIFY(cls != 0);

    {
        QJNIObject parameter = QJNIObject::fromString("true");
        QVERIFY(parameter.isValid());

        jboolean b = QJNIObject::callStaticMethod<jboolean>(cls,
                                                            "parseBoolean",
                                                            "(Ljava/lang/String;)Z",
                                                            parameter.object<jstring>());
        QVERIFY(b);
    }

    {
        QJNIObject parameter = QJNIObject::fromString("false");
        QVERIFY(parameter.isValid());

        jboolean b = QJNIObject::callStaticMethod<jboolean>(cls,
                                                            "parseBoolean",
                                                            "(Ljava/lang/String;)Z",
                                                            parameter.object<jstring>());
        QVERIFY(!b);
    }
}

void tst_QJNIObject::callStaticBooleanMethodClassName()
{
    {
        QJNIObject parameter = QJNIObject::fromString("true");
        QVERIFY(parameter.isValid());

        jboolean b = QJNIObject::callStaticMethod<jboolean>("java/lang/Boolean",
                                                            "parseBoolean",
                                                            "(Ljava/lang/String;)Z",
                                                            parameter.object<jstring>());
        QVERIFY(b);
    }

    {
        QJNIObject parameter = QJNIObject::fromString("false");
        QVERIFY(parameter.isValid());

        jboolean b = QJNIObject::callStaticMethod<jboolean>("java/lang/Boolean",
                                                            "parseBoolean",
                                                            "(Ljava/lang/String;)Z",
                                                            parameter.object<jstring>());
        QVERIFY(!b);
    }
}

void tst_QJNIObject::callStaticByteMethodClassName()
{
    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jbyte returnValue = QJNIObject::callStaticMethod<jbyte>("java/lang/Byte",
                                                            "parseByte",
                                                            "(Ljava/lang/String;)B",
                                                            parameter.object<jstring>());
    QCOMPARE(returnValue, jbyte(number.toInt()));
}

void tst_QJNIObject::callStaticByteMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Byte");
    QVERIFY(cls != 0);

    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jbyte returnValue = QJNIObject::callStaticMethod<jbyte>(cls,
                                                            "parseByte",
                                                            "(Ljava/lang/String;)B",
                                                            parameter.object<jstring>());
    QCOMPARE(returnValue, jbyte(number.toInt()));
}

void tst_QJNIObject::callStaticIntMethodClassName()
{
    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jint returnValue = QJNIObject::callStaticMethod<jint>("java/lang/Integer",
                                                          "parseInt",
                                                          "(Ljava/lang/String;)I",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toInt());
}


void tst_QJNIObject::callStaticIntMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Integer");
    QVERIFY(cls != 0);

    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jint returnValue = QJNIObject::callStaticMethod<jint>(cls,
                                                          "parseInt",
                                                          "(Ljava/lang/String;)I",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toInt());
}

void tst_QJNIObject::callStaticCharMethodClassName()
{
    jchar returnValue = QJNIObject::callStaticMethod<jchar>("java/lang/Character",
                                                            "toUpperCase",
                                                            "(C)C",
                                                            jchar('a'));
    QCOMPARE(returnValue, jchar('A'));
}


void tst_QJNIObject::callStaticCharMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Character");
    QVERIFY(cls != 0);

    jchar returnValue = QJNIObject::callStaticMethod<jchar>(cls,
                                                            "toUpperCase",
                                                            "(C)C",
                                                            jchar('a'));
    QCOMPARE(returnValue, jchar('A'));
}

void tst_QJNIObject::callStaticDoubleMethodClassName    ()
{
    QString number = QString::number(123.45);
    QJNIObject parameter = QJNIObject::fromString(number);

    jdouble returnValue = QJNIObject::callStaticMethod<jdouble>("java/lang/Double",
                                                          "parseDouble",
                                                          "(Ljava/lang/String;)D",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toDouble());
}


void tst_QJNIObject::callStaticDoubleMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Double");
    QVERIFY(cls != 0);

    QString number = QString::number(123.45);
    QJNIObject parameter = QJNIObject::fromString(number);

    jdouble returnValue = QJNIObject::callStaticMethod<jdouble>(cls,
                                                          "parseDouble",
                                                          "(Ljava/lang/String;)D",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toDouble());
}

void tst_QJNIObject::callStaticFloatMethodClassName()
{
    QString number = QString::number(123.45);
    QJNIObject parameter = QJNIObject::fromString(number);

    jfloat returnValue = QJNIObject::callStaticMethod<jfloat>("java/lang/Float",
                                                          "parseFloat",
                                                          "(Ljava/lang/String;)F",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toFloat());
}


void tst_QJNIObject::callStaticFloatMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Float");
    QVERIFY(cls != 0);

    QString number = QString::number(123.45);
    QJNIObject parameter = QJNIObject::fromString(number);

    jfloat returnValue = QJNIObject::callStaticMethod<jfloat>(cls,
                                                          "parseFloat",
                                                          "(Ljava/lang/String;)F",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toFloat());
}

void tst_QJNIObject::callStaticShortMethodClassName()
{
    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jshort returnValue = QJNIObject::callStaticMethod<jshort>("java/lang/Short",
                                                          "parseShort",
                                                          "(Ljava/lang/String;)S",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toShort());
}


void tst_QJNIObject::callStaticShortMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Short");
    QVERIFY(cls != 0);

    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jshort returnValue = QJNIObject::callStaticMethod<jshort>(cls,
                                                          "parseShort",
                                                          "(Ljava/lang/String;)S",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, number.toShort());
}

void tst_QJNIObject::callStaticLongMethodClassName()
{
    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jlong returnValue = QJNIObject::callStaticMethod<jlong>("java/lang/Long",
                                                          "parseLong",
                                                          "(Ljava/lang/String;)J",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, jlong(number.toLong()));
}

void tst_QJNIObject::callStaticLongMethod()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Long");
    QVERIFY(cls != 0);

    QString number = QString::number(123);
    QJNIObject parameter = QJNIObject::fromString(number);

    jlong returnValue = QJNIObject::callStaticMethod<jlong>(cls,
                                                          "parseLong",
                                                          "(Ljava/lang/String;)J",
                                                          parameter.object<jstring>());
    QCOMPARE(returnValue, jlong(number.toLong()));
}

void tst_QJNIObject::getStaticObjectFieldClassName()
{
    {
        QJNIObject boolObject = QJNIObject::getStaticObjectField<jobject>("java/lang/Boolean",
                                                                          "FALSE",
                                                                          "Ljava/lang/Boolean;");
        QVERIFY(boolObject.isValid());

        jboolean booleanValue = boolObject.callMethod<jboolean>("booleanValue");
        QVERIFY(!booleanValue);
    }

    {
        QJNIObject boolObject = QJNIObject::getStaticObjectField<jobject>("java/lang/Boolean",
                                                                 "TRUE",
                                                                 "Ljava/lang/Boolean;");
        QVERIFY(boolObject.isValid());

        jboolean booleanValue = boolObject.callMethod<jboolean>("booleanValue");
        QVERIFY(booleanValue);
    }
}

void tst_QJNIObject::getStaticObjectField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Boolean");
    QVERIFY(cls != 0);

    {
        QJNIObject boolObject = QJNIObject::getStaticObjectField<jobject>(cls,
                                                                          "FALSE",
                                                                          "Ljava/lang/Boolean;");
        QVERIFY(boolObject.isValid());

        jboolean booleanValue = boolObject.callMethod<jboolean>("booleanValue");
        QVERIFY(!booleanValue);
    }

    {
        QJNIObject boolObject = QJNIObject::getStaticObjectField<jobject>(cls,
                                                                 "TRUE",
                                                                 "Ljava/lang/Boolean;");
        QVERIFY(boolObject.isValid());

        jboolean booleanValue = boolObject.callMethod<jboolean>("booleanValue");
        QVERIFY(booleanValue);
    }
}

void tst_QJNIObject::getStaticIntFieldClassName()
{
    jint i = QJNIObject::getStaticField<jint>("java/lang/Double", "SIZE");
    QCOMPARE(i, 64);
}

void tst_QJNIObject::getStaticIntField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Double");
    QVERIFY(cls != 0);

    jint i = QJNIObject::getStaticField<jint>(cls, "SIZE");
    QCOMPARE(i, 64);
}

void tst_QJNIObject::getStaticByteFieldClassName()
{
    jbyte i = QJNIObject::getStaticField<jbyte>("java/lang/Byte", "MAX_VALUE");
    QCOMPARE(i, jbyte(127));
}

void tst_QJNIObject::getStaticByteField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Byte");
    QVERIFY(cls != 0);

    jbyte i = QJNIObject::getStaticField<jbyte>(cls, "MAX_VALUE");
    QCOMPARE(i, jbyte(127));
}

void tst_QJNIObject::getStaticLongFieldClassName()
{
    jlong i = QJNIObject::getStaticField<jlong>("java/lang/Long", "MAX_VALUE");
    QCOMPARE(i, jlong(9223372036854775807L));
}

void tst_QJNIObject::getStaticLongField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Long");
    QVERIFY(cls != 0);

    jlong i = QJNIObject::getStaticField<jlong>(cls, "MAX_VALUE");
    QCOMPARE(i, jlong(9223372036854775807L));
}

void tst_QJNIObject::getStaticDoubleFieldClassName()
{
    jdouble i = QJNIObject::getStaticField<jdouble>("java/lang/Double", "NaN");
    jlong *k = reinterpret_cast<jlong*>(&i);
    QCOMPARE(*k, jlong(0x7ff8000000000000L));
}

void tst_QJNIObject::getStaticDoubleField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Double");
    QVERIFY(cls != 0);

    jdouble i = QJNIObject::getStaticField<jdouble>(cls, "NaN");
    jlong *k = reinterpret_cast<jlong*>(&i);
    QCOMPARE(*k, jlong(0x7ff8000000000000L));
}

void tst_QJNIObject::getStaticFloatFieldClassName()
{
    jfloat i = QJNIObject::getStaticField<jfloat>("java/lang/Float", "NaN");
    unsigned *k = reinterpret_cast<unsigned*>(&i);
    QCOMPARE(*k, unsigned(0x7fc00000));
}

void tst_QJNIObject::getStaticFloatField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Float");
    QVERIFY(cls != 0);

    jfloat i = QJNIObject::getStaticField<jfloat>(cls, "NaN");
    unsigned *k = reinterpret_cast<unsigned*>(&i);
    QCOMPARE(*k, unsigned(0x7fc00000));
}

void tst_QJNIObject::getStaticShortFieldClassName()
{
    jshort i = QJNIObject::getStaticField<jshort>("java/lang/Short", "MAX_VALUE");
    QCOMPARE(i, jshort(32767));
}

void tst_QJNIObject::getStaticShortField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Short");
    QVERIFY(cls != 0);

    jshort i = QJNIObject::getStaticField<jshort>(cls, "MAX_VALUE");
    QCOMPARE(i, jshort(32767));
}

void tst_QJNIObject::getStaticCharFieldClassName()
{
    jchar i = QJNIObject::getStaticField<jchar>("java/lang/Character", "MAX_VALUE");
    QCOMPARE(i, jchar(0xffff));
}

void tst_QJNIObject::getStaticCharField()
{
    QJNIEnvironment env;
    jclass cls = env->FindClass("java/lang/Character");
    QVERIFY(cls != 0);

    jchar i = QJNIObject::getStaticField<jchar>(cls, "MAX_VALUE");
    QCOMPARE(i, jchar(0xffff));
}


void tst_QJNIObject::getBooleanField()
{
    QVERIFY(m_activityDelegateClass);

    QJNIObject obj(m_activityDelegateClass);

    QVERIFY(obj.isValid());
    QVERIFY(!obj.getField<jboolean>("m_fullScreen"));
}

void tst_QJNIObject::getIntField()
{
    QVERIFY(m_activityDelegateClass);

    QJNIObject obj(m_activityDelegateClass);

    QVERIFY(obj.isValid());
    jint res = obj.getField<jint>("m_currentRotation");

    QCOMPARE(res, -1);
}

Q_DECL_EXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    typedef union {
        JNIEnv *nenv;
        void *venv;
    } _JNIEnv;

    _JNIEnv uenv;
    uenv.venv = Q_NULLPTR;

    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    JNIEnv *env = uenv.nenv;

    jclass clazz = env->FindClass("org/qtproject/qt5/android/QtActivityDelegate");
    tst_QJNIObject::m_activityDelegateClass = (jclass)env->NewGlobalRef(clazz);

    return JNI_VERSION_1_6;
}

QTEST_APPLESS_MAIN(tst_QJNIObject)

#include "tst_qjniobject.moc"
