//
// Created by Andrew Graser on 2/26/2024.
//

#include <src/Wolframite/Core/Log.h>
#include <src/Wolframite/Core/Core.h>
#include <GLFW/glfw3.h>
#include "Application.h"

namespace Tungsten {
    Application* Application::mInstance = nullptr;

    Application::Application() {
        Log::Init();

        TUNGSTEN_CORE_ASSERT(!mInstance, "Only one instance of Application may exist")
        mInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
    }

    void Application::Run() {
        while (mRunning){
            glfwPollEvents();

            for(auto layer : mLayerStack){
                layer->OnUpdate();
                layer->OnRender();

                //layer->OnImguiRender();
            }

        }
    }

    void Application::PushLayer(Layer *layer) {
        mLayerStack.PushLayer(layer);
    }
}
