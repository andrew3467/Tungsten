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

        const glm::mat4 &GetViewProjection() const { return mViewProjection; }
        const glm::mat4 &GetView() const { return mView; }
        const glm::mat4 &GetProjection() const { return mProjection; }

        const glm::vec3 &Forward() {return mFront;}
        const glm::vec3 &Up() {return mUp;}
        const glm::vec3 &Right() {return mRight;}

        const glm::vec3 &GetPosition() const { return mPosition; }

        void SetPosition(const glm::vec3 &position) {
            mPosition = position;
            RecalculateMatrices();
        }

        void SetRotation(const glm::vec3 &rotation)
        {
            mFront = glm::normalize(rotation);

            mRight = glm::normalize(glm::cross(mFront, glm::vec3(0.0f, 1.0f, 0.0f)));
            mUp = glm::normalize(glm::cross(mRight, mFront));
        }

        void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, bool constrainPitch);

    private:
        void RecalculateMatrices();

    private:
        glm::mat4 mView;
        glm::mat4 mProjection;
        glm::mat4 mViewProjection;

        glm::vec3 mPosition;
        glm::vec3 mFront = {0.0f, 0.0f, 1.0f};
        glm::vec3 mUp = {0.0f, 1.0f, 0.0f};
        glm::vec3 mRight = {1.0f, 0.0f, 0.0f};
        glm::vec3 mWorldUp = {0.0f, 1.0f, 0.0f};

        float mFOV = 60.0f;
        float mNear = 0.1f, mFar = 100.0f;

        float mYaw = -90.0f;
        float mPitch = 0.0f;
    };
}
