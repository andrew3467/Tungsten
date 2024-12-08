//
// Created by Andrew Graser on 11/9/2024.
//

#include "Window.h"

#include "Engine.h"
#include "Renderer/Renderer.h"


namespace Tungsten {
    //GLFW Error callback
    void GLFWErrorCallback(int code, const char* description)
    {
        TUNGSTEN_ERROR("GLFW Error {0}: {1}", code, description);
    }

    bool sGLFWInitialized = false;
    void InitGLFW() {
        glfwSetErrorCallback(GLFWErrorCallback);

        int success = glfwInit();
        TUNGSTEN_ASSERT(success, "Failed to initialize GLFW3");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        sGLFWInitialized = true;
    }

    Window::Window(const WindowProps &props)
    {
        mData.Width = props.Width;
        mData.Height = props.Height;
        mData.Title = props.Title;

        mData.VSync = true;


        if(!sGLFWInitialized)
        {
            InitGLFW();
        }

        mWindow = glfwCreateWindow(mData.Width, mData.Height, mData.Title.c_str(), nullptr, nullptr);
        TUNGSTEN_ASSERT(mWindow, "Failed to create GLFW window");

        glfwMakeContextCurrent(mWindow);
        glfwSetWindowUserPointer(mWindow, &mData);

        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
        {
            Engine::Get().Close();
        });

        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow *window, int width, int height)
        {
            auto data = (WindowData*)glfwGetWindowUserPointer(window);
            data->Width = width;
            data->Height = height;

            Renderer::SetViewport(0, 0, width, height);
        });
    }

    Window::~Window() {
        glfwDestroyWindow(mWindow);
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(mWindow);
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }
} // Tungsten