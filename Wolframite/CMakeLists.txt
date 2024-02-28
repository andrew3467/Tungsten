cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)

project(Wolframite)

set(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/../bin)


#SPDlog
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)

#GLFW
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

#Tell glfw not to include OpenGL
add_compile_definitions(GLFW_INCLUDE_NONE)


#GLAD
file(GLOB_RECURSE GLAD_SRC external/glad/*)
include_directories(external/glad/include)




include_directories(src)

file(GLOB_RECURSE PRJ_HEADERS
        ${CMAKE_SOURCE_DIR}/*.h
        ${CMAKE_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE PRJ_SRC
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.c
)


add_library(Wolframite
        ${GLAD_SRC}
        src/Wolframite/Core/Log.cpp
        src/Wolframite/Core/Log.h
        src/Wolframite/Core/Window.h
        src/Wolframite/Platform/Windows/WindowsWindow.h
        src/Wolframite/Platform/Windows/WindowsWindow.cpp
        src/Application.h
        src/Application.cpp
        src/Wolframite/Tungsten.h
        src/Wolframite/Core/Core.h
        src/Wolframite/Layer.h
        src/Wolframite/LayerStack.h
        src/Wolframite/LayerStack.cpp
        src/Wolframite/Events/MouseEvent.h
        src/Wolframite/Events/Event.h
        src/Wolframite/Events/KeyEvent.h
        src/Wolframite/Events/ApplicationEvent.h
        src/Wolframite/Renderer/GraphicsContext.h
        src/Wolframite/Platform/OpenGL/OpenGLGraphicsContext.h
        src/Wolframite/Platform/OpenGL/OpenGLGraphicsContext.cpp
        src/Wolframite/Renderer/Buffer.cpp
        src/Wolframite/Platform/OpenGL/OpenGLBuffer.cpp
)

target_link_libraries(Wolframite
        PUBLIC
        spdlog::spdlog
        glfw
)
