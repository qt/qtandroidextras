TARGET = QtAndroidExtras
DEFINES += QT_NO_USING_NAMESPACE
QMAKE_DOCS = \
             $$PWD/doc/qtandroidextras.qdocconf
QT -= gui
QT += core-private

include(jni/jni.pri)
include(android/android.pri)

ANDROID_BUNDLED_JAR_DEPENDENCIES = \
    jar/Qt$${QT_MAJOR_VERSION}AndroidExtras.jar

load(qt_module)
