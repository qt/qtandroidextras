# Generated from androidextras.pro.

#####################################################################
## AndroidExtras Module:
#####################################################################

qt_add_module(AndroidExtras
    SOURCES
        android/qandroidactivitycallbackresultreceiver.cpp
        android/qandroidactivityresultreceiver.cpp android/qandroidactivityresultreceiver.h android/qandroidactivityresultreceiver_p.h
        android/qandroidbinder.cpp android/qandroidbinder.h android/qandroidbinder_p.h
        android/qandroidfunctions.cpp android/qandroidfunctions.h
        android/qandroidintent.cpp android/qandroidintent.h
        android/qandroidparcel.cpp android/qandroidparcel.h android/qandroidparcel_p.h
        android/qandroidservice.cpp android/qandroidservice.h
        android/qandroidserviceconnection.cpp android/qandroidserviceconnection.h
        android/qjnionload.cpp
        jni/qandroidjnienvironment.cpp jni/qandroidjnienvironment.h
        jni/qandroidjniobject.cpp jni/qandroidjniobject.h
    DEFINES
        QT_NO_USING_NAMESPACE
    LIBRARIES
        Qt::CorePrivate
    PUBLIC_LIBRARIES
        Qt::Core
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
)

if(ANDROID)
    set_property(TARGET AndroidExtras APPEND PROPERTY QT_ANDROID_BUNDLED_JAR_DEPENDENCIES
        jar/Qt${QtAndroidExtras_VERSION_MAJOR}AndroidExtras.jar
    )
endif()
qt_add_docs(AndroidExtras
    doc/qtandroidextras.qdocconf
)

