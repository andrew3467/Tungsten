//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_APPLICATION_H
#define SANDBOX_APPLICATION_H


#include <memory>
#include <src/Wolframite/LayerStack.h>

#include "Wolframite/Core/Window.h"

namespace Tungsten {
    class Application {
    public:
        Application();
        virtual ~Application() = default;

        void Run();


        void PushLayer(Layer* layer);



        static Application* GetInstance() {return mInstance;}

    private:
        static Application* mInstance;

    private:

        bool mRunning = true;

        std::unique_ptr<Window> mWindow;
        std::unique_ptr<LayerStack> mLayerStack;
    };
}


#endif //SANDBOX_APPLICATION_H
