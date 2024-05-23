cmake_minimum_required(VERSION 3.5)

project(DriverManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network OpenCV Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network Charts)

#opencv
include_directories(D:/opencv452/include/opencv2)
include_directories(D:/opencv452/include)
link_directories(D:/opencv452/x64/mingw/lib)
file(GLOB OpenCV_LIBS "D:/opencv452/x64/mingw/lib/*.a")
#include_directories(${OpenCV_INCLUDE_DIRS})
#seetaface
include_directories(D:/SeetaFace/include D:/SeetaFace/include/seeta)
link_directories(D:/SeetaFace/lib)
file(GLOB SEETAFACE "D:/SeetaFace/lib/*.a")
set(PROJECT_SOURCES
        main.cpp
        driver.cpp
        driver.h
        driver.ui
        ./images/img.qrc
        adduser.cpp
        adduser.h
        adduser.ui
        sqlmgr.cpp
        sqlmgr.h
        facedetect.cpp
        facedetect.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DriverManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DriverManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DriverManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DriverManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DriverManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network ${OpenCV_LIBS} ${SEETAFACE} Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(DriverManager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS DriverManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DriverManager)
endif()
