//
// Created by Andrew Graser on 11/27/2024.
//

#include "Engine.h"


#include "Tungsten/Core/Util/Time.h"
#include "Tungsten/Renderer/Renderer.h"
#include "Tungsten/Renderer/Texture.h"
#include "Primitive.h"

namespace Tungsten
{
    AssetManager& Assets() {return Engine::Get().Assets();}

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
        Primitive::Init();

        mImGuiLayer.Init();

        MainCamera = std::make_shared<Camera>();

        TUNGSTEN_INFO("Tungsten Initialized: Starting Runtime");
        mRunning = true;
    }

    Engine::~Engine()
    {
    }

    void Engine::Run(const std::function<void()>& updateFunc, const std::function<void()>& startFunc, const std::function<void()>& imGuiFunc)
    {
        startFunc();


        Renderer::SetClearColor(0.1f, 0.1f, 0.1f);
        while(mRunning)
        {
            Renderer::Clear();

            Renderer::StartScene(MainCamera->GetViewProjection(), MainCamera->GetPosition());
            updateFunc();

            Renderer::EndScene();

            Renderer::ExecuteRenderPipeline();

            //Restore Gl Viewport
            Renderer::SetViewport(0.0f, 0.0f, mWindow->GetSize().x, mWindow->GetSize().y);

            if(imGuiFunc) {
                mImGuiLayer.Begin();

                imGuiFunc();

                mImGuiLayer.End();
            }

            mWindow->Update();
            Time::Update();
        }
    }

    void Engine::OnWindowClose(GLFWwindow *window)
    {
        mRunning = false;
    }
}
