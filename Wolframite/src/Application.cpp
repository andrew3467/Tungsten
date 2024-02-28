//
// Created by Andrew Graser on 2/26/2024.
//

#include "Application.h"
#include "Wolframite/Core/Log.h"
#include "Wolframite/Core/Core.h"
#include <Wolframite/Events/ApplicationEvent.h>

#include <GLFW/glfw3.h>
#include <Glad/glad.h>


namespace Tungsten {
    Application* Application::mInstance = nullptr;

    Application::Application() {
        Log::Init();

        TUNGSTEN_CORE_ASSERT(!mInstance, "Only one instance of Application may exist")
        mInstance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        float squareVertices[4 * 3 * 2] = {
                -0.5f, -0.5f, 0.0f,         0.0f, 0.0f,
                0.5f, -0.5f, 0.0f,          1.0f, 0.0f,
                0.5f, 0.5f, 0.0f,        1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f,       0.0f, 1.0f,
        };

        uint32_t squareIndices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);



        //glGenBuffers(1, &mVBO);
        //glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
        mVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices) / sizeof(float)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));

        glGenBuffers(1, &mIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    }

    void Application::Run() {
        while (mRunning){
            //TODO Move to rendererAPI
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.1, 0.1, 0.1,1);

            //TODO MOVE TO SANDBOX
            glBindVertexArray(mVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


            for(auto layer : mLayerStack){
                layer->OnUpdate();
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
