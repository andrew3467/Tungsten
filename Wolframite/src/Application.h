//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_APPLICATION_H
#define SANDBOX_APPLICATION_H


#include <memory>

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



        static Application* GetInstance() {return mInstance;}

    private:
        bool OnWindowClosed(WindowCloseEvent &e);

    private:
        static Application* mInstance;

    private:

        bool mRunning = true;

        std::unique_ptr<Window> mWindow;
        LayerStack mLayerStack;

        std::shared_ptr<VertexArray> mVertexArray;
        std::shared_ptr<VertexBuffer> mVertexBuffer;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
}


#endif //SANDBOX_APPLICATION_H
