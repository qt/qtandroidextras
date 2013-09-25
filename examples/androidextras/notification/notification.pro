QT += quick androidextras

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
ANDROID_PACKAGE = org.qtproject.example.notification
ANDROID_MINIMUM_VERSION = 16
ANDROID_TARGET_VERSION = 16
ANDROID_APP_NAME = Qt Notifier

SOURCES += \
    main.cpp \
    notificationclient.cpp

OTHER_FILES += \
    qml/main.qml \
    android-sources/src/org/qtproject/example/notification/NotificationClient.java \
    android-sources/AndroidManifest.xml

RESOURCES += \
    main.qrc

HEADERS += \
    notificationclient.h
