cmake_minimum_required(VERSION 3.29)
project(src/Tungsten)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_library(
        Tungsten
        ${SRC}
        ${HEADERS}
)

target_include_directories(
        Tungsten
        PRIVATE
        src/Tungsten
)
