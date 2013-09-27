/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
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

#include "qjniobject.h"
#include <QtCore/private/qjni_p.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

/*!
    \class QJNIObject
    \inmodule QtAndroidExtras
    \brief The QJNIObject is a C++ wrapper around a Java objects.
    \since 5.2

    QJNIObject provides APIs to call Java code from C++ by acting as a wrapper around a Java object.

    \section1 General Notes

    \list
    \li Class names needs to contain the fully-qualified class name, for example: \b"java/lang/String".
    \li Method signatures are written as \b"(Arguments)ReturnType"
    \li All object types are returned as a QJNIObject.
    \endlist

    \section1 Method signatures

    For functions that take no arguments QJNIObject provides convenience functions that will use
    the correct signature based on the provided template type, for example:

    \code
    jint x = QJNIObject::callMethod<jint>("getSize");
    QJNIObject::callMethod<void>("touch");
    \endcode

    In other cases you will need to supply the signature yourself, and it is important that the
    signature matches the function you want to call. The signature structure is \b \(A\)R, where \b A
    is the type of the argument\(s\) and \b R is the return type.
    Any types in the signature that are arrays needs to have the character \b\[ in front of them, in addition
    fully-qualified type names needs to be surrounded with \b L and \b ; at the start and end, respectively.

    The example below demonstrates how to call two different static functions.
    \code
    // Java class
    package org.qtproject.qt5;
    class TestClass
    {
       static String fromNumber(int x) { ... }
       static String[] stringArray(String s1, String s2) { ... }
    }
    \endcode

    The signature for the first function is \b"\(I\)Ljava/lang/String;"

    \code
    // C++ code
    QJNIObject stringNumber = QJNIObject::callStaticObjectMethod("org/qtproject/qt5/TestClass",
                                                                 "fromNumber"
                                                                 "(I)Ljava/lang/String;",
                                                                 10);
    \endcode

    and the signature for the second function is \b"\(Ljava/lang/String;Ljava/lang/String;\)\[Ljava/lang/String;"

    \code
    // C++ code
    QJNIObject string1 = QJNIObject::fromString("String1");
    QJNIObject string2 = QJNIObject::fromString("String2");
    QJNIObject stringArray = QJNIObject::callStaticObjectMethod("org/qtproject/qt5/TestClass",
                                                                "stringArray"
                                                                "(Ljava/lang/String;Ljava/lang/String;)[Ljava/lang/String;"
                                                                string1.object<jstring>(),
                                                                string2.object<jstring>());
    \endcode


    \section1 Handling Java exception

    When calling Java functions that might throw an exception, it is important that you check, handle
    and clear out the exception before continuing, it is unsafe to make a JNI call when there are
    exceptions pending.

    \snippet code/src_androidextras_qjniobject.cpp Check for exceptions

    \section1 Java native methods

    Java native methods makes it possible to call native code from Java, this is done by creating a
    function declaration in Java and prefixing it with the \b native keyword.
    Before a native function can be called from Java, you need to map the Java native function to a
    native function in your code. Mapping functions can be done by calling the RegisterNatives() function
    through the \l{QJNIEnvironment}{JNI environment pointer}.

    The example below demonstrates how the this could be done.

    Java implementation:
    \snippet code/src_androidextras_qjniobject.cpp Java native methods

    C++ Implementation:
    \snippet code/src_androidextras_qjniobject.cpp Registering native methods

    \section1 The lifetime of a Java object

    All \l{Object types}{Java objects} returned from a JNI call is by default a local references and
    will only stay valid in the scope it was returned in, afther that the object becomes eligible for
    garbage collection. If you want to keep a Java object alive you need to either create a new global
    reference to the object and release it when you are done, or construct a new QJNIObject and let
    it manage the lifetime of the Java object.
    \sa object()

    \note The QJNIObject does only manage it's own references, if you construct a QJNIObject from a
          global reference that reference will not be released by the QJNIObject.

    \section1 JNI types

    \section3 Object types
    \table
    \header
        \li Type
        \li Signature
    \row
        \li jobject
        \li {1, 3} L\e<fully-qulified-name>};
    \row
        \li jclass
    \row
        \li jstring
    \row
        \li jobjectArray
        \li [L\e<fully-qulified-name>;
    \row
        \li jarray
        \li [\e<type>
    \row
        \li jbooleanArray
        \li [Z
    \row
        \li jbyteArray
        \li [B
    \row
        \li jcharArray
        \li [C
    \row
        \li jshortArray
        \li [S
    \row
        \li jintArray
        \li [I
    \row
        \li jlongArray
        \li [J
    \row
        \li jfloatArray
        \li [F
    \row
        \li jdoubleArray
        \li [D
    \endtable


    \section3 Primitive types
    \table
    \header
        \li Type
        \li Signature
    \row
        \li jboolean
        \li Z
    \row
        \li jbyte
        \li B
    \row
        \li jchar
        \li C
    \row
       \li jshort
       \li S
    \row
        \li jint
        \li I
    \row
        \li jlong
        \li J
    \row
        \li jfloat
        \li F
    \row
        \li jdouble
        \li D
    \endtable

    \section3 Other
    \table
    \header
        \li Type
        \li Signature
    \row
        \li void
        \li V
    \endtable

    For more information about JNI see: \l http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html
*/

/*!
    \fn QJNIObject::QJNIObject()

    Constructs an invalid QJNIObject.

    \sa isValid()
*/

/*!
    \fn QJNIObject::QJNIObject(const char *className)

    Constructs a new QJNIObject by calling the default constructor of \a className.

    \code

    ...
    QJNIObject myJavaString("java/lang/String");
    ...

    \endcode
*/

/*!
    \fn QJNIObject::QJNIObject(const char *className, const char *signature, ...)

    Constructs a new QJNIObject by calling the constructor of \a className with \a signature
    and arguments.

    \code

    ...
    jstring myJStringArg = ...;
    QJNIObject myNewJavaString("java/lang/String", "(Ljava/lang/String;)V", myJStringArg);
    ...

    \endcode
*/

/*!
    \fn QJNIObject::QJNIObject(jclass clazz)

    Constructs a new QJNIObject by calling the default constructor of \a clazz.

    Note: The QJNIObject will create a new reference to the class \a clazz
          and releases it again when it is destroyed. References to the class created
          outside the QJNIObject needs to be managed by the caller.

*/

/*!
    \fn QJNIObject::QJNIObject(jclass clazz, const char *signature, ...)

    Constructs a new QJNIObject from \a clazz by calling the constructor with \a signature
    and arguments.

    \code
    jclass myClass = ...;
    QJNIObject::QJNIObject(myClazz, "(I)V", 3);
    \endcode
*/

/*!
    \fn QJNIObject::QJNIObject(jobject object)

    Constructs a new QJNIObject around the Java object \a object.

    Note: The QJNIObject will hold a reference to the Java object \a object
          and release it when destroyed. Any references to the Java object \a object
          outside QJNIObject needs to be managed by the caller.
*/

/*!
    \fn QJNIObject::~QJNIObject()

    Destroys the QJNIObject and releases any references held by the QJNIObject.
*/

/*!
    \fn T QJNIObject::callMethod(const char *methodName, const char *signature, ...) const

    Calls the method \a methodName with \a signature and returns the value.

    \code
    QJNIObject myJavaString = ...;
    jint index = myJavaString.callMethod<jint>("indexOf", "(I)I", 0x0051);
    \endcode

*/

/*!
    \fn T QJNIObject::callMethod(const char *methodName) const

    Calls the method \a methodName and returns the value.

    \code
    QJNIObject myJavaString = ...;
    jint size = myJavaString.callMethod<jint>("length");
    \endcode
*/

/*!
    \fn QJNIObject QJNIObject::callObjectMethod(const char *methodName) const

    Calls the Java objects method \a methodName and returns a new QJNIObject for
    the returned Java object.

    \code
    ...
    QJNIObject myJavaString1 = ...;
    QJNIObject myJavaString2 = myJavaString.callObjectMethod<jstring>("toString");
    ...
    \endcode
*/

/*!
    \fn QJNIObject QJNIObject::callObjectMethod(const char *methodName, const char *signature, ...) const

    Calls the Java object's method \a methodName with the signature \a signature and arguments

    \code
    QJNIObject myJavaString; ==> "Hello, Java"
    QJNIObject mySubstring = myJavaString.callObjectMethod<jstring>("substring", "(II)Ljava/lang/String;" 7, 10);
    \endcode
*/

/*!
    \fn T QJNIObject::callStaticMethod(jclass clazz, const char *methodName)

    Calls the static method \a methodName on \a clazz and returns the value.

    \code
    ...
    jclass javaMathClass = ...; // ("java/lang/Math")
    jdouble randNr = QJNIObject::callStaticMethod<jdouble>(javaMathClass, "random");
    ...
    \endcode
*/

/*!
    \fn T QJNIObject::callStaticMethod(const char *className, const char *methodName)

    Calls the static method \a methodName on class \a className and returns the value.

    \code
    jint value = QJNIObject::callStaticMethod<jint>("MyClass", "staticMethod");
    \endcode
*/

/*!
    \fn T QJNIObject::callStaticMethod(const char *className, const char *methodName, const char *signature, ...)

    Calls the static method with \a methodName with \a signature on class \a className with optional arguments.

    \code
    ...
    jint a = 2;
    jint b = 4;
    jint max = QJNIObject::callStaticMethod<jint>("java/lang/Math", "max", "(II)I", a, b);
    ...
    \endcode
*/

/*!
    \fn T QJNIObject::callStaticMethod(jclass clazz, const char *methodName, const char *signature, ...)

    Calls the static method \a methodName with \a signature on \a clazz and returns the value.

    \code
    ...
    jclass javaMathClass = ...; // ("java/lang/Math")
    jint a = 2;
    jint b = 4;
    jint max = QJNIObject::callStaticMethod<jint>(javaMathClass, "max", "(II)I", a, b);
    ...
    \endcode
*/

/*!
    \fn QJNIObject QJNIObject::callStaticObjectMethod(const char *className, const char *methodName)

    Calls the static method with \a methodName on the class \a className.

    \code
    QJNIObject string = QJNIObject::callStaticObjectMethod<jstring>("CustomClass", "getClassName");
    \endcode
*/

/*!
    \fn QJNIObject QJNIObject::callStaticObjectMethod(const char *className, const char *methodName, const char *signature, ...)

    Calls the static method with \a methodName and \a signature on the class \a className.

    \code
    QJNIObject thread = QJNIObject::callStaticObjectMethod("java/lang/Thread", "currentThread", "()Ljava/lang/Thread;");
    QJNIObject string = QJNIObject::callStaticObjectMethod("java/lang/String", "valueOf", "(I)Ljava/lang/String;", 10);
    \endcode
*/

/*!
    \fn QJNIObject QJNIObject::callStaticObjectMethod(jclass clazz, const char *methodName)

    Calls the static method with \a methodName on \a clazz.

*/

/*!
    \fn QJNIObject QJNIObject::callStaticObjectMethod(jclass clazz, const char *methodName, const char *signature, ...)

    Calls the static method with \a methodName and \a signature on class \a clazz.
*/

/*!
    \fn T QJNIObject::getField(const char *fieldName) const

    Retrieves the value of the field \a fieldName.

    \code
    QJNIObject volumeControll = ...;
    jint fieldValue = obj.getField<jint>("MAX_VOLUME");
    \endcode
*/

/*!
    \fn QJNIObject QJNIObject::getObjectField(const char *fieldName) const

    Retrieves the object of field \a fieldName.
*/

/*!
    \fn QJNIObject QJNIObject::getObjectField(const char *fieldName, const char *signature) const

    Retrieves the object from the field with \a signature and \a fieldName.
*/

/*!
    \fn T QJNIObject::getStaticField(const char *className, const char *fieldName)

    Retrieves the value from the static field \a fieldName on the class \a className.
*/

/*!
    \fn T QJNIObject::getStaticField(jclass clazz, const char *fieldName)

    Retrieves the value from the static field \a fieldName on \a clazz.
*/

/*!
    \fn QJNIObject QJNIObject::getStaticObjectField(const char *className, const char *fieldName)

    Retrieves the object from the field \a fieldName on the class \a className.
*/

/*!
    \fn QJNIObject QJNIObject::getStaticObjectField(const char *className, const char *fieldName, const char *signature)

    Retrieves the object from the field with \a signature and \a fieldName on class \a className.
*/

/*!
    \fn QJNIObject QJNIObject::getStaticObjectField(jclass clazz, const char *fieldName)

    Retrieves the object from the field \a fieldName on \a clazz.
*/

/*!
    \fn QJNIObject QJNIObject::getStaticObjectField(jclass clazz, const char *fieldName, const char *signature)

    Retrieves the object from the field with \a signature and \a fieldName on \a clazz.
*/

/*!
    \fn void QJNIObject::setField(const char *fieldName, T value)

    Sets the value of \a fieldName to \a value.

    \code
    ...
    QJNIObject obj;
    obj.setField<jint>("AN_INT_FIELD", 10);
    jstring myString = ...
    obj.setField<jstring>("A_STRING_FIELD", myString);
    ...
    \endcode
*/

/*!
    \fn void QJNIObject::setField(const char *fieldName, const char *signature, T value)

    Sets the value of \a fieldName with \a signature to \a value.

    \code
    QJNIObject stringArray = ...;
    QJNIObject obj = ...;
    obj.setField<jobjectArray>("KEY_VALUES", "([Ljava/lang/String;)V", stringArray.object<jobjectArray>())
    \endcode
*/

/*!
    \fn void QJNIObject::setStaticField(const char *className, const char *fieldName, T value)

    Sets the value of the static field \a fieldName in class \a className to \a value.
*/

/*!
    \fn void QJNIObject::setStaticField(const char *className, const char *fieldName, const char *signature, T value);

    Sets the static field with \a fieldName and \a signature to \a value on class \a className.
*/

/*!
    \fn void QJNIObject::setStaticField(jclass clazz, const char *fieldName, T value)

    Sets the static field \a fieldName of the class \a clazz to \a value.
*/

/*!
    \fn void QJNIObject::setStaticField(jclass clazz, const char *fieldName, const char *signature, T value);

    Sets the static field with \a fieldName and \a signature to \a value on class \a clazz.
*/

/*!
    \fn bool QJNIObject::isClassAvailable(const char *className)

    Returns true if the Java class \a className is available.

    \code
    ...
    if (QJNIObject::isClassAvailable("java/lang/String")) {
       ...
    }
    ...
    \endcode
*/

/*!
    \fn bool QJNIObject::isValid() const

    Returns true if this instance holds a valid Java object.

    \code
    ...
    QJNIObject qjniObject;                        ==> isValid() == false
    QJNIObject qjniObject(0)                      ==> isValid() == false
    QJNIObject qjniObject("could/not/find/Class") ==> isValid() == false
    ...
    \endcode
*/

/*!
    \fn T QJNIObject::object() const

    Returns the object held by the QJNIObject as type T.

    \code
    QJNIObject string = QJNIObject::fromString("Hello, JNI");
    jstring jstring = string.object<jstring>();
    \endcode

    Note that the jobject is still owned by the QJNIObject. If you want to keep the jobject valid
    you should create a new QJNIObject or make a new global reference to the jobject and
    free it yourself.

    \snippet code/src_androidextras_qjniobject.cpp QJNIObject scope
*/

/*!
    \fn QJNIObject &QJNIObject::operator=(T object)

    Replace the current object with \a object. The old Java object will be released.
*/

/*!
    \fn QString QJNIObject::toString() const

    Returns a QString with a string representation of the java object.
    Calling this function on a Java String object is a convenient way of getting the actual string
    data.

    \code
    QJNIObject string = ...; //  "Hello Java"
    QString qstring = string.toString(); // "Hello Java"
    \endcode

    \sa fromString()
*/

/*!
    \fn QJNIObject QJNIObject::fromString(const QString &string)

    Creates a Java string from the QString \a string and returns a QJNIObject holding that string.

    \code
    ...
    QString myQString = "QString";
    QJNIObject myJavaString = QJNIObject::fromString(myQString);
    ...
    \endcode

    \sa toString()
*/

/*!
    \fn bool operator==(const QJNIObject &o1, const QJNIObject &o2)
    \relates QJNIObject

    Returns true if both objects, \a o1 and \a o2, are referencing the same Java object, or if both
    are NULL. In any other cases false will be returned.
*/

/*!
    \fn bool operator==(const QJNIObject &o1, T o2)
    \relates QJNIObject

    Returns true if both objects, \a o1 and \a o2, are referencing the same Java object, or if both
    are NULL. In any other cases false will be returned.
*/

/*!
    \fn bool operator==(T o1, const QJNIObject &o2)
    \relates QJNIObject

    Returns true if both objects, \a o1 and \a o2, are referencing the same Java object, or if both
    are NULL. In any other cases false will be returned.
*/

/*!
    \fn bool operator!=(const QJNIObject &o1, const QJNIObject &o2)
    \relates QJNIObject

    Returns true if \a o1 holds a reference to a different object then \a o2.
*/

/*!
    \fn bool operator!=(const QJNIObject &o1, T o2)
    \relates QJNIObject

    Returns true if \a o1 holds a reference to a different object then \a o2.
*/

/*!
    \fn bool operator!=(T o1, const QJNIObject &o2)
    \relates QJNIObject

    Returns true if \a o1 is referencing a different object then \a o2.
*/


QJNIObject::QJNIObject(const char *className, const char *sig, ...)
{
    va_list args;
    va_start(args, sig);
    d = QSharedPointer<QJNIObjectPrivate>(new QJNIObjectPrivate(className, sig, args));
    va_end(args);
}

QJNIObject::QJNIObject(jclass clazz, const char *sig, ...)
{
    va_list args;
    va_start(args, sig);
    d = QSharedPointer<QJNIObjectPrivate>(new QJNIObjectPrivate(clazz, sig, args));
    va_end(args);
}


QJNIObject::QJNIObject() : d(new QJNIObjectPrivate)
{

}

QJNIObject::QJNIObject(const char *className) : d(new QJNIObjectPrivate(className))
{
}

QJNIObject::QJNIObject(jclass clazz) : d(new QJNIObjectPrivate(clazz))
{
}

QJNIObject::QJNIObject(jobject obj) : d(new QJNIObjectPrivate(obj))
{
}

QJNIObject::QJNIObject(const QJNIObjectPrivate &o) : d(new QJNIObjectPrivate(o))
{

}

template <>
void QJNIObject::callMethod<void>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    d->callMethod<void>(methodName, sig, args);
    va_end(args);
}

template <>
jboolean QJNIObject::callMethod<jboolean>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jboolean res = d->callMethod<jboolean>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jbyte QJNIObject::callMethod<jbyte>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jbyte res = d->callMethod<jbyte>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jchar QJNIObject::callMethod<jchar>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jchar res = d->callMethod<jchar>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jshort QJNIObject::callMethod<jshort>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jshort res = d->callMethod<jshort>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jint QJNIObject::callMethod<jint>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jint res = d->callMethod<jint>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jlong QJNIObject::callMethod<jlong>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jlong res = d->callMethod<jlong>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jfloat QJNIObject::callMethod<jfloat>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jfloat res = d->callMethod<jfloat>(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jdouble QJNIObject::callMethod<jdouble>(const char *methodName, const char *sig, ...) const
{
    va_list args;
    va_start(args, sig);
    jdouble res = d->callMethod<jdouble>(methodName, sig, args);
    va_end(args);
    return res;
}

QJNIObject QJNIObject::callObjectMethod(const char *methodName,
                                        const char *sig,
                                        ...) const
{
    va_list args;
    va_start(args, sig);
    QJNIObjectPrivate res = d->callObjectMethod(methodName, sig, args);
    va_end(args);
    return res;
}

template <>
void QJNIObject::callMethod<void>(const char *methodName) const
{
    callMethod<void>(methodName, "()V");
}

template <>
jboolean QJNIObject::callMethod<jboolean>(const char *methodName) const
{
    return callMethod<jboolean>(methodName, "()Z");
}

template <>
jbyte QJNIObject::callMethod<jbyte>(const char *methodName) const
{
    return callMethod<jbyte>(methodName, "()B");
}

template <>
jchar QJNIObject::callMethod<jchar>(const char *methodName) const
{
    return callMethod<jchar>(methodName, "()C");
}

template <>
jshort QJNIObject::callMethod<jshort>(const char *methodName) const
{
    return callMethod<jshort>(methodName, "()S");
}

template <>
jint QJNIObject::callMethod<jint>(const char *methodName) const
{
    return callMethod<jint>(methodName, "()I");
}

template <>
jlong QJNIObject::callMethod<jlong>(const char *methodName) const
{
    return callMethod<jlong>(methodName, "()J");
}

template <>
jfloat QJNIObject::callMethod<jfloat>(const char *methodName) const
{
    return callMethod<jfloat>(methodName, "()F");
}

template <>
jdouble QJNIObject::callMethod<jdouble>(const char *methodName) const
{
    return callMethod<jdouble>(methodName, "()D");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jstring>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()Ljava/lang/String;");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jbooleanArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[Z");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jbyteArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[B");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jshortArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[S");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jintArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[I");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jlongArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[J");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jfloatArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[F");
}

template <>
QJNIObject QJNIObject::callObjectMethod<jdoubleArray>(const char *methodName) const
{
    return d->callObjectMethod(methodName, "()[D");
}

template <>
void QJNIObject::callStaticMethod<void>(const char *className,
                                        const char *methodName,
                                        const char *sig,
                                        ...)
{
    va_list args;
    va_start(args, sig);
    QJNIObjectPrivate::callStaticMethod<void>(className, methodName, sig, args);
    va_end(args);
}

template <>
void QJNIObject::callStaticMethod<void>(jclass clazz,
                                        const char *methodName,
                                        const char *sig,
                                        ...)
{
    va_list args;
    va_start(args, sig);
    QJNIObjectPrivate::callStaticMethod<void>(clazz, methodName, sig, args);
    va_end(args);
}

template <>
jboolean QJNIObject::callStaticMethod<jboolean>(const char *className,
                                                const char *methodName,
                                                const char *sig,
                                                ...)
{
    va_list args;
    va_start(args, sig);
    jboolean res = QJNIObjectPrivate::callStaticMethod<jboolean>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jboolean QJNIObject::callStaticMethod<jboolean>(jclass clazz,
                                                const char *methodName,
                                                const char *sig,
                                                ...)
{
    va_list args;
    va_start(args, sig);
    jboolean res = QJNIObjectPrivate::callStaticMethod<jboolean>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jbyte QJNIObject::callStaticMethod<jbyte>(const char *className,
                                          const char *methodName,
                                          const char *sig,
                                          ...)
{
    va_list args;
    va_start(args, sig);
    jbyte res = QJNIObjectPrivate::callStaticMethod<jbyte>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jbyte QJNIObject::callStaticMethod<jbyte>(jclass clazz,
                                          const char *methodName,
                                          const char *sig,
                                          ...)
{
    va_list args;
    va_start(args, sig);
    jbyte res = QJNIObjectPrivate::callStaticMethod<jbyte>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jchar QJNIObject::callStaticMethod<jchar>(const char *className,
                                          const char *methodName,
                                          const char *sig,
                                          ...)
{
    va_list args;
    va_start(args, sig);
    jchar res = QJNIObjectPrivate::callStaticMethod<jchar>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jchar QJNIObject::callStaticMethod<jchar>(jclass clazz,
                                          const char *methodName,
                                          const char *sig,
                                          ...)
{
    va_list args;
    va_start(args, sig);
    jchar res = QJNIObjectPrivate::callStaticMethod<jchar>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}


template <>
jshort QJNIObject::callStaticMethod<jshort>(const char *className,
                                            const char *methodName,
                                            const char *sig,
                                            ...)
{
    va_list args;
    va_start(args, sig);
    jshort res = QJNIObjectPrivate::callStaticMethod<jshort>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jshort QJNIObject::callStaticMethod<jshort>(jclass clazz,
                                            const char *methodName,
                                            const char *sig,
                                            ...)
{
    va_list args;
    va_start(args, sig);
    jshort res = QJNIObjectPrivate::callStaticMethod<jshort>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jint QJNIObject::callStaticMethod<jint>(const char *className,
                                        const char *methodName,
                                        const char *sig,
                                        ...)
{
    va_list args;
    va_start(args, sig);
    jint res = QJNIObjectPrivate::callStaticMethod<jint>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jint QJNIObject::callStaticMethod<jint>(jclass clazz,
                                        const char *methodName,
                                        const char *sig,
                                        ...)
{
    va_list args;
    va_start(args, sig);
    jint res = QJNIObjectPrivate::callStaticMethod<jint>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jlong QJNIObject::callStaticMethod<jlong>(const char *className,
                                          const char *methodName,
                                          const char *sig,
                                          ...)
{
    va_list args;
    va_start(args, sig);
    jlong res = QJNIObjectPrivate::callStaticMethod<jlong>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jlong QJNIObject::callStaticMethod<jlong>(jclass clazz,
                                          const char *methodName,
                                          const char *sig,
                                          ...)
{
    va_list args;
    va_start(args, sig);
    jlong res = QJNIObjectPrivate::callStaticMethod<jlong>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jfloat QJNIObject::callStaticMethod<jfloat>(const char *className,
                                            const char *methodName,
                                            const char *sig,
                                            ...)
{
    va_list args;
    va_start(args, sig);
    jfloat res = QJNIObjectPrivate::callStaticMethod<jfloat>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jfloat QJNIObject::callStaticMethod<jfloat>(jclass clazz,
                                            const char *methodName,
                                            const char *sig,
                                            ...)
{
    va_list args;
    va_start(args, sig);
    jfloat res = QJNIObjectPrivate::callStaticMethod<jfloat>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jdouble QJNIObject::callStaticMethod<jdouble>(const char *className,
                                              const char *methodName,
                                              const char *sig,
                                              ...)
{
    va_list args;
    va_start(args, sig);
    jdouble res = QJNIObjectPrivate::callStaticMethod<jdouble>(className, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
jdouble QJNIObject::callStaticMethod<jdouble>(jclass clazz,
                                              const char *methodName,
                                              const char *sig,
                                              ...)
{
    va_list args;
    va_start(args, sig);
    jdouble res = QJNIObjectPrivate::callStaticMethod<jdouble>(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

QJNIObject QJNIObject::callStaticObjectMethod(const char *className,
                                              const char *methodName,
                                              const char *sig,
                                              ...)
{
    va_list args;
    va_start(args, sig);
    QJNIObjectPrivate res = QJNIObjectPrivate::callStaticObjectMethod(className,
                                                                      methodName,
                                                                      sig,
                                                                      args);
    va_end(args);
    return res;
}

QJNIObject QJNIObject::callStaticObjectMethod(jclass clazz,
                                              const char *methodName,
                                              const char *sig,
                                              ...)
{
    va_list args;
    va_start(args, sig);
    QJNIObjectPrivate res = QJNIObjectPrivate::callStaticObjectMethod(clazz, methodName, sig, args);
    va_end(args);
    return res;
}

template <>
void QJNIObject::callStaticMethod<void>(const char *className, const char *methodName)
{
    callStaticMethod<void>(className, methodName, "()V");
}

template <>
void QJNIObject::callStaticMethod<void>(jclass clazz, const char *methodName)
{
    callStaticMethod<void>(clazz, methodName, "()V");
}

template <>
jboolean QJNIObject::callStaticMethod<jboolean>(const char *className, const char *methodName)
{
    return callStaticMethod<jboolean>(className, methodName, "()Z");
}

template <>
jboolean QJNIObject::callStaticMethod<jboolean>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jboolean>(clazz, methodName, "()Z");
}

template <>
jbyte QJNIObject::callStaticMethod<jbyte>(const char *className, const char *methodName)
{
    return callStaticMethod<jbyte>(className, methodName, "()B");
}

template <>
jbyte QJNIObject::callStaticMethod<jbyte>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jbyte>(clazz, methodName, "()B");
}

template <>
jchar QJNIObject::callStaticMethod<jchar>(const char *className, const char *methodName)
{
    return callStaticMethod<jchar>(className, methodName, "()C");
}

template <>
jchar QJNIObject::callStaticMethod<jchar>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jchar>(clazz, methodName, "()C");
}

template <>
jshort QJNIObject::callStaticMethod<jshort>(const char *className, const char *methodName)
{
    return callStaticMethod<jshort>(className, methodName, "()S");
}

template <>
jshort QJNIObject::callStaticMethod<jshort>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jshort>(clazz, methodName, "()S");
}

template <>
jint QJNIObject::callStaticMethod<jint>(const char *className, const char *methodName)
{
    return callStaticMethod<jint>(className, methodName, "()I");
}

template <>
jint QJNIObject::callStaticMethod<jint>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jint>(clazz, methodName, "()I");
}

template <>
jlong QJNIObject::callStaticMethod<jlong>(const char *className, const char *methodName)
{
    return callStaticMethod<jlong>(className, methodName, "()J");
}

template <>
jlong QJNIObject::callStaticMethod<jlong>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jlong>(clazz, methodName, "()J");
}

template <>
jfloat QJNIObject::callStaticMethod<jfloat>(const char *className, const char *methodName)
{
    return callStaticMethod<jfloat>(className, methodName, "()F");
}

template <>
jfloat QJNIObject::callStaticMethod<jfloat>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jfloat>(clazz, methodName, "()F");
}

template <>
jdouble QJNIObject::callStaticMethod<jdouble>(const char *className, const char *methodName)
{
    return callStaticMethod<jdouble>(className, methodName, "()D");
}

template <>
jdouble QJNIObject::callStaticMethod<jdouble>(jclass clazz, const char *methodName)
{
    return callStaticMethod<jdouble>(clazz, methodName, "()D");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jstring>(const char *className,
                                                       const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()Ljava/lang/String;");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jstring>(jclass clazz,
                                                       const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()Ljava/lang/String;");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jbooleanArray>(const char *className,
                                                             const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[Z");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jbooleanArray>(jclass clazz,
                                                             const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[Z");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jbyteArray>(const char *className,
                                                          const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[B");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jbyteArray>(jclass clazz,
                                                          const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[B");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jcharArray>(const char *className,
                                                          const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[C");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jcharArray>(jclass clazz,
                                                          const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[C");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jshortArray>(const char *className,
                                                           const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[S");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jshortArray>(jclass clazz,
                                                           const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[S");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jintArray>(const char *className,
                                                         const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[I");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jintArray>(jclass clazz,
                                                         const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[I");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jlongArray>(const char *className,
                                                          const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[J");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jlongArray>(jclass clazz,
                                                          const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[J");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jfloatArray>(const char *className,
                                                           const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[F");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jfloatArray>(jclass clazz,
                                                           const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[F");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jdoubleArray>(const char *className,
                                                            const char *methodName)
{
    return callStaticObjectMethod(className, methodName, "()[D");
}

template <>
QJNIObject QJNIObject::callStaticObjectMethod<jdoubleArray>(jclass clazz,
                                                            const char *methodName)
{
    return callStaticObjectMethod(clazz, methodName, "()[D");
}

template <>
jboolean QJNIObject::getField<jboolean>(const char *fieldName) const
{
    return d->getField<jboolean>(fieldName);
}

template <>
jbyte QJNIObject::getField<jbyte>(const char *fieldName) const
{
    return d->getField<jbyte>(fieldName);
}

template <>
jchar QJNIObject::getField<jchar>(const char *fieldName) const
{
    return d->getField<jchar>(fieldName);
}

template <>
jshort QJNIObject::getField<jshort>(const char *fieldName) const
{
    return d->getField<jshort>(fieldName);
}

template <>
jint QJNIObject::getField<jint>(const char *fieldName) const
{
    return d->getField<jint>(fieldName);
}

template <>
jlong QJNIObject::getField<jlong>(const char *fieldName) const
{
    return d->getField<jlong>(fieldName);
}

template <>
jfloat QJNIObject::getField<jfloat>(const char *fieldName) const
{
    return d->getField<jfloat>(fieldName);
}

template <>
jdouble QJNIObject::getField<jdouble>(const char *fieldName) const
{
    return d->getField<jdouble>(fieldName);
}

template <>
QJNIObject QJNIObject::getObjectField<jobject>(const char *fieldName, const char *sig) const
{
    return d->getObjectField(fieldName, sig);
}

template <>
QJNIObject QJNIObject::getObjectField<jbooleanArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[Z");
}

template <>
QJNIObject QJNIObject::getObjectField<jbyteArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[B");
}

template <>
QJNIObject QJNIObject::getObjectField<jcharArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[C");
}

template <>
QJNIObject QJNIObject::getObjectField<jshortArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[S");
}

template <>
QJNIObject QJNIObject::getObjectField<jintArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[I");
}

template <>
QJNIObject QJNIObject::getObjectField<jlongArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[J");
}

template <>
QJNIObject QJNIObject::getObjectField<jfloatArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[F");
}

template <>
QJNIObject QJNIObject::getObjectField<jdoubleArray>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "[D");
}

template <>
QJNIObject QJNIObject::getObjectField<jstring>(const char *fieldName) const
{
    return d->getObjectField(fieldName, "Ljava/lang/String;");
}

template <>
QJNIObject QJNIObject::getObjectField<jobjectArray>(const char *fieldName,
                                                    const char *sig) const
{
    return d->getObjectField(fieldName, sig);
}

template <>
void QJNIObject::setField<jboolean>(const char *fieldName, jboolean value)
{
    d->setField<jboolean>(fieldName, value);
}

template <>
void QJNIObject::setField<jbyte>(const char *fieldName, jbyte value)
{
    d->setField<jbyte>(fieldName, value);
}

template <>
void QJNIObject::setField<jchar>(const char *fieldName, jchar value)
{
    d->setField<jchar>(fieldName, value);
}

template <>
void QJNIObject::setField<jshort>(const char *fieldName, jshort value)
{
    d->setField<jshort>(fieldName, value);
}

template <>
void QJNIObject::setField<jint>(const char *fieldName, jint value)
{
    d->setField<jint>(fieldName, value);
}

template <>
void QJNIObject::setField<jlong>(const char *fieldName, jlong value)
{
    d->setField<jlong>(fieldName, value);
}

template <>
void QJNIObject::setField<jfloat>(const char *fieldName, jfloat value)
{
    d->setField<jfloat>(fieldName, value);
}

template <>
void QJNIObject::setField<jdouble>(const char *fieldName, jdouble value)
{
    d->setField<jdouble>(fieldName, value);
}

template <>
void QJNIObject::setField<jbooleanArray>(const char *fieldName, jbooleanArray value)
{
    d->setField<jbooleanArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jbyteArray>(const char *fieldName, jbyteArray value)
{
    d->setField<jbyteArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jcharArray>(const char *fieldName, jcharArray value)
{
    d->setField<jcharArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jshortArray>(const char *fieldName, jshortArray value)
{
    d->setField<jshortArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jintArray>(const char *fieldName, jintArray value)
{
    d->setField<jintArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jlongArray>(const char *fieldName, jlongArray value)
{
    d->setField<jlongArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jfloatArray>(const char *fieldName, jfloatArray value)
{
    d->setField<jfloatArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jdoubleArray>(const char *fieldName, jdoubleArray value)
{
    d->setField<jdoubleArray>(fieldName, value);
}

template <>
void QJNIObject::setField<jstring>(const char *fieldName, jstring value)
{
    d->setField<jstring>(fieldName, value);
}

template <>
void QJNIObject::setField<jobject>(const char *fieldName,
                                   const char *sig,
                                   jobject value)
{
    d->setField<jobject>(fieldName, sig, value);
}

template <>
void QJNIObject::setField<jobjectArray>(const char *fieldName,
                                        const char *sig,
                                        jobjectArray value)
{
    d->setField<jobjectArray>(fieldName, sig, value);
}

template <>
jboolean QJNIObject::getStaticField<jboolean>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jboolean>(clazz, fieldName);
}

template <>
jboolean QJNIObject::getStaticField<jboolean>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jboolean>(className, fieldName);
}

template <>
jbyte QJNIObject::getStaticField<jbyte>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jbyte>(clazz, fieldName);
}

template <>
jbyte QJNIObject::getStaticField<jbyte>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jbyte>(className, fieldName);
}

template <>
jchar QJNIObject::getStaticField<jchar>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jchar>(clazz, fieldName);
}

template <>
jchar QJNIObject::getStaticField<jchar>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jchar>(className, fieldName);
}

template <>
jshort QJNIObject::getStaticField<jshort>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jshort>(clazz, fieldName);
}

template <>
jshort QJNIObject::getStaticField<jshort>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jshort>(className, fieldName);
}

template <>
jint QJNIObject::getStaticField<jint>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jint>(clazz, fieldName);
}

template <>
jint QJNIObject::getStaticField<jint>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jint>(className, fieldName);
}

template <>
jlong QJNIObject::getStaticField<jlong>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jlong>(clazz, fieldName);
}

template <>
jlong QJNIObject::getStaticField<jlong>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jlong>(className, fieldName);
}

template <>
jfloat QJNIObject::getStaticField<jfloat>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jfloat>(clazz, fieldName);
}

template <>
jfloat QJNIObject::getStaticField<jfloat>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jfloat>(className, fieldName);
}

template <>
jdouble QJNIObject::getStaticField<jdouble>(jclass clazz, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jdouble>(clazz, fieldName);
}

template <>
jdouble QJNIObject::getStaticField<jdouble>(const char *className, const char *fieldName)
{
    return QJNIObjectPrivate::getStaticField<jdouble>(className, fieldName);
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jobject>(jclass clazz,
                                                     const char *fieldName,
                                                     const char *sig)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, sig);
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jobject>(const char *className,
                                                     const char *fieldName,
                                                     const char *sig)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, sig);
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jstring>(jclass clazz,
                                                     const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "Ljava/lang/String;");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jstring>(const char *className,
                                                     const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "Ljava/lang/String;");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jbooleanArray>(jclass clazz,
                                                           const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[Z");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jbooleanArray>(const char *className,
                                                           const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[Z");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jbyteArray>(jclass clazz,
                                                        const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[B");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jbyteArray>(const char *className,
                                                        const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[B");;
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jcharArray>(jclass clazz,
                                                        const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[C");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jcharArray>(const char *className,
                                                        const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[C");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jshortArray>(jclass clazz,
                                                         const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[S");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jshortArray>(const char *className,
                                                         const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[S");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jintArray>(jclass clazz,
                                                       const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[I");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jintArray>(const char *className,
                                                       const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[I");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jlongArray>(jclass clazz,
                                                        const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[J");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jlongArray>(const char *className,
                                                        const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[J");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jfloatArray>(jclass clazz,
                                                         const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[F");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jfloatArray>(const char *className,
                                                         const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[F");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jdoubleArray>(jclass clazz,
                                                          const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, "[D");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jdoubleArray>(const char *className,
                                                          const char *fieldName)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, "[D");
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jobjectArray>(jclass clazz,
                                                          const char *fieldName,
                                                          const char *sig)
{
    return QJNIObjectPrivate::getStaticObjectField(clazz, fieldName, sig);
}

template <>
QJNIObject QJNIObject::getStaticObjectField<jobjectArray>(const char *className,
                                                          const char *fieldName,
                                                          const char *sig)
{
    return QJNIObjectPrivate::getStaticObjectField(className, fieldName, sig);
}

template <>
void QJNIObject::setStaticField<jboolean>(jclass clazz, const char *fieldName, jboolean value)
{
    QJNIObjectPrivate::setStaticField<jboolean>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jboolean>(const char *className,
                                          const char *fieldName,
                                          jboolean value)
{
    QJNIObjectPrivate::setStaticField<jboolean>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jbyte>(jclass clazz, const char *fieldName, jbyte value)
{
    QJNIObjectPrivate::setStaticField<jbyte>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jbyte>(const char *className,
                                       const char *fieldName,
                                       jbyte value)
{
    QJNIObjectPrivate::setStaticField<jbyte>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jchar>(jclass clazz, const char *fieldName, jchar value)
{
    QJNIObjectPrivate::setStaticField<jchar>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jchar>(const char *className,
                                       const char *fieldName,
                                       jchar value)
{
    QJNIObjectPrivate::setStaticField<jchar>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jshort>(jclass clazz, const char *fieldName, jshort value)
{
    QJNIObjectPrivate::setStaticField<jshort>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jshort>(const char *className,
                                        const char *fieldName,
                                        jshort value)
{
    QJNIObjectPrivate::setStaticField<jshort>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jint>(jclass clazz, const char *fieldName, jint value)
{
    QJNIObjectPrivate::setStaticField<jint>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jint>(const char *className, const char *fieldName, jint value)
{
    QJNIObjectPrivate::setStaticField<jint>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jlong>(jclass clazz, const char *fieldName, jlong value)
{
    QJNIObjectPrivate::setStaticField<jlong>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jlong>(const char *className,
                                       const char *fieldName,
                                       jlong value)
{
    QJNIObjectPrivate::setStaticField<jlong>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jfloat>(jclass clazz, const char *fieldName, jfloat value)
{
    QJNIObjectPrivate::setStaticField<jfloat>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jfloat>(const char *className,
                                        const char *fieldName,
                                        jfloat value)
{
    QJNIObjectPrivate::setStaticField<jfloat>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jdouble>(jclass clazz, const char *fieldName, jdouble value)
{
    QJNIObjectPrivate::setStaticField<jdouble>(clazz, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jdouble>(const char *className,
                                         const char *fieldName,
                                         jdouble value)
{
    QJNIObjectPrivate::setStaticField<jdouble>(className, fieldName, value);
}

template <>
void QJNIObject::setStaticField<jobject>(jclass clazz,
                                         const char *fieldName,
                                         const char *sig,
                                         jobject value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, sig, value);
}

template <>
void QJNIObject::setStaticField<jobject>(const char *className,
                                         const char *fieldName,
                                         const char *sig,
                                         jobject value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, sig, value);
}

template <>
void QJNIObject::setStaticField<jstring>(const char *className,
                                         const char *fieldName,
                                         jstring value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "Ljava/lang/String;", value);
}

template <>
void QJNIObject::setStaticField<jstring>(jclass clazz, const char *fieldName, jstring value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "Ljava/lang/String;", value);
}

template <>
void QJNIObject::setStaticField<jbooleanArray>(const char *className,
                                               const char *fieldName,
                                               jbooleanArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[Z", value);
}

template <>
void QJNIObject::setStaticField<jbooleanArray>(jclass clazz,
                                               const char *fieldName,
                                               jbooleanArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[Z", value);
}

template <>
void QJNIObject::setStaticField<jbyteArray>(const char *className,
                                            const char *fieldName,
                                            jbyteArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[B", value);
}

template <>
void QJNIObject::setStaticField<jbyteArray>(jclass clazz,
                                            const char *fieldName,
                                            jbyteArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[B", value);
}

template <>
void QJNIObject::setStaticField<jcharArray>(const char *className,
                                            const char *fieldName,
                                            jcharArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[C", value);
}

template <>
void QJNIObject::setStaticField<jcharArray>(jclass clazz,
                                            const char *fieldName,
                                            jcharArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[C", value);
}

template <>
void QJNIObject::setStaticField<jshortArray>(const char *className,
                                             const char *fieldName,
                                             jshortArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[S", value);
}

template <>
void QJNIObject::setStaticField<jshortArray>(jclass clazz,
                                             const char *fieldName,
                                             jshortArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[S", value);
}

template <>
void QJNIObject::setStaticField<jintArray>(const char *className,
                                           const char *fieldName,
                                           jintArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[I", value);
}

template <>
void QJNIObject::setStaticField<jintArray>(jclass clazz,
                                           const char *fieldName,
                                           jintArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[I", value);
}

template <>
void QJNIObject::setStaticField<jlongArray>(const char *className,
                                            const char *fieldName,
                                            jlongArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[J", value);
}

template <>
void QJNIObject::setStaticField<jlongArray>(jclass clazz,
                                            const char *fieldName,
                                            jlongArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[J", value);
}

template <>
void QJNIObject::setStaticField<jfloatArray>(const char *className,
                                             const char *fieldName,
                                             jfloatArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[F", value);
}

template <>
void QJNIObject::setStaticField<jfloatArray>(jclass clazz,
                                             const char *fieldName,
                                             jfloatArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[F", value);
}

template <>
void QJNIObject::setStaticField<jdoubleArray>(const char *className,
                                              const char *fieldName,
                                              jdoubleArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(className, fieldName, "[D", value);
}

template <>
void QJNIObject::setStaticField<jdoubleArray>(jclass clazz,
                                              const char *fieldName,
                                              jdoubleArray value)
{
    QJNIObjectPrivate::setStaticField<jobject>(clazz, fieldName, "[D", value);
}

QJNIObject QJNIObject::fromString(const QString &string)
{
    return QJNIObjectPrivate::fromString(string);
}

QString QJNIObject::toString() const
{
    return d->toString();
}

bool QJNIObject::isClassAvailable(const char *className)
{
    return QJNIObjectPrivate::isClassAvailable(className);
}

bool QJNIObject::isValid() const
{
    return d->isValid();
}

jobject QJNIObject::javaObject() const
{
    return d->object();
}

bool QJNIObject::isSameObject(jobject obj) const
{
    return d->isSameObject(obj);
}

bool QJNIObject::isSameObject(const QJNIObject &obj) const
{
    return d->isSameObject(*obj.d);
}

void QJNIObject::assign(jobject o)
{
    if (d->isSameObject(o))
        return;

    d = QSharedPointer<QJNIObjectPrivate>(new QJNIObjectPrivate(o));
}

QT_END_NAMESPACE
