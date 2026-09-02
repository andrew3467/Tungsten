//
// Created by Andrew Graser on 11/27/2024.
//


#pragma once

#include <Tungsten/Core/Asset/AssetManager.h>
#include "Window.h"
#include "Camera.h"
#include "ImGuiLayer.h"

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

        void Run(const std::function<void()>& updateFunc, const std::function<void()>& startFunc, const std::function<void()>& imGuiFunc = nullptr);

        Window& GetWindow() {return *mWindow;}
        AssetManager& Assets() {return mAssetManager;}


        void OnWindowClose(GLFWwindow *window);

        static Engine& Get() {return *sInstance;}


    private:
        static Engine* sInstance;

        bool mRunning = false;

        std::shared_ptr<Window> mWindow;

        AssetManager mAssetManager;

        ImGuiLayer mImGuiLayer;

    public:
        static std::shared_ptr<Camera> MainCamera;
    };

    AssetManager& Assets();
}
