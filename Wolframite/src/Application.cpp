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


namespace Tungsten {
    Application* Application::mInstance = nullptr;

    Application::Application() 
        : mCamera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
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

        mVertexArray.reset(VertexArray::Create());

        mVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices) / sizeof(float)));
        mVertexBuffer->SetLayout({
                                         {Tungsten::ShaderDataType::Float3, "aPosition"},
                                         {Tungsten::ShaderDataType::Float2, "aTexCoord"},
        });
        mVertexArray->AddVertexBuffer(mVertexBuffer);

        mIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        mShader.reset(Shader::Create("../../Wolframite/src/Shaders/Basic_Unlit.glsl"));

        mShader->Bind();
        mShader->SetUniformFloat4("uColor", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    }

    void Application::Run() {
        while (mRunning){
            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            //Input Polling
            if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_A)){
                mCameraPosition.x -= mCameraMoveSpeed * timestep;
            }

            if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_D)){
                mCameraPosition.x += mCameraMoveSpeed * timestep;
            }

            if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_S)){
                mCameraPosition.y -= mCameraMoveSpeed * timestep;
            }

            if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_W)){
                mCameraPosition.y += mCameraMoveSpeed * timestep;
            }

            if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_LEFT)){
                mCameraRotation += mCameraRotationSpeed * timestep;
            }

            if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_RIGHT)){
                mCameraRotation -= mCameraRotationSpeed * timestep;
            }

            mCamera.SetPosition(mCameraPosition);
            mCamera.SetRotation(mCameraRotation);
            

            //TODO Move to rendererAPI
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.1, 0.1, 0.1,1);

            //TODO MOVE TO SANDBOX
            mVertexArray->Bind();
            mShader->Bind();

            mShader->SetUniformMat4("uViewProjection", mCamera.GetViewProjectionMatrix());

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


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
