//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once
#include <glm/glm.hpp>

#include "../Core/Material.h"
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

        void Clear();

        void StartScene(const glm::mat4& viewProj, const glm::vec3& viewPos);

        void SetLightData(const std::vector<PointLight>& lights, const DirectionalLight& dirLight);

        void Draw(Mesh& mesh, const glm::mat4& model, Material& material);
    }
}
