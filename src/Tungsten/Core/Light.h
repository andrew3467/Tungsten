//
// Created by Andrew Graser on 6/24/2025.
//


#pragma once

#include <glm/vec3.hpp>

namespace Tungsten {
    struct DirectionalLight {
        glm::vec3 Direction;
        glm::vec3 Color {1,1,1};
    };

    struct PointLight {
        glm::vec3 Position;
        glm::vec3 Color {1,1,1};

        float Constant = 1.0f;
        float Linear = 0.09f;
        float Quadratic = 0.032f;
    };
}