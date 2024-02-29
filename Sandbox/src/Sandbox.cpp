//
// Created by Andrew Graser on 2/26/2024.
//

#include "Wolframite/Tungsten.h"
#include "EntryPoint.h"


#include <imgui.h>


class ExampleLayer : public Tungsten::Layer {
public:
    ExampleLayer() {
        {
            float vertices[4 * 5] = {
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            };

            uint32_t indices[6] = {
                    0, 1, 2,
                    2, 3, 0
            };

            mSquareVA.reset(Tungsten::VertexArray::Create());

            std::shared_ptr<Tungsten::VertexBuffer> vertexBuffer;
            vertexBuffer.reset(Tungsten::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));
            vertexBuffer->SetLayout({
                                            {Tungsten::ShaderDataType::Float3, "aPosition"},
                                            {Tungsten::ShaderDataType::Float2, "aTexCoord"},
                                    });
            mSquareVA->AddVertexBuffer(vertexBuffer);

            std::shared_ptr<Tungsten::IndexBuffer> indexBuffer;
            indexBuffer.reset(Tungsten::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
            mSquareVA->SetIndexBuffer(indexBuffer);
        }

        {

            float vertices[] = {
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };

            mCubeVA.reset(Tungsten::VertexArray::Create());

            std::shared_ptr<Tungsten::VertexBuffer> vertexBuffer;
            vertexBuffer.reset(Tungsten::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));
            vertexBuffer->SetLayout({
                                            {Tungsten::ShaderDataType::Float3, "aPosition"},
                                            {Tungsten::ShaderDataType::Float2, "aTexCoord"},
                                    });
            mCubeVA->AddVertexBuffer(vertexBuffer);
        }




        mShader.reset(Tungsten::Shader::Create("../../Wolframite/src/Shaders/Basic_Unlit.glsl"));

        mTexture.reset(Tungsten::Texture2D::Create("../../assets/textures/marble_tiles_diff.jpg"));

        mShader->Bind();
        mShader->SetUniformInt("uTexture", 0);
    }

    ~ExampleLayer() {

    }

    void OnUpdate(Tungsten::Timestep ts) override {
        mCameraController.OnUpdate(ts);
    }

    void OnRender() override {
        Tungsten::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Tungsten::RenderCommand::Clear();


        Tungsten::Renderer::StartScene(mCameraController.GetCamera());

        mTexture->Bind();
        //Tungsten::Renderer::Submit(mShader, mSquareVA);

        Tungsten::Renderer::Submit(mShader, mCubeVA);

        Tungsten::Renderer::EndScene();
    }

    void OnImguiRender() override {
        ImGui::Begin("Material Editor");

        auto pos = mCameraController.GetCamera().GetPosition();
        auto rot = mCameraController.GetCamera().GetRotation();

        ImGui::SliderFloat3("Position", &pos.x, 0, 1);
        ImGui::SliderFloat3("Rotation", &rot.x, 0, 1);

        ImGui::End();
    }
    
private:
    Tungsten::CameraController mCameraController;

    std::shared_ptr<Tungsten::Texture2D> mTexture;

    std::shared_ptr<Tungsten::Shader> mShader;

    std::shared_ptr<Tungsten::VertexArray> mSquareVA;
    std::shared_ptr<Tungsten::VertexArray> mCubeVA;
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
