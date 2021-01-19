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

#ifndef QANDROIDSERVICE_H
#define QANDROIDSERVICE_H

#include <QtAndroidExtras/qandroidextrasglobal.h>
#include <QCoreApplication>
#include <QSharedPointer>
#include <functional>

QT_BEGIN_NAMESPACE
class QAndroidServicePrivate;
class QAndroidIntent;
class QAndroidBinder;
class Q_ANDROIDEXTRAS_EXPORT QAndroidService : public QCoreApplication
{
public:
    QAndroidService(int &argc, char **argv
#ifndef Q_QDOC
                                     , int flags = ApplicationFlags
#endif
            );
    QAndroidService(int &argc, char **argv,
                    const std::function<QAndroidBinder*(const QAndroidIntent &intent)> & binder
#ifndef Q_QDOC
                                     , int flags = ApplicationFlags
#endif
            );
    virtual ~QAndroidService();

    virtual QAndroidBinder* onBind(const QAndroidIntent &intent);

private:
    friend class QAndroidServicePrivate;
    Q_DISABLE_COPY(QAndroidService)

    QScopedPointer<QAndroidServicePrivate> d;
};

QT_END_NAMESPACE

#endif // QANDROIDSERVICE_H
