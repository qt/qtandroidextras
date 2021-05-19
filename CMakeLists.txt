# Generated from qtandroidextras.pro.

cmake_minimum_required(VERSION 3.15.0)

include(.cmake.conf)
project(QtAndroidExtras
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt AndroidExtras Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

# Make sure we use the fixed BASE argument of qt_add_resource.
set(QT_USE_FIXED_QT_ADD_RESOURCE_BASE TRUE)

# special case begin
find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core)
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS Gui)

if (NOT ANDROID)
    message(NOTICE "Skipping the build as the condition \"ANDROID\" is not met.")
    return()
endif()
# special case end

if(NOT TARGET Qt::Gui)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Gui\" is not met.")
    return()
endif()

qt_build_repo()
