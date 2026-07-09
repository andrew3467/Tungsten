//
// Created by Andrew Graser on 11/9/2024.
//

#include "Renderer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <Core/Light.h>
#include <glm/gtc/type_ptr.hpp>
#include <Core/Material.h>

#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include "RenderState.h"

namespace Tungsten::Renderer
{
    struct CameraData {
        glm::vec4 ViewPos;
        glm::mat4 ViewProj;
    };

    struct alignas(16) LightingData {
            DirectionalLight uDirLight;
            PointLight uPointLights[32];
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

    void InitData()
    {
        sData.CameraUBO = std::make_shared<UniformBuffer>(sizeof(CameraData), 0);
        sData.LightingUBO = std::make_shared<UniformBuffer>(sizeof(LightingData), 1);
    }

    void OnImGUIDrawRenderer() {
        ImGui::Begin("Renderer Debug");

        if (ImGui::Checkbox("Wireframe", &sImGuiData.wireframe)) RenderState::ToggleWireframe(sImGuiData.wireframe);
    }


    void Init()
    {
        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
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

        TUNGSTEN_INFO("Renderer Initialized");
    }

    void SetClearColor(float r, float g, float b)
    {
        glClearColor(r, g, b, 1.0f);
    }

    void SetViewport(float x, float y, float width, float height)
    {
        glViewport(x, y, width, height);
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void StartScene(const glm::mat4 &viewProj, const glm::vec3& viewPos) {

        CameraData data{
                glm::vec4(viewPos, 0),
                viewProj
        };

        sData.CameraUBO->SetData(&data, sizeof(CameraData));
    }

    void SetLightData(const std::vector<PointLight>& lights, const DirectionalLight& dirLight) {
        LightingData data;
        data.uDirLight = dirLight;
        data.uNumPointLights = lights.size();

        for(int i = 0; i < lights.size(); i++) {
            data.uPointLights[i] = lights[i];
        }

        sData.LightingUBO->SetData(&data, sizeof(LightingData));
    }

    void Draw(Mesh& mesh, const glm::mat4& model, Material& material) {
        material.Shader->Bind();
        material.Bind();

        material.Shader->SetFloat4x4("uModel", model);

        mesh.GetVertexArray()->Bind();
        glDrawElements(GL_TRIANGLES, mesh.GetVertexArray()->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    }
} // Tungsten::Renderer