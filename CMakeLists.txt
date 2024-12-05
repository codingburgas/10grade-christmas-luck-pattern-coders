cmake_minimum_required(VERSION 3.16)

project(pattern_coders VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(application
    src/main.cpp
    include/algorithms.h
    include/application.h
    include/backend.h
)

target_link_libraries(application PRIVATE Qt6::Widgets)

set_target_properties(application PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
