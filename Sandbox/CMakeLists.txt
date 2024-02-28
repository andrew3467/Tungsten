cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)

project(Sandbox)

set(${CMAKE_BINARY_DIR} ../bin)


#Wolframite
add_subdirectory(../Wolframite Wolframite)
include_directories(../Wolframite/src)

#ImGui
include_directories(../Wolframite/external/imgui)


file(GLOB_RECURSE PRJ_HEADERS
        src/*.h
        src/*.hpp
)

file(GLOB_RECURSE PRJ_SRC
        src/*.cpp
        src/*.c
)


add_executable(Sandbox
        ${PRJ_HEADERS}
        ${PRJ_SRC}
)

target_link_libraries(Sandbox
        PUBLIC
        Wolframite
)
