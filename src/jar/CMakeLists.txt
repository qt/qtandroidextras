# Generated from jar.pro.

set(java_sources
    src/org/qtproject/qt5/android/extras/QtAndroidBinder.java
    src/org/qtproject/qt5/android/extras/QtAndroidServiceConnection.java
    src/org/qtproject/qt5/android/extras/QtNative.java
)

add_jar(QtAndroidExtras
    INCLUDE_JARS ${QT_ANDROID_JAR}
    SOURCES ${java_sources}
)

install_jar(QtAndroidExtras
    DESTINATION jar
    COMPONENT Devel
)

