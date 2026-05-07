cmake_minimum_required(VERSION 3.21)

project(DeepTideStation VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(DeepTideStation
    src/main.cpp
    src/gamewindow.h
    src/gamewindow.cpp
    src/gamescene.h
    src/gamescene.cpp
    src/projectpaths.h
    src/projectpaths.cpp
)

target_link_libraries(DeepTideStation PRIVATE Qt6::Widgets)

if (WIN32)
    set_target_properties(DeepTideStation PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
