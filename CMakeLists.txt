# Generated from qtandroidextras.pro.

cmake_minimum_required(VERSION 3.15.0)

project(QtAndroidExtras
    VERSION 6.0.0
    DESCRIPTION "Qt AndroidExtras Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core Gui) # special case

qt_build_repo()
