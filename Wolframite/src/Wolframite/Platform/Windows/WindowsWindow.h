//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_WINDOWSWINDOW_H
#define SANDBOX_WINDOWSWINDOW_H


#include "Wolframite/Core/Window.h"


#include <GLFW/glfw3.h>


namespace Tungsten {
    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps &props);
        ~WindowsWindow() override;

        inline uint32_t GetWidth() const override {return mData.Width;}
        inline uint32_t GetHeight() const override {return mData.Height;}

        inline void SetEventCallback(const EventCallbackFn &callback) override {
            mData.EventCallback = callback;
        }


        void OnUpdate() override;

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    private:
        void Init(const WindowProps& props);
        void Shutdown();

    private:
        GLFWwindow* mWindow;

        struct WindowData {
            uint32_t Width, Height;
            std::string Title;

            bool VSync;

            EventCallbackFn EventCallback;
        } mData;
    };
}


#endif //SANDBOX_WINDOWSWINDOW_H
