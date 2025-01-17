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
        std::shared_ptr<VertexArray> CubeVA;

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

        {
            Vertex vertices[] = {
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},  // A 0
                    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},  // B 1
                    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},  // C 2
                    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},  // D 3
                    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // E 4
                    {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},   // F 5
                    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},   // G 6
                    {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},   // H 7

                    {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},  // D 8
                    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // A 9
                    {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},  // E 10
                    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // H 11
                    {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},   // B 12
                    {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},   // C 13
                    {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }},   // G 14
                    {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},   // F 15

                    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},  // A 16
                    {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},   // B 17
                    {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},   // F 18
                    {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},  // E 19
                    {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},  // C 20
                    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},  // D 21
                    {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},  // H 22
                    {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},  // G 23
            };

            uint32_t indices[] = {
                // front and back
                0, 3, 2,
                2, 1, 0,
                4, 5, 6,
                6, 7 ,4,
                // left and right
                11, 8, 9,
                9, 10, 11,
                12, 13, 14,
                14, 15, 12,
                // bottom and top
                16, 17, 18,
                18, 19, 16,
                20, 21, 22,
                22, 23, 20
            };

            auto VB = VertexBuffer::Create(reinterpret_cast<float*>(&vertices), sizeof(vertices) / sizeof(float));

            BufferLayout layout = {
                {ShaderDataType::Float3, "aPosition"},
                {ShaderDataType::Float3, "aNormal"},
                {ShaderDataType::Float2, "aTexCoord"},
            };
            VB->SetLayout(layout);

            auto IB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));


            sData.CubeVA = VertexArray::Create();

            sData.CubeVA->AddVertexBuffer(VB);
            sData.CubeVA->SetIndexBuffer(IB);
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



#pragma region 3D

    void DrawCube(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &color)
    {
        DrawCube(position, scale, Texture2D::Get("Default"), color);
    }

    void DrawCube(const glm::vec3 &position, const glm::vec3 &scale, const std::shared_ptr<Texture2D> &texture)
    {
        DrawCube(position, scale, texture, glm::vec3(1));
    }

    void DrawCube(const glm::vec3 &position, const glm::vec3 &scale, const std::shared_ptr<Texture2D> &texture,
        const glm::vec3 &color)
    {
        const auto& shader = sData.UnlitShader;
        shader->Bind();

        shader->SetFloat3("uColor", color);

        texture->Bind(0);

        shader->SetFloat4x4("uModel",
            glm::scale(glm::translate(glm::mat4(1.0f), position), scale));
        shader->SetFloat4x4("uViewProj", sData.ViewProj);


        sData.CubeVA->Bind();

        //Draw Vertices
        glDrawElements(GL_TRIANGLES, sData.CubeVA->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    }

#pragma endregion

#pragma region 2D
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

#pragma endregion
} // Tungsten::Renderer