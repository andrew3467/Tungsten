//
// Created by Andrew Graser on 11/26/2024.
//

#include "BoxCollider2D.h"

namespace Tungsten
{
    BoxCollider2D::BoxCollider2D(const glm::vec2 &position, float width, float height)
        : Position(position), Width(width), Height(height)
    {

    }

    BoxCollider2D::BoxCollider2D(const BoxCollider2D &other)
        : Position(other.Position), Width(other.Width), Height(other.Height)
    {

    }

    bool BoxCollider2D::Collides(const BoxCollider2D &other) const
    {
        return Position.x < other.Position.x + other.Width &&
                Position.x + Width > other.Position.x &&
                    Position.y < other.Position.y + other.Height &&
                        Position.y + Height > other.Position.y;
    }
}
