//
// Created by Andrew Graser on 6/24/2025.
//


#pragma once

#include <glm/vec4.hpp>

namespace Tungsten {
    struct alignas(16) DirectionalLight {
        glm::vec4 Direction{0};
        glm::vec4 Color {1};
    };

    struct alignas(16) PointLight {
        glm::vec4 Position {2,2,2,0};
        glm::vec4 Color {1};

        float Constant = 1.0f;
        float Linear = 0.09f;
        float Quadratic = 0.032f;
    private:
        float padding;
    };
}