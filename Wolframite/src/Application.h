//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_APPLICATION_H
#define SANDBOX_APPLICATION_H


#include <memory>
#include <Wolframite/Renderer/Shader.h>
#include <Wolframite/Renderer/Camera.h>

#include "Wolframite/LayerStack.h"
#include "Wolframite/Core/Window.h"
#include "Wolframite/Events/ApplicationEvent.h"
#include "Wolframite/Renderer/VertexArray.h"
#include "Wolframite/Renderer/Buffer.h"

namespace Tungsten {
    class Application {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer* layer);


        inline Window& GetWindow() {return *mWindow;}
        inline static Application& GetInstance() {return *mInstance;}

    private:
        bool OnWindowClosed(WindowCloseEvent &e);

    private:
        static Application* mInstance;

    private:

        bool mRunning = true;

        std::unique_ptr<Window> mWindow;
        LayerStack mLayerStack;

        float mLastFrameTime = 0.0f;
    };
}


#endif //SANDBOX_APPLICATION_H
