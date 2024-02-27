cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)

project(Wolframite)


#SPDlog
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)





include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE PRJ_HEADERS
        ${CMAKE_SOURCE_DIR}/*.h
        ${CMAKE_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE PRJ_SRC
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.c
)


add_library(Wolframite
        src/Wolframite/Core/Log.cpp
        src/Wolframite/Core/Log.h
)

target_link_libraries(Wolframite
        PUBLIC
        spdlog::spdlog
)
