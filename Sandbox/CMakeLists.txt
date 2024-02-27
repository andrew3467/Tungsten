cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)

project(Sandbox)

set(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../bin)


#Wolframite
add_subdirectory(${CMAKE_SOURCE_DIR}/../Wolframite ${CMAKE_SOURCE_DIR}/Wolframite)
include_directories(${CMAKE_SOURCE_DIR}/../Wolframite/src)


file(GLOB_RECURSE PRJ_HEADERS
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
)

file(GLOB_RECURSE PRJ_SRC
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.c
)


add_executable(Sandbox
        ${PRJ_HEADERS}
        ${PRJ_SRC}
)

target_link_libraries(Sandbox
        PUBLIC
        Wolframite
)
