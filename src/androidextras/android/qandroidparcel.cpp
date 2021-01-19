/****************************************************************************
**
** Copyright (C) 2017 BogDan Vatra <bogdan@kde.org>
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

#include "qandroidparcel.h"

#include "qandroidbinder.h"
#include "qandroidbinder_p.h"
#include "qandroidparcel_p.h"

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QBuffer>
#include <QDataStream>
#include <QVariant>

QT_BEGIN_NAMESPACE

struct FileDescriptor
{
    explicit FileDescriptor(int fd = -1)
        : handle("java/io/FileDescriptor")
    {
        QAndroidJniExceptionCleaner cleaner;
        setFileDescriptor(fd);
    }

    inline void setFileDescriptor(int fd)
    {
        QAndroidJniExceptionCleaner cleaner;
        handle.setField("descriptor", fd);
    }

    QAndroidJniObject handle;
};

QAndroidParcelPrivate::QAndroidParcelPrivate()
    : handle(QAndroidJniObject::callStaticObjectMethod("android/os/Parcel","obtain", "()Landroid/os/Parcel;").object())
{}

QAndroidParcelPrivate::QAndroidParcelPrivate(const QAndroidJniObject &parcel)
    : handle(parcel)
{}

void QAndroidParcelPrivate::writeData(const QByteArray &data) const
{
    if (data.isEmpty())
        return;

    QAndroidJniExceptionCleaner cleaner;
    QAndroidJniEnvironment env;
    jbyteArray array = env->NewByteArray(data.size());
    env->SetByteArrayRegion(array, 0, data.length(), reinterpret_cast<const jbyte*>(data.constData()));
    handle.callMethod<void>("writeByteArray", "([B)V", array);
    env->DeleteLocalRef(array);
}

void QAndroidParcelPrivate::writeBinder(const QAndroidBinder &binder) const
{
    QAndroidJniExceptionCleaner cleaner;
    handle.callMethod<void>("writeStrongBinder", "(Landroid/os/IBinder;)V", binder.handle().object());
}

void QAndroidParcelPrivate::writeFileDescriptor(int fd) const
{
    QAndroidJniExceptionCleaner cleaner;
    handle.callMethod<void>("writeFileDescriptor", "(Ljava/io/FileDescriptor;)V", FileDescriptor(fd).handle.object());
}

QByteArray QAndroidParcelPrivate::readData() const
{
    QAndroidJniExceptionCleaner cleaner;
    auto array = handle.callObjectMethod("createByteArray", "()[B");
    QAndroidJniEnvironment env;
    auto sz = env->GetArrayLength(jbyteArray(array.object()));
    QByteArray res(sz, Qt::Initialization::Uninitialized);
    env->GetByteArrayRegion(jbyteArray(array.object()), 0, sz, reinterpret_cast<jbyte *>(res.data()));
    return res;
}

int QAndroidParcelPrivate::readFileDescriptor() const
{
    QAndroidJniExceptionCleaner cleaner;
    auto parcelFD = handle.callObjectMethod("readFileDescriptor", "()Landroid/os/ParcelFileDescriptor;");
    if (parcelFD.isValid())
        return parcelFD.callMethod<jint>("getFd", "()I");
    return -1;
}

QAndroidBinder QAndroidParcelPrivate::readBinder() const
{
    QAndroidJniExceptionCleaner cleaner;
    auto strongBinder = handle.callObjectMethod("readStrongBinder", "()Landroid/os/IBinder;");
    return QAndroidBinder(strongBinder.object());
}

/*!
    \class QAndroidParcel
    \inmodule QtAndroidExtras
    \brief Wraps the most important methods of Android Parcel class.

    The QAndroidParcel is a convenience class that wraps the most important
    \l {https://developer.android.com/reference/android/os/Parcel.html}{Android Parcel}
    methods.

    \since 5.10
*/

/*!
    Creates a new object.
 */
QAndroidParcel::QAndroidParcel()
    : d(new QAndroidParcelPrivate())
{
}

/*!
    Wraps the \a parcel object.
 */
QAndroidParcel::QAndroidParcel(const QAndroidJniObject& parcel)
    : d(new QAndroidParcelPrivate(parcel))
{

}

QAndroidParcel::~QAndroidParcel()
{
}

/*!
    Writes the provided \a data as a byte array
 */
void QAndroidParcel::writeData(const QByteArray &data) const
{
    d->writeData(data);
}

/*!
    Writes the provided \a value. The value is converted into a
    QByteArray before is written.
 */
void QAndroidParcel::writeVariant(const QVariant &value) const
{
    QByteArray buff;
    QDataStream stream(&buff, QIODevice::WriteOnly);
    stream << value;
    d->writeData(buff);
}

/*!
    Writes a \a binder object. This is useful for a client to
    send to a server a binder which can be used by the server callback the client.
 */
void QAndroidParcel::writeBinder(const QAndroidBinder &binder) const
{
    d->writeBinder(binder);
}

/*!
    Writes the provided \a fd.
 */
void QAndroidParcel::writeFileDescriptor(int fd) const
{
    d->writeFileDescriptor(fd);
}

/*!
    Returns the data as a QByteArray
 */
QByteArray QAndroidParcel::readData() const
{
    return d->readData();
}

/*!
    Returns the data as a QVariant
 */
QVariant QAndroidParcel::readVariant() const
{
    QDataStream stream(d->readData());
    QVariant res;
    stream >> res;
    return res;
}

/*!
    Returns the binder as a QAndroidBinder
 */
QAndroidBinder QAndroidParcel::readBinder() const
{
    return d->readBinder();
}

/*!
    Returns the file descriptor
 */
int QAndroidParcel::readFileDescriptor() const
{
    return d->readFileDescriptor();
}

/*!
    The return value is useful to call other Java API which are not covered by this wrapper
 */
QAndroidJniObject QAndroidParcel::handle() const
{
    return d->handle;
}

QT_END_NAMESPACE
