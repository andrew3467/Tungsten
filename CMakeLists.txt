cmake_minimum_required(VERSION 3.29)
project(src/Tungsten)

set(CMAKE_CXX_STANDARD 23)

find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


add_subdirectory(External)


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
        External/stb
        External/imgui
)

target_link_libraries(
        Tungsten
        PUBLIC
        spdlog::spdlog
        PRIVATE
        glad::glad
        glfw
        glm::glm
        stb
        ImGui
)

target_precompile_headers(
        Tungsten
        PUBLIC
        src/Tungsten/tungstenpch.h
)

target_compile_definitions(
        Tungsten
        PRIVATE

        GLFW_INCLUDE_NONE
)
