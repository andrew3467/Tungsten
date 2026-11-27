//
// Created by Andrew Graser on 11/9/2024.
//

#include "Renderer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include "Tungsten/Core/Light.h"
#include "Tungsten/Core/Material.h"

#include "Shader.h"
#include "Buffer.h"
#include "UniformBuffer.h"
#include "RenderQueue.h"
#include "Framebuffer.h"
#include "imstb_rectpack.h"

namespace Tungsten::Renderer
{
    constexpr int MAX_LIGHTS = 32;

    struct CameraData {
        glm::vec4 ViewPos;
        glm::mat4 ViewProj;
    };

    struct alignas(16) LightingData {
            DirectionalLight uDirLight;
            PointLight uPointLights[MAX_LIGHTS];
            int uNumPointLights;
    private:
            int padding[3];
    };

    struct RendererData
    {
        std::shared_ptr<UniformBuffer> CameraUBO;
        std::shared_ptr<UniformBuffer> LightingUBO;
    } sData;

    struct ImGUIDrawData {
        bool wireframe = false;
    } sImGuiData;

    static RenderQueue sRenderQueue;
    static std::shared_ptr<Framebuffer> sFrameBuffer;

    void InitData()
    {
        sData.CameraUBO = std::make_shared<UniformBuffer>(sizeof(CameraData), 0);
        sData.LightingUBO = std::make_shared<UniformBuffer>(sizeof(LightingData), 1);
    }

    void Init()
    {
        int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        TUNGSTEN_ASSERT(success, "Failed to load OpenGL functions");

        glEnable(GL_DEPTH_TEST);

        Shader::Init();

        InitData();

        //Setup UBOs in shaders
        for(auto& [_, shader] : Shader::GetShaders()) {
            glUniformBlockBinding(
                    shader->GetID(),
                    glGetUniformBlockIndex(shader->GetID(), "CameraData"),
                    0
                    );

            glUniformBlockBinding(
                    shader->GetID(),
                    glGetUniformBlockIndex(shader->GetID(), "LightingData"),
                    1
            );
        }


        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        sFrameBuffer = Framebuffer::Create({
            .Width = viewport[2],
            .Height = viewport[3],
        });

        TUNGSTEN_INFO("Renderer Initialized");
    }

    void SetClearColor(float r, float g, float b)
    {
        glClearColor(r, g, b, 1.0f);
    }

    void SetViewport(float x, float y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    glm::vec2 GetViewport()
    {
        int out[4];
        glGetIntegerv(GL_VIEWPORT, out);

        return {out[2], out[3]};
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void StartScene(const glm::mat4 &viewProj, const glm::vec3& viewPos) {
        sFrameBuffer->Bind();
        //sFrameBuffer->Clear();

        SetViewport(0,0, sFrameBuffer->Width(), sFrameBuffer->Height());


        CameraData data{
                glm::vec4(viewPos, 0),
                viewProj
        };

        sData.CameraUBO->SetData(&data, sizeof(CameraData));

        sFrameBuffer->Bind();
    }

    void EndScene() {
        sRenderQueue.Sort();
    }

    void SetLightData(const std::vector<PointLight>& lights, const DirectionalLight& dirLight) {
        LightingData data{};
        data.uDirLight = dirLight;
        data.uNumPointLights = std::min(static_cast<int>(lights.size()), MAX_LIGHTS);

        for(int i = 0; i < data.uNumPointLights; i++) {
            data.uPointLights[i] = lights[i];
        }

        sData.LightingUBO->SetData(&data, sizeof(LightingData));
    }

    void ExecuteRenderPipeline() {
        const auto& renderBatches = sRenderQueue.GetBatches();

        Clear();

        for (auto& batch : renderBatches)
        {
            batch.Material->Shader->Bind();
            batch.Material->Bind();

            batch.Mesh->GetVertexArray()->Bind();

            for (auto& model : batch.Transforms)
            {
                batch.Material->Shader->SetFloat4x4("uModel", model);
                glDrawElements(
                    GL_TRIANGLES,
                    batch.Mesh->GetVertexArray()->GetIndexBuffer().GetCount(),
                    GL_UNSIGNED_INT,
                    nullptr
                    );
            }
        }

        sRenderQueue.Clear();
        sFrameBuffer->Unbind();
    }

    void Submit(Mesh* mesh, Material* material, const glm::mat4& model) {
        sRenderQueue.Submit(mesh, material, model);
    }

    void ResizeFrameBuffer(int width, int height)
    {
        sFrameBuffer->Resize(width, height);
    }
} // Tungsten::Renderer