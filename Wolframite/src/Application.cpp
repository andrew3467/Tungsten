//
// Created by Andrew Graser on 2/26/2024.
//

#include "Wolframite/Core/Log.h"
#include "Wolframite/Core/Core.h"

#include <GLFW/glfw3.h>
#include <Wolframite/Events/ApplicationEvent.h>
#include "Application.h"

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
