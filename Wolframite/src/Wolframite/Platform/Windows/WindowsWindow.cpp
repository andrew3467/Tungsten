//
// Created by Andrew Graser on 2/26/2024.
//

#include "WindowsWindow.h"
#include "Wolframite/Core/Core.h"
#include "Wolframite/Events/ApplicationEvent.h"
#include "Wolframite/Events/MouseEvent.h"
#include "Wolframite/Events/KeyEvent.h"

#include <GLFW/glfw3.h>


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
        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
            auto& data = *(WindowData*) glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(mWindow, [](GLFWwindow *window, unsigned int keycode) {
            WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleassedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset){
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos){
            auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });
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
