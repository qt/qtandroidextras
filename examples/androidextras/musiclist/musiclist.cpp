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
#include "musiclist.h"

#include <QAndroidIntent>
#include <QAndroidJniEnvironment>

MusicList::MusicList(QObject *parent) : QObject(parent)
{
    QAndroidJniObject musicList = QAndroidJniObject::callStaticObjectMethod(
        "org/qtproject/example/musiclist/MusicList",
        "fetchMusicList",
        "(Landroid/content/Context;)Ljava/util/ArrayList;",
        QtAndroid::androidContext().object());

    for (int i = 0; i < musicList.callMethod<jint>("size"); ++i) {
        QAndroidJniObject track = musicList.callObjectMethod("get", "(I)Ljava/lang/Object;", i);
        const QString title = track.callObjectMethod("getTitle", "()Ljava/lang/String;").toString();
        const QString artist = track.callObjectMethod("getArtist", "()Ljava/lang/String;").toString();
        const long duration = track.callMethod<jlong>("getDuration");
        m_assembledMusicList.append(new MusicTrack(title, artist, duration, this));
    }
}

QList<MusicTrack *> MusicList::assembledMusicList() const
{
    return m_assembledMusicList;
}
