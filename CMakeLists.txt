
cmake_minimum_required(VERSION 3.16)

project(pattern_coders VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    UiTools
)

# Specify the path to libcurl
set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libcurl/include")
set(CURL_LIBRARY "${CMAKE_SOURCE_DIR}/libcurl/lib")

find_package(CURL REQUIRED)

qt_standard_project_setup()


link_directories(${CURL_LIBRARY})
# Add the include directory to the project
include_directories(${CURL_INCLUDE_DIR})


set(NLOHMANN_JSON_DIR "${CMAKE_SOURCE_DIR}/include/json")
include_directories("${NLOHMANN_JSON_DIR}")
file(GLOB NLOHMANN_JSON_SRC "${NLOHMANN_JSON_DIR}/json.hpp")
set(NLOHMANN_JSON ${NLOHMANN_JSON_SRC})



qt_add_executable(application
        #tests/test.cpp                 #
        #tests/testFunctions.h          # COMMENT OUT THIS LINEs IN ORDER TO TЕST FUNCTIONS



        ${NLOHMANN_JSON}


        src/main.cpp
        include/word.h
        include/parser.h
        src/parser.cpp
        src/word.cpp
        include/scrapper.h
        src/scrapper.cpp

        .gitignore
        bin/words.txt
        bin/words.json
        include/fileManager.h
        src/fileManager.cpp



)




#qt_add_resources(RESOURCES assets/resources.qrc)
target_sources(application PRIVATE ${RESOURCES})




target_link_libraries(application PRIVATE
        Qt6::Widgets
        Qt6::UiTools
        "${CURL_LIBRARY}/libcurl.a"
        "${CURL_LIBRARY}/libcurl.dll.a"
        "${GUMBO_LIBRARY}"
)

# Copy libcurl.dll to the output folder
#add_custom_command(TARGET application POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${CURL_LIBRARY}/libcurl.dll.a"
#        "${CMAKE_SOURCE_DIR}/bin"
#)


set_target_properties(application PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
