cmake_minimum_required(VERSION 3.16)

project(pattern_coders VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    UiTools
)
qt_standard_project_setup()

qt_add_executable(application
    src/main.cpp
    include/algorithms.h
    include/application.h
    include/backend.h
    assets/main.ui
    assets/resources.qrc
)

qt_add_resources(RESOURCES assets/resources.qrc)
target_sources(application PRIVATE ${RESOURCES})

target_link_libraries(application PRIVATE
    Qt6::Widgets
    Qt6::UiTools
)

set_target_properties(application PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)
