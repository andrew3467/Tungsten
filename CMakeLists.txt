cmake_minimum_required(VERSION 3.29)
project(Tungsten)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(external)

add_subdirectory(src/Tungsten)
add_subdirectory(src/Editor)