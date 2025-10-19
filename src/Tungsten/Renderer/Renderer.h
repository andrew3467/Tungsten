//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once
#include <glm/glm.hpp>

#include "../Core/Light.h"
#include "../Core/Mesh.h"
#include "VertexArray.h"


namespace Tungsten
{
    class Texture2D;



    namespace Renderer
    {
        void Init();

        void OnImGUIDrawRenderer();

        void SetClearColor(float r, float g, float b);
        void SetViewport(float x, float y, float width, float height);

        void ToggleWireframe();

        void Clear();

        void StartScene(const glm::mat4& viewProj);

        void SetDirectionalLightData(DirectionalLight dirLight);
        void SetPointLightData(std::vector<PointLight> lights);
        void UpdateViewPos(const glm::vec3 &position);

        void Draw(const std::shared_ptr<VertexArray>& VA, const glm::vec3& position);

        void Draw(const std::shared_ptr<Mesh>& mesh, const glm::vec3& position);

#pragma region 3D

        void DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color, bool wireframe = false);
        void DrawCube(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Texture2D>& texture);
        void DrawCube(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Texture2D>& texture, const glm::vec3& color);


#pragma endregion

#pragma region 2D
        void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec3& color);
        void DrawQuad(const glm::vec2 &position, const glm::vec2 &scale, const std::shared_ptr<Texture2D> &texture);

        void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color);
        void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Texture2D>& texture);
        void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Texture2D>& texture, const glm::vec3& color);

#pragma endregion

    }
}
