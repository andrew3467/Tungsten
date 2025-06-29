//
// Created by Andrew Graser on 6/27/2025.
//


#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Tungsten {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
    };
}