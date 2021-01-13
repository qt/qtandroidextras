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
#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QtAndroid>

class MusicTrack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString artist READ artist CONSTANT)
    Q_PROPERTY(long duration READ duration CONSTANT)

public:
    MusicTrack(const QString title, const QString artist, const long duration, QObject *parent = nullptr)
        : QObject(parent), m_title(title), m_artist(artist), m_duration(duration) {}

    QString title() const { return m_title; }
    QString artist() const { return m_artist; }
    long duration() const { return m_duration; }

private:
    QString m_title;
    QString m_artist;
    long m_duration;
};

class MusicList : public QObject
{
    Q_OBJECT

public:
    MusicList(QObject *parent = nullptr);
    QList<MusicTrack *> assembledMusicList() const;

private:
    QList<MusicTrack *> m_assembledMusicList;
};

#endif
