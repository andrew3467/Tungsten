//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once
#include <glm/glm.hpp>

namespace Tungsten
{
    class Texture2D;
}

namespace Tungsten
{
    namespace Renderer
    {
        void Init();

        void SetClearColor(float r, float g, float b);
        void SetViewport(float x, float y, float width, float height);

        void ToggleWireframe();

        void Clear();

        void StartScene(const glm::mat4& viewProj);
        void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec3& color);
        void DrawQuad(const glm::vec2 &position, const glm::vec2 &scale, const std::shared_ptr<Texture2D> &texture);

        void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color);
        void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Texture2D>& texture);
        void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Texture2D>& texture, const glm::vec3& color);
    }
}
