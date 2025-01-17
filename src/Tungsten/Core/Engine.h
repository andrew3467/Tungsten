//
// Created by Andrew Graser on 11/27/2024.
//


#pragma once

#include "Window.h"
#include "Camera.h"

namespace Tungsten
{
    class Engine
    {
    public:
        Engine() : Engine("Tungsten Engine") {}
        Engine(const std::string& title);
        ~Engine();

        bool IsRunning() const {return mRunning;}
        void Close() {mRunning = false;}

        void Run(const std::function<void()>& updateFunc, const std::function<void()>& startFunc);

        Window& GetWindow() {return *mWindow;}


        void OnWindowClose(GLFWwindow *window);

        static Engine& Get() {return *sInstance;}


    private:
        static Engine* sInstance;

        bool mRunning = false;

        std::shared_ptr<Window> mWindow;

    public:
        static std::shared_ptr<Camera> MainCamera;
    };
}
