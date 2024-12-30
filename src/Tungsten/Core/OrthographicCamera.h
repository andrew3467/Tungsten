//
// Created by Andrew Graser on 12/7/2024.
//


#pragma once

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

namespace Tungsten
{
    class OrthographicCamera {
    public:
        OrthographicCamera() : OrthographicCamera({0,0,0}) {}
        OrthographicCamera(const glm::vec3& pos);
        ~OrthographicCamera() = default;

        glm::mat4 GetProjection() const;

    private:
        glm::vec3 mPosition;

        glm::vec3 mUp = {0,1,0};

        glm::mat4 mOrthoMatrix{};
    };
}
