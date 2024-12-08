//
// Created by Andrew Graser on 11/9/2024.
//

#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"


namespace Tungsten::Renderer
{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };

    struct RendererData
    {
        std::shared_ptr<VertexArray> QuadVA;

        std::shared_ptr<Shader> UnlitShader;

        glm::mat4 ViewProj;
    } sData;

    void InitData()
    {
        {
            Vertex vertices[4] = {
                    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},   // A
                    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},   // B
                    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // C
                    {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},   // D
                };

            uint32_t indices[6] = {
                0, 1, 2,     //A, B, C
                2, 3, 0,     //C, D, A
            };

            auto VB = VertexBuffer::Create(reinterpret_cast<float*>(&vertices), sizeof(vertices) / sizeof(float));

            BufferLayout layout = {
                {ShaderDataType::Float3, "aPosition"},
                {ShaderDataType::Float3, "aNormal"},
                {ShaderDataType::Float2, "aTexCoord"},
            };
            VB->SetLayout(layout);

            auto IB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));


            sData.QuadVA = VertexArray::Create();

            sData.QuadVA->AddVertexBuffer(VB);
            sData.QuadVA->SetIndexBuffer(IB);
        }

        sData.UnlitShader = Shader::Get("Basic_Unlit");
    }


    void Init()
    {
        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        TUNGSTEN_ASSERT(success, "Failed to load OpenGL functions");

        Shader::Init();

        InitData();
    }

    void SetClearColor(float r, float g, float b)
    {
        glClearColor(r, g, b, 1.0f);
    }

    void SetViewport(float x, float y, float width, float height)
    {
        glViewport(x, y, width, height);
    }

    void ToggleWireframe()
    {
        static bool toggle = false;
        glPolygonMode(GL_FRONT_AND_BACK, toggle ? GL_LINE : GL_FILL);
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void StartScene(const glm::mat4 &viewProj)
    {
        sData.ViewProj = viewProj;
    }

    void DrawQuad(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec3 &color)
    {
        DrawQuad(glm::vec3(position, 0.0f), glm::vec3(scale, 1.0f), color);
    }

    void DrawQuad(const glm::vec2 &position, const glm::vec2 &scale, const std::shared_ptr<Texture2D> &texture)
    {
        DrawQuad(glm::vec3(position, 0.0f), glm::vec3(scale, 1.0f), texture);
    }

    void DrawQuad(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &color)
    {
        DrawQuad(position, scale, Texture2D::Get("Default"), color);
    }

    void DrawQuad(const glm::vec3 &position, const glm::vec3 &scale, const std::shared_ptr<Texture2D> &texture)
    {
        DrawQuad(position, scale, texture, glm::vec3(1));
    }

    void DrawQuad(const glm::vec3 &position, const glm::vec3 &scale, const std::shared_ptr<Texture2D> &texture,
        const glm::vec3 &color)
    {
        const auto& shader = sData.UnlitShader;
        shader->Bind();

        shader->SetFloat3("uColor", color);

        texture->Bind(0);

        shader->SetFloat4x4("uModel",
            glm::scale(glm::translate(glm::mat4(1.0f), position), scale));
        shader->SetFloat4x4("uViewProj", sData.ViewProj);


        sData.QuadVA->Bind();

        //Draw Vertices
        glDrawElements(GL_TRIANGLES, sData.QuadVA->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    }
} // Tungsten::Renderer