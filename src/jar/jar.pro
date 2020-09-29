TARGET = Qt$${QT_MAJOR_VERSION}AndroidExtras

load(qt_build_paths)
CONFIG += java

DESTDIR = $$MODULE_BASE_OUTDIR/jar

JAVACLASSPATH += $$PWD/src

JAVASOURCES += $$PWD/src/org/qtproject/qt/android/extras/QtAndroidBinder.java \
               $$PWD/src/org/qtproject/qt/android/extras/QtAndroidServiceConnection.java \
               $$PWD/src/org/qtproject/qt/android/extras/QtNative.java

# install
target.path = $$[QT_INSTALL_PREFIX]/jar
INSTALLS += target

OTHER_FILES += $$JAVASOURCES
