//
// Created by Andrew Graser on 7/7/2026.
//


#pragma once

#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

namespace Tungsten {
    struct Material {
        void Bind();

        std::shared_ptr<Shader> Shader;
        std::shared_ptr<Texture2D> Texture;

        float Shininess = 128.0f;
        float Metallic = 0.5f;
        float Roughness = 0.5f;

        glm::vec4 Albedo {1};
    };
}
