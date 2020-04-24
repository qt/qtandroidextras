# Generated from qandroidjniobject.pro.

#####################################################################
## tst_qandroidjniobject Test:
#####################################################################

qt_add_test(tst_qandroidjniobject
    SOURCES
        tst_qandroidjniobject.cpp
    PUBLIC_LIBRARIES
        Qt::AndroidExtras
        Qt::Gui
)

if(ANDROID)
    set_property(TARGET tst_qandroidjniobject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/testdata
    )
endif()

#### Keys ignored in scope 1:.:.:qandroidjniobject.pro:<TRUE>:
# OTHER_FILES = "testdata/src/org/qtproject/qt5/android/testdata/QtAndroidJniObjectTestClass.java"
