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

package org.qtproject.example.musiclist;

import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.MediaStore;
import java.util.ArrayList;

public class MusicList {

   static ArrayList<MusicTrack> fetchMusicList(Context context) {
        ArrayList<MusicTrack> musicList = new ArrayList<MusicTrack>();
        Cursor songCursor;

        try {
            ContentResolver contentResolver = context.getContentResolver();
            Uri songUri = MediaStore.Audio.Media.EXTERNAL_CONTENT_URI;
            songCursor = contentResolver.query(songUri, null, null, null, null);
        } catch (SecurityException e) {
            e.printStackTrace();
            return musicList;
        }

        if (songCursor != null && songCursor.moveToFirst())
        {
            int title = songCursor.getColumnIndexOrThrow(MediaStore.Audio.Media.TITLE);
            int artist = songCursor.getColumnIndexOrThrow(MediaStore.Audio.Media.ARTIST);
            int duration = duration = songCursor.getColumnIndexOrThrow(MediaStore.Audio.Media.DURATION);

            do {
                String currentTitle = songCursor.getString(title);
                String currentArtist = songCursor.getString(artist);
                long currentDuration = songCursor.getLong(duration);
                musicList.add(new MusicTrack(currentTitle, currentArtist, currentDuration));
            } while (songCursor.moveToNext());
        }

        if (songCursor != null)
            songCursor.close();

        return musicList;
    }
}

class MusicTrack {

    private String title;
    private String artist;
    private long duration;

    MusicTrack (String title, String artist, long duration) {
       this.title = title;
       this.artist = artist;
       this.duration = duration;
    }

   public String getTitle() { return title; }

   public String getArtist() { return artist; }

   public long getDuration() { return duration;  }
}
