cmake_minimum_required(VERSION 3.5)

project(FatigueDetection VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TOOLCHAIN_DIR /opt/atk-dlrv1126-toolchain)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/usr/bin/arm-linux-gnueabihf-g++)
set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/usr/bin/arm-linux-gnueabihf-gcc)
set(SYSROOT ${TOOLCHAIN_DIR}/arm-buildroot-linux-gnueabihf/sysroot/usr/include)
set(CMAKE_SYSROOT ${TOOLCHAIN_DIR}/arm-buildroot-linux-gnueabihf/sysroot)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-g -O0 -ggdb -gdwarf -funwind-tables -rdynamic)
add_definitions(-Wno-write-strings -Wno-return-type)

set(OPENCV_LIBS opencv_core opencv_imgcodecs opencv_imgproc opencv_features2d opencv_flann opencv_highgui opencv_freetype)
set(RKNN_LIBS easymedia rga rkaiq rknn_api sample_common_isp)
link_directories(include lib)

include_directories(${SYSROOT})
include_directories(${SYSROOT}/rga)
include_directories(${SYSROOT}/easymedia)
include_directories(${SYSROOT}/rkaiq/uAPI)
include_directories(${SYSROOT}/rkaiq/xcore)
include_directories(${SYSROOT}/rkaiq/algos)
include_directories(${SYSROOT}/rkaiq/common)
include_directories(${SYSROOT}/rkaiq/iq_parser)
include_directories(${SYSROOT}/rknn)
include_directories(${SYSROOT}/qt5/QtNetwork)
include_directories(.)
include_directories(./include)
include_directories(./include/3rdparty)
include_directories(./include/3rdparty/drm/include/libdrm)
include_directories(./include/3rdparty/rga/include)

set(PROJECT_SOURCES
        main.cpp
        fatigue.cpp
        fatigue.h
        fatigue.ui
        ./SOURCE/images.qrc
        detect.cpp
        detect.h
        detect_postprocess.cpp
        detect_postprocess.h
        utils.cpp
        utils.h
        detect_loop.cpp
        detect_loop.h
)
set(MY_INCLUDE_DIRS
    ./
)
include_directories(${MY_INCLUDE_DIRS})
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FatigueDetection
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FatigueDetection APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FatigueDetection SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FatigueDetection
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FatigueDetection PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OPENCV_LIBS} ${RKNN_LIBS} pthread dl Qt${QT_VERSION_MAJOR}::Network opencv_objdetect)

set_target_properties(FatigueDetection PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS FatigueDetection
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FatigueDetection)
endif()
