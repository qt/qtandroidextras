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

import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

ApplicationWindow {
    id: window
    visible: true

    ColumnLayout {
        anchors.fill: parent
        Text {
            id: messengerLog
            text: qsTr("")
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            transformOrigin: Item.Center
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }

        RowLayout {
            id: rowlayout
            Layout.bottomMargin: 10
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            anchors.bottom: window.bottom
            spacing: 10

            Button {
                text: qsTr("Send to Java via JNI")
                onClicked: {
                    var message = qsTr("QML sending to Java: Hello from QML")
                    messengerLog.text += "\n" + message
                    JniMessenger.printFromJava(message)
                }
            }

            Button {
                text: "Clear"
                onClicked: messengerLog.text = ""
            }
        }
    }

    Connections {
        target: JniMessenger
        function onMessageFromJava(message) {
            var output = qsTr("QML received a message: %1").arg(message)
            print(output)
            messengerLog.text += "\n" + output
        }
    }
}
