/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#include "qandroidfunctions.h"

#include <QtCore/private/qjnihelpers_p.h>

QT_BEGIN_NAMESPACE

/*!
    \namespace QtAndroid
    \inmodule QtAndroidExtras
    \since 5.3
    \brief The QtAndroid namespace provides miscellaneous functions to aid Android development.
    \inheaderfile QtAndroid
*/

/*!
    \since 5.3
    \fn QAndroidJniObject QtAndroid::androidActivity()

    Returns a handle to this applications main Activity

    \sa QAndroidJniObject
*/
QAndroidJniObject QtAndroid::androidActivity()
{
    return QtAndroidPrivate::activity();
}

/*!
    \since 5.3
    \fn int QtAndroid::androidSdkVersion()

    Returns the Android SDK version. This is also known as the API level.
*/
int QtAndroid::androidSdkVersion()
{
    return QtAndroidPrivate::androidSdkVersion();
}

QT_END_NAMESPACE
