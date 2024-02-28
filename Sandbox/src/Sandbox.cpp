//
// Created by Andrew Graser on 2/26/2024.
//

#include "Wolframite/Tungsten.h"

#include <imgui.h>


class ExampleLayer : public Tungsten::Layer {
public:
    ExampleLayer()
        : mCamera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
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

        mVertexArray.reset(Tungsten::VertexArray::Create());

        std::shared_ptr<Tungsten::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Tungsten::VertexBuffer::Create(squareVertices, sizeof(squareVertices) / sizeof(float)));
        vertexBuffer->SetLayout({
                                        {Tungsten::ShaderDataType::Float3, "aPosition"},
                                        {Tungsten::ShaderDataType::Float2, "aTexCoord"},
                                });
        mVertexArray->AddVertexBuffer(vertexBuffer);

        std::shared_ptr<Tungsten::IndexBuffer> indexBuffer;
        indexBuffer.reset(Tungsten::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        mVertexArray->SetIndexBuffer(indexBuffer);

        mShader.reset(Tungsten::Shader::Create("../../Wolframite/src/Shaders/Basic_Unlit.glsl"));

        mTexture.reset(Tungsten::Texture2D::Create("../../assets/textures/marble_tiles_diff.jpg"));

        mShader->Bind();
        mShader->SetUniformInt("uTexture", 0);
    }

    ~ExampleLayer() {

    }

    void OnUpdate(Tungsten::Timestep ts) override {
        //Input Polling
        if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_A)){
            mCameraPosition.x -= mCameraMoveSpeed * ts;
        }

        if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_D)){
            mCameraPosition.x += mCameraMoveSpeed * ts;
        }

        if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_S)){
            mCameraPosition.y -= mCameraMoveSpeed * ts;
        }

        if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_W)){
            mCameraPosition.y += mCameraMoveSpeed * ts;
        }

        if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_LEFT)){
            mCameraRotation += mCameraRotationSpeed * ts;
        }

        if(Tungsten::Input::IsKeyPressed(TUNGSTEN_KEY_RIGHT)){
            mCameraRotation -= mCameraRotationSpeed * ts;
        }

        mCamera.SetPosition(mCameraPosition);
        mCamera.SetRotation(mCameraRotation);
    }

    void OnRender() override {
        Tungsten::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Tungsten::RenderCommand::Clear();

        Tungsten::Renderer::StartScene(mCamera);

        mTexture->Bind();
        Tungsten::Renderer::Submit(mShader, mVertexArray);

        Tungsten::Renderer::EndScene();
    }

    void OnImguiRender() override {
        ImGui::Begin("Material Editor");

        ImGui::Text("Test");

        ImGui::End();
    }
    
private:
    Tungsten::Camera mCamera;
    glm::vec3 mCameraPosition = {0.0f, 0.0f, 0.0f};
    float mCameraMoveSpeed = 2.5f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 180.0f;

    std::shared_ptr<Tungsten::Texture2D> mTexture;

    std::shared_ptr<Tungsten::Shader> mShader;

    std::shared_ptr<Tungsten::VertexArray> mVertexArray;
};


class Sandbox : public Tungsten::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer);
    }

    ~Sandbox() override {

    }
};

Tungsten::Application* CreateApplication() {
    return new Sandbox;
}
