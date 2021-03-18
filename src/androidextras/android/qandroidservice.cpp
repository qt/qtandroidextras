/****************************************************************************
**
** Copyright (C) 2021 BogDan Vatra <bogdan@kde.org>
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

#include "qandroidservice.h"

#include "qandroidintent.h"
#include "qandroidbinder.h"
#include "qandroidbinder_p.h"

#include <private/qjnihelpers_p.h>

#include <QMutex>
#include <QTimer>
#include <QSet>

QT_BEGIN_NAMESPACE

class QAndroidServicePrivate : public QObject, public QtAndroidPrivate::OnBindListener
{
public:
    QAndroidServicePrivate(QAndroidService *service, const std::function<QAndroidBinder *(const QAndroidIntent &)> &binder = {})
        : m_service(service)
        , m_binder(binder)
    {
        QTimer::singleShot(0,this, [this]{ QtAndroidPrivate::setOnBindListener(this);});
    }

    ~QAndroidServicePrivate()
    {
        QMutexLocker lock(&m_bindersMutex);
        while (!m_binders.empty()) {
            auto it = m_binders.begin();
            lock.unlock();
            delete (*it);
            lock.relock();
        }
    }

    // OnBindListener interface
    jobject onBind(jobject intent) override
    {
        auto qai = QAndroidIntent(intent);
        auto binder = m_binder ? m_binder(qai) : m_service->onBind(qai);
        if (binder) {
            {
                QMutexLocker lock(&m_bindersMutex);
                binder->d->setDeleteListener([this, binder]{binderDestroied(binder);});
                m_binders.insert(binder);
            }
            return binder->handle().object();
        }
        return nullptr;
    }

private:
    void binderDestroied(QAndroidBinder* obj)
    {
        QMutexLocker lock(&m_bindersMutex);
        m_binders.remove(obj);
    }

public:
    QAndroidService *m_service = nullptr;
    std::function<QAndroidBinder *(const QAndroidIntent &)> m_binder;
    QMutex m_bindersMutex;
    QSet<QAndroidBinder*> m_binders;
};

/*!
    \class QAndroidService
    \inmodule QtAndroidExtras
    \brief Wraps the most important methods of Android Service class.

    The QAndroidService is a convenience class that wraps the most important
    \l {https://developer.android.com/reference/android/app/Service.html}{Android Service}
    methods.

    \since 5.10
*/


/*!
    \fn QAndroidService::QAndroidService(int &argc, char **argv)

    Creates a new Android service, passing \a argc and \a argv as parameters.

    //! Parameter \a flags is omitted in the documentation.

    \sa QCoreApplication
 */
QAndroidService::QAndroidService(int &argc, char **argv, int flags)
    : QCoreApplication (argc, argv, QtAndroidPrivate::acuqireServiceSetup(flags))
    , d(new QAndroidServicePrivate{this})
{
}

/*!
    \fn QAndroidService::QAndroidService(int &argc, char **argv, const std::function<QAndroidBinder *(const QAndroidIntent &)> &binder)

    Creates a new Android service, passing \a argc and \a argv as parameters.

    \a binder is used to create a \l {QAndroidBinder}{binder} when needed.

    //! Parameter \a flags is omitted in the documentation.

    \sa QCoreApplication
 */
QAndroidService::QAndroidService(int &argc, char **argv, const std::function<QAndroidBinder *(const QAndroidIntent &)> &binder, int flags)
    : QCoreApplication (argc, argv, QtAndroidPrivate::acuqireServiceSetup(flags))
    , d(new QAndroidServicePrivate{this, binder})
{
}

QAndroidService::~QAndroidService()
{}

/*!
    The user must override this method and to return a binder.

    The \a intent parameter contains all the caller information.

    The returned binder is used by the caller to perform IPC calls.

    \warning This method is called from Binder's thread which is different
    from the thread that this object was created.

    \sa QAndroidBinder::onTransact, QAndroidBinder::transact
 */
QAndroidBinder* QAndroidService::onBind(const QAndroidIntent &/*intent*/)
{
    return nullptr;
}

QT_END_NAMESPACE
