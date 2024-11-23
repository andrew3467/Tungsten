//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once
#include <GLFW/glfw3.h>

namespace Tungsten {
    struct WindowProps {
        uint32_t Width = 1280, Height = 720;
        std::string Title = "Tungsten Engine";
    };

    class Window {
    public:
        Window() = delete;
        Window(const WindowProps& props);
        ~Window();

        GLFWwindow* GetNativeWindow() const {return mWindow;}

        bool ShouldClose();

        void Update();

    private:
        struct WindowData {
            uint32_t Width;
            uint32_t Height;
            std::string Title;

            bool VSync;
        };
        WindowData mData;


        GLFWwindow *mWindow;
    };
}
