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

#ifndef QANDROIDBINDER_P_H
#define QANDROIDBINDER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qandroidjniobject.h"

#include <functional>
#include <jni.h>

QT_BEGIN_NAMESPACE
class QAndroidBinder;
class QAndroidBinderPrivate
{
public:
    explicit QAndroidBinderPrivate(QAndroidBinder *binder);
    explicit QAndroidBinderPrivate(const QAndroidJniObject &binder);
    void setDeleteListener(const std::function<void()> &func) { m_deleteListener = func; }
    ~QAndroidBinderPrivate();

private:
    QAndroidJniObject handle;
    std::function<void()> m_deleteListener;
    bool m_isQtAndroidBinder;
    friend class QAndroidBinder;
};
QT_END_NAMESPACE

#endif // QANDROIDBINDER_P_H
