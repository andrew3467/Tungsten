//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once
#include <glm/glm.hpp>

namespace Tungsten
{
    namespace Renderer
    {
        void Init();

        void SetClearColor(float r, float g, float b);
        void SetViewport(float x, float y, float width, float height);

        void Clear();

        void DrawQuad(const glm::vec3& position, const glm::vec3& scale);
    }
}
