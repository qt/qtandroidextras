/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
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
****************************************************************************/

#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class JniMessenger : public QObject
{
    Q_OBJECT

public:
    explicit JniMessenger(QObject *parent = nullptr);
    static JniMessenger *instance() { return m_instance; }
    Q_INVOKABLE void printFromJava(const QString &message);

signals:
    void messageFromJava(const QString &message);

public slots:

private:
    static JniMessenger *m_instance;
};

#endif // MYCLASS_H
