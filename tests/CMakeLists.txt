cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tests test.cpp)


# PRIVATE makes the include directory visible only to the target that
# consumes it, and not to any of its dependents.
target_include_directories(tests PRIVATE ../../include)