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


#GLM
add_subdirectory(external/glm)
include_directories(external/glm)

#Imgui
add_subdirectory(external/imgui)
include_directories(external/imgui)




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
        src/Wolframite/Renderer/VertexArray.h
        src/Wolframite/Renderer/VertexArray.cpp
        src/Wolframite/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Wolframite/Renderer/Shader.h
        src/Wolframite/Platform/OpenGL/OpenGLShader.h
        src/Wolframite/Platform/OpenGL/OpenGLShader.cpp
        src/Wolframite/Renderer/Shader.cpp
        src/Wolframite/Renderer/Camera.h
        src/Wolframite/Renderer/Camera.cpp
        src/Wolframite/Core/Input.h
        src/Wolframite/Platform/Windows/WindowsInput.cpp
        src/Wolframite/Core/KeyCodes.h
        src/Wolframite/Core/MouseButtonCodes.h
        src/Wolframite/Renderer/Renderer.h
        src/Wolframite/Renderer/Renderer.cpp
        src/Wolframite/Renderer/RendererAPI.cpp
        src/Wolframite/Renderer/RenderCommand.h
        src/Wolframite/Platform/OpenGL/OpenGLRendererAPI.h
        src/Wolframite/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Wolframite/Renderer/RenderCommand.cpp
        src/Wolframite/ImGui/ImGuiBuild.cpp
        src/Wolframite/ImGui/ImGuiLayer.h
        src/Wolframite/ImGui/ImGuiLayer.cpp
)

target_link_libraries(Wolframite
        PUBLIC
        spdlog::spdlog
        glfw
        glm
        ImGui
)
