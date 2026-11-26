cmake_minimum_required(VERSION 3.29)
project(Tungsten)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external)

add_subdirectory(src/Tungsten)
add_subdirectory(src/Editor)