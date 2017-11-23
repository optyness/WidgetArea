cmake_minimum_required(VERSION 3.9)

project(Mytestapp)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set (LIB_HEADERS
        listwidget.h
        )

set (HEADERS
        listwidgetitem.h
        cardlist.h
        cardwidget.h
        usermodelrole.h
        widgetmodel.h
        widgettype.h
        )

set (LIB_SOURCES
        listwidget.cpp
        )

set (SOURCES
        listwidgetitem.cpp
        cardlist.cpp
        cardwidget.cpp
        widgetmodel.cpp
        main.cpp
        )

add_library(listwidget STATIC ${LIB_HEADERS} ${LIB_SOURCES})
target_link_libraries(listwidget Qt5::Widgets)

# Tell CMake to create the helloworld executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} )
include_directories(${Qt5Widgets_INCLUDES})

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} listwidget)
