//
// Created by Andrew Graser on 12/7/2024.
//


#pragma once

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

namespace Tungsten
{
    class Camera {
    public:
        Camera() : Camera({0, 0, 0}) {}
        Camera(const glm::vec3& pos);
        ~Camera() = default;

        glm::mat4 GetProjection() const;

    private:
        glm::vec3 mPosition;

        glm::vec3 mUp = {0,1,0};

        glm::mat4 mOrthoMatrix{};
    };
}
