//
// Created by Andrew Graser on 11/27/2024.
//

#include "Engine.h"


#include "Time.h"
#include "../Renderer/Renderer.h"
#include "Renderer/Texture.h"

namespace Tungsten
{

    std::shared_ptr<Camera> Engine::MainCamera = nullptr;
    Engine* Engine::sInstance = nullptr;

    Engine::Engine(const std::string &title)
    {
        sInstance = this;

        Logger::Init();
        Time::Init();


        mWindow = std::make_shared<Window>(WindowProps(1280, 720, title));


        Renderer::Init();
        Texture2D::Init();

        MainCamera = std::make_shared<Camera>();

        TUNGSTEN_INFO("Tungsten Initialized: Starting Runtime");
        mRunning = true;
    }

    Engine::~Engine()
    {
    }

    void Engine::Run(const std::function<void()>& updateFunc, const std::function<void()>& startFunc)
    {
        startFunc();

        while(mRunning)
        {
            Renderer::SetClearColor(0.1f, 0.1f, 0.1f);
            Renderer::Clear();

            Renderer::StartScene(MainCamera->GetViewProjection());

            updateFunc();

            mWindow->Update();
            Time::Update();
        }
    }

    void Engine::OnWindowClose(GLFWwindow *window)
    {
        mRunning = false;
    }
}
