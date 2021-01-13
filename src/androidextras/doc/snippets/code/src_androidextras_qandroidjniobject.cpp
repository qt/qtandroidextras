/****************************************************************************
 **
 ** Copyright (C) 2021 The Qt Company Ltd.
 ** Contact: https://www.qt.io/licensing/
 **
 ** This file is part of the documentation of the Qt Toolkit.
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
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **********************************************************************/

//! [Working with lists]
QStringList getTrackTitles(const QAndroidJniObject &album) {
    QStringList stringList;
    QAndroidJniObject list = album.callObjectMethod("getTitles",
                                                      "()Ljava/util/List;");

    if (list.isValid()) {
        const int size = list.callMethod<jint>("size");
        for (int i = 0; i < size; ++i) {
            QAndroidJniObject title = list.callObjectMethod("get", "(I)Ljava/lang/Object;", i);
            stringList.append(title.toString());
        }
    }
    return stringList;
}
//! [Working with lists]

//! [QAndroidJniObject scope]
void functionScope()
{
    QString helloString("Hello");
    jstring myJString = 0;
    {
        QAndroidJniObject string = QAndroidJniObject::fromString(helloString);
        myJString = string.object<jstring>();
    }

   // Ops! myJString is no longer valid.
}
//! [QAndroidJniObject scope]

//! [Check for exceptions]
void functionException()
{
    QAndroidJniObject myString = QAndroidJniObject::fromString("Hello");
    jchar c = myString.callMethod<jchar>("charAt", "(I)C", 1000);
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck()) {
        // Handle exception here.
        env->ExceptionClear();
    }
}
//! [Check for exceptions]

//! [Registering native methods]
static void fromJavaOne(JNIEnv *env, jobject thiz, jint x)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    qDebug() << x << "< 100";
}

static void fromJavaTwo(JNIEnv *env, jobject thiz, jint x)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)
    qDebug() << x << ">= 100";
}

void registerNativeMethods() {
    JNINativeMethod methods[] {{"callNativeOne", "(I)V", reinterpret_cast<void *>(fromJavaOne)},
                               {"callNativeTwo", "(I)V", reinterpret_cast<void *>(fromJavaTwo)}};

    QAndroidJniObject javaClass("my/java/project/FooJavaClass");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void foo()
{
    QAndroidJniObject::callStaticMethod<void>("my/java/project/FooJavaClass", "foo", "(I)V", 10);  // Output: 10 < 100
    QAndroidJniObject::callStaticMethod<void>("my/java/project/FooJavaClass", "foo", "(I)V", 100); // Output: 100 >= 100
}

//! [Registering native methods]

//! [Java native methods]
class FooJavaClass
{
    public static void foo(int x)
    {
        if (x < 100)
            callNativeOne(x);
        else
            callNativeTwo(x);
    }

private static native void callNativeOne(int x);
private static native void callNativeTwo(int x);

}
//! [Java native methods]
