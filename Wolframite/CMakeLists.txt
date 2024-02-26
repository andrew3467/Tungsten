cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)

project(Wolframite)


file(GLOB_RECURSE PRJ_HEADERS
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
)

file(GLOB_RECURSE PRJ_SRC
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.c
)


add_library(Wolframite
        ${PRJ_HEADERS}
        ${PRJ_SRC}
)
