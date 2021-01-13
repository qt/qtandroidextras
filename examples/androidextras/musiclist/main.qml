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
import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Android Music List")

    Text {
        id: resultText
        height: 40
        text: "Music library list:"
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: 20
        verticalAlignment: Text.AlignTop
    }

    ToolSeparator {
        id: toolSeparator
        width: parent.width
        anchors.bottom: listView.top
        anchors.bottomMargin: 10
        anchors.top: resultText.bottom
        anchors.topMargin: 6
        anchors.horizontalCenter: parent.horizontalCenter
        orientation: Qt.Horizontal
    }

    ListView {
        id: listView
        width: parent.width
        clip: true
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: resultText.bottom
        anchors.topMargin: 30
        anchors.bottom: parent.bottom

        model: musiclist
        delegate: Rectangle {
            height: 25
            width: ListView.view.width
            color: index % 2 == 0 ? "#EDEDED" : "#FFFFFF"

            function toTimeFormat(sec_num) {
                sec_num = Math.floor(sec_num / 1000);
                var hours   = Math.floor(sec_num / 3600);
                var minutes = Math.floor((sec_num - (hours * 3600)) / 60);
                var seconds = sec_num - (hours * 3600) - (minutes * 60);

                if (hours < 10) { hours = "0" + hours; }
                if (minutes < 10) { minutes = "0" + minutes; }
                if (seconds < 10) { seconds = "0" + seconds; }

                return hours+':'+minutes+':'+seconds;
            }

            Text { text: model.modelData.title + " | " + model.modelData.artist + " | " + toTimeFormat(model.modelData.duration) }
        }
    }
}
