//
// Created by Andrew Graser on 2/26/2024.
//

#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include <src/Wolframite/Core/Core.h>


namespace Tungsten {
    static bool mGLFWInitialized = false;

    static void GLFWErrorCallback(int error_code, const char* description){
        TUNGSTEN_CORE_ERROR("GLFW Error: ({0}), {1}", error_code,  description);
    }

    Window* Window::Create(const Tungsten::WindowProps &props) {
        return new WindowsWindow(props);
    }


    WindowsWindow::WindowsWindow(const WindowProps &props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps &props) {
        mData.Width = props.Width;
        mData.Height = props.Height;
        mData.Title = props.Title;

        if(!mGLFWInitialized) {
            int success = glfwInit();
            TUNGSTEN_CORE_ASSERT(success, "Failed to initialize GLFW");

            glfwSetErrorCallback(GLFWErrorCallback);

            mGLFWInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mWindow = glfwCreateWindow(mData.Width, mData.Height, mData.Title.c_str(), nullptr, nullptr);


        //TODO
        //Init OpenGL context

        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);


        //TODO
        //GLFW Callbacks
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        //Swap Buffers
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(mWindow);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        //glfwSwapInterval(enabled ? 1 : 0);
        mData.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const {
        return mData.VSync;
    }


}
