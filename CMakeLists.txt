cmake_minimum_required(VERSION 3.9)

project(WidgetArea)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set (HEADERS 
	listwidget.h
	listwidgetitem.h)
 
set (SOURCES 
	listwidget.cpp
        listwidgetitem.cpp
	main.cpp) 

# Tell CMake to create the helloworld executable
add_executable(WidgetArea ${HEADERS} ${SOURCES})
include_directories(${Qt5Widgets_INCLUDES})
# Use the Widgets module from Qt 5.
target_link_libraries(WidgetArea Qt5::Widgets)
