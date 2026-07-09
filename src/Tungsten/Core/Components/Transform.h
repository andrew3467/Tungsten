//
// Created by Andrew Graser on 7/7/2026.
//


#pragma once


#include <glm/glm.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Tungsten {
    struct Transform {
        glm::vec3 Position {0};
        glm::quat Rotation {1, 0, 0, 0};
        glm::vec3 Scale {1};


        void Rotate(const glm::vec3& axis, float angle) {
            glm::quat qrot = glm::angleAxis(angle, axis);
            Rotation *= qrot;
            Rotation = glm::normalize(Rotation);
        }

        glm::mat4 ModelMatrix() {
            glm::mat4 model(1.0f);
            model = glm::translate(model, Position);
            model *= glm::mat4_cast(Rotation);
            model = glm::scale(model, Scale);
            return model;
        }
    };
}