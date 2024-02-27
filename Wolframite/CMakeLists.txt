cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 23)

project(Wolframite)


#SPDlog
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)

#GLFW
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

#Tell glfw not to include OpenGL
add_compile_definitions(GLFW_INCLUDE_NONE)




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
        src/Wolframite/Core/Window.h
        src/Platform/Windows/WindowsWindow.h
        src/Platform/Windows/WindowsWindow.cpp
        src/Application.h
        src/Application.cpp
        src/Wolframite/Tungsten.h
        src/Wolframite/Core/Core.h
        src/Wolframite/Layer.h
        src/Wolframite/LayerStack.h
)

target_link_libraries(Wolframite
        PUBLIC
        spdlog::spdlog
        glfw
)
