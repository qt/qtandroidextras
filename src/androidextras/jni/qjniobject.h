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

#ifndef QJNIOBJECT_H
#define QJNIOBJECT_H

#include <jni.h>
#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QtCore/qglobal.h>
#include <QtCore/qsharedpointer.h>

QT_BEGIN_NAMESPACE

class QJNIObjectPrivate;

class Q_ANDROIDEXTRAS_EXPORT QJNIObject
{
public:
    QJNIObject();
    explicit QJNIObject(const char *className);
    QJNIObject(const char *className, const char *sig, ...);
    explicit QJNIObject(jclass clazz);
    QJNIObject(jclass clazz, const char *sig, ...);
    QJNIObject(jobject obj);
    ~QJNIObject() { }

    template <typename T>
    inline T object() const { return static_cast<T>(javaObject()); }

    template <typename T>
    T callMethod(const char *methodName) const;
    template <typename T>
    T callMethod(const char *methodName, const char *sig, ...) const;
    template <typename T>
    QJNIObject callObjectMethod(const char *methodName) const;
    QJNIObject callObjectMethod(const char *methodName,
                                const char *sig,
                                ...) const;

    template <typename T>
    static T callStaticMethod(const char *className, const char *methodName);
    template <typename T>
    static T callStaticMethod(const char *className, const char *methodName, const char *sig, ...);
    template <typename T>
    static QJNIObject callStaticObjectMethod(const char *className, const char *methodName);
    static QJNIObject callStaticObjectMethod(const char *className,
                                             const char *methodName,
                                             const char *sig, ...);
    template <typename T>
    static T callStaticMethod(jclass clazz, const char *methodName);
    template <typename T>
    static T callStaticMethod(jclass clazz, const char *methodName, const char *sig, ...);
    template <typename T>
    static QJNIObject callStaticObjectMethod(jclass clazz, const char *methodName);
    static QJNIObject callStaticObjectMethod(jclass clazz,
                                             const char *methodName,
                                             const char *sig, ...);
    template <typename T>
    T getField(const char *fieldName) const;
    template <typename T>
    QJNIObject getObjectField(const char *fieldName) const;
    template <typename T>
    QJNIObject getObjectField(const char *fieldName, const char *sig) const;
    template <typename T>
    void setField(const char *fieldName, T value);
    template <typename T>
    void setField(const char *fieldName, const char *sig, T value);
    template <typename T>
    static QJNIObject getStaticObjectField(const char *className, const char *fieldName);
    template <typename T>
    static QJNIObject getStaticObjectField(const char *className,
                                           const char *fieldName,
                                           const char *sig);
    template <typename T>
    static T getStaticField(const char *className, const char *fieldName);
    template <typename T>
    static QJNIObject getStaticObjectField(jclass clazz, const char *fieldName);
    template <typename T>
    static QJNIObject getStaticObjectField(jclass clazz,
                                           const char *fieldName,
                                           const char *sig);
    template <typename T>
    static T getStaticField(jclass clazz, const char *fieldName);

    template <typename T>
    static void setStaticField(const char *className,
                               const char *fieldName,
                               const char *sig,
                               T value);
    template <typename T>
    static void setStaticField(const char *className, const char *fieldName, T value);
    template <typename T>
    static void setStaticField(jclass clazz, const char *fieldName, const char *sig, T value);
    template <typename T>
    static void setStaticField(jclass clazz, const char *fieldName, T value);

    static QJNIObject fromString(const QString &string);
    QString toString() const;

    static bool isClassAvailable(const char *className);
    bool isValid() const;

    template <typename T>
    inline QJNIObject &operator=(T o)
    {
        assign(static_cast<jobject>(o));
        return *this;
    }

private:
    friend bool operator==(const QJNIObject &, const QJNIObject &);
    friend bool operator!=(const QJNIObject &, const QJNIObject &);
    template <typename T> friend bool operator!=(const QJNIObject &, T);
    template <typename T> friend bool operator==(const QJNIObject &, T);
    template <typename T> friend bool operator!=(T, const QJNIObject &);
    template <typename T> friend bool operator==(T, const QJNIObject &);

    QJNIObject(const QJNIObjectPrivate &o);

    void assign(jobject o);
    jobject javaObject() const;
    bool isSameObject(jobject obj) const;
    bool isSameObject(const QJNIObject &obj) const;

    QSharedPointer<QJNIObjectPrivate> d;
};

inline bool operator==(const QJNIObject &obj1, const QJNIObject &obj2)
{
    return obj1.isSameObject(obj2);
}

inline bool operator!=(const QJNIObject &obj1, const QJNIObject &obj2)
{
    return !obj1.isSameObject(obj2);
}

template <typename T>
inline bool operator==(const QJNIObject &obj1, T obj2)
{
    return obj1.isSameObject(static_cast<jobject>(obj2));
}

template <typename T>
inline bool operator==(T obj1, const QJNIObject &obj2)
{
    return obj2.isSameObject(static_cast<jobject>(obj1));
}

template <typename T>
inline bool operator!=(const QJNIObject &obj1, T obj2)
{
    return !obj1.isSameObject(static_cast<jobject>(obj2));
}

template <typename T>
inline bool operator!=(T obj1, const QJNIObject &obj2)
{
    return !obj2.isSameObject(static_cast<jobject>(obj1));
}

QT_END_NAMESPACE

#endif // QJNIOBJECT_H
