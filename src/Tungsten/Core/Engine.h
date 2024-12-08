//
// Created by Andrew Graser on 11/27/2024.
//


#pragma once

#include "Window.h"

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

        void Run(std::function<void()> updateFunc);

        Window& GetWindow() {return *mWindow;}


        void OnWindowClose(GLFWwindow *window);

        static Engine& Get() {return *sInstance;}


    private:
        static Engine* sInstance;

        bool mRunning = false;

        std::shared_ptr<Window> mWindow;
    };
}
