cmake_minimum_required(VERSION 3.22.1)
project(3DViewer_v2_0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 QtCore COMPONENTS Widgets REQUIRED OpenGL GLUT)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED OpenGL)

include_directories(src/includes)

add_executable(3DViewer_v2_0
        src/main/main.cc
        src/front/main_window.cc
        src/front/main_window.h
        src/front/main_window.ui
        src/front/widget_draw.cc
        src/front/widget_draw.h
        src/front/model_settings.cc
        src/front/model_settings.h
        src/controller/controller.cc
        src/controller/controller.h
        src/backend/main_back_end.cc
        src/backend/main_back_end.h
        src/backend/parser.cc
        src/backend/parser.h
        src/backend/model_transform.cc
        src/backend/model_transform.h
        src/backend/validator_file_obj.cc
        src/backend/validator_file_obj.h
        src/backend/common_backend.h

        src/includes/qtgifimage/src/gifimage/qgifimage.h
        src/includes/qtgifimage/src/gifimage/qgifimage.cpp
        src/includes/qtgifimage/src/gifimage/qgifimage_p.h
        src/includes/qtgifimage/src/gifimage/qgifglobal.h

        src/includes/qtgifimage/src/3rdParty/giflib/dgif_lib.c
        src/includes/qtgifimage/src/3rdParty/giflib/egif_lib.c
        src/includes/qtgifimage/src/3rdParty/giflib/gif_err.c
        src/includes/qtgifimage/src/3rdParty/giflib/gif_font.c
        src/includes/qtgifimage/src/3rdParty/giflib/gif_hash.c
        src/includes/qtgifimage/src/3rdParty/giflib/gif_hash.h
        src/includes/qtgifimage/src/3rdParty/giflib/gif_lib.h
        src/includes/qtgifimage/src/3rdParty/giflib/gif_lib_private.h
        src/includes/qtgifimage/src/3rdParty/giflib/gifalloc.c
        src/includes/qtgifimage/src/3rdParty/giflib/quantize.c

)

target_link_libraries(3DViewer_v2_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL glut GL GLU)



find_package(GTest COMPONENTS Gtest)

add_executable(test_model
        src/tests/test.cc
        src/backend/main_back_end.cc
        src/backend/main_back_end.h
        src/backend/parser.cc
        src/backend/parser.h
        src/backend/model_transform.cc
        src/backend/model_transform.h
        src/backend/validator_file_obj.cc
        src/backend/validator_file_obj.h
        src/backend/common_backend.h
)

target_link_libraries(test_model GTest::GTest Qt${QT_VERSION_MAJOR}::Widgets)

enable_testing()

gtest_discover_tests(test_model)

