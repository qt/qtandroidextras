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

import QtQuick 2.0

Rectangle {
    width: 500
    height: 500
    color: "white"

    Column {
        anchors.fill: parent
        spacing: (height - happyButton.height - sadButton.height - title.height) / 3

        Text {
            id: title
            color: "black"
            font.pixelSize: parent.width / 20
            text: "How are you feeling?"
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }

        Image {
            id: happyButton
            height: parent.height / 5
            fillMode: Image.PreserveAspectFit
            source: "../images/happy.png"
            anchors.horizontalCenter: parent.horizontalCenter
            smooth: true

            Behavior on scale {
                PropertyAnimation {
                    duration: 100
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: notificationClient.notification = "User is happy!"
                onPressed: happyButton.scale = 0.9
                onReleased: happyButton.scale = 1.0
            }
        }

        Image {
            id: sadButton
            height: parent.height / 5
            fillMode: Image.PreserveAspectFit
            source: "../images/sad.png"
            anchors.horizontalCenter: parent.horizontalCenter
            smooth: true

            Behavior on scale {
                PropertyAnimation {
                    duration: 100
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: notificationClient.notification = "User is sad :("
                onPressed: sadButton.scale = 0.9
                onReleased: sadButton.scale = 1.0
            }
        }
    }
}
