//
// Created by Andrew Graser on 7/7/2026.
//


#pragma once

#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

namespace Tungsten {
    struct Material {
        Material();
        ~Material() = default;

        void Bind();

        std::shared_ptr<Shader> Shader;
        std::shared_ptr<Texture2D> Texture;

        glm::vec4 Albedo {1};
    };
}
