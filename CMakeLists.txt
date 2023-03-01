cmake_minimum_required(VERSION 3.24)
project(orbit)
add_subdirectory(test)
include_directories (include)

set(CMAKE_CXX_STANDARD 23)

set(HEADER_FILES include/vector3.hpp include/constants.hpp include/orbit.hpp)

set(SOURCE_FILES source/vector3.cpp source/orbit.cpp)

add_library(orbit SHARED ${SOURCE_FILES} ${HEADER_FILES})
