cmake_minimum_required(VERSION 3.9)

project(listwidgetlib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set (LIB_HEADERS
        listwidget.h
        )

set (LIB_SOURCES
        listwidget.cpp
        )

add_library(listwidget STATIC ${LIB_HEADERS} ${LIB_SOURCES})
target_link_libraries(listwidget Qt5::Widgets)

#include_directories(${Qt5Widgets_INCLUDES})
