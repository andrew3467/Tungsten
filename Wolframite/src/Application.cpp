//
// Created by Andrew Graser on 2/26/2024.
//

#include "Application.h"
#include "Wolframite/Core/Log.h"
#include "Wolframite/Core/Core.h"
#include <Wolframite/Events/ApplicationEvent.h>

#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include <Wolframite/Renderer/Shader.h>
#include <Wolframite/Core/Input.h>
#include <Wolframite/Core/KeyCodes.h>
#include <Wolframite/Renderer/RenderCommand.h>
#include <Wolframite/Renderer/Renderer.h>


namespace Tungsten {
    Application* Application::mInstance = nullptr;

    Application::Application() {
        Log::Init();

        TUNGSTEN_CORE_ASSERT(!mInstance, "Only one instance of Application may exist")
        mInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    void Application::Run() {
        while (mRunning){
            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            for(auto layer : mLayerStack){
                layer->OnUpdate(timestep);
                layer->OnRender();

                //layer->OnImguiRender();
            }

            mWindow->OnUpdate();
        }
    }

    void Application::PushLayer(Layer *layer) {
        mLayerStack.PushLayer(layer);
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

        for(auto it = mLayerStack.end(); it != mLayerStack.begin(); ){
            (*--it)->OnEvent(e);
            if(e.Handled){
                break;
            }
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        mRunning = false;

        return true;
    }
}
