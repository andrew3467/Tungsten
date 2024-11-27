//
// Created by Andrew Graser on 11/26/2024.
//


#pragma once
#include <glm/vec2.hpp>

namespace Tungsten
{
    struct BoxCollider2D {
        BoxCollider2D(const glm::vec2& position, float width, float height);
        BoxCollider2D(const BoxCollider2D& other);
        ~BoxCollider2D() = default;

        bool Collides(const BoxCollider2D& other) const;

        glm::vec2 Size() const {return {Width, Height};}

        glm::vec2 Position;
        float Width;
        float Height;
    };
}
