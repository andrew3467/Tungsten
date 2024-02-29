//
// Created by Andrew Graser on 2/28/2024.
//


#include "Wolframite/Renderer/Camera.h"


#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Tungsten {

    Camera::Camera()
        : mAspectRatio(16.0f / 9.0f), mPosition(0.0f)
    {

    }

    Camera::Camera(float aspect, const glm::vec3 &position)
        : mAspectRatio(aspect), mPosition(position)
    {

    }

    Camera::~Camera() {

    }

    void Camera::CalculateMatrices() {
        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjection = glm::perspective(glm::radians(mFOV), mAspectRatio, mNear, mFar);
        mViewProjection = mProjection * mView;
    }

    void Camera::SetRotation(const glm::vec3 &rotation) {
        mFront = glm::normalize(rotation);

        mRight = glm::normalize(glm::cross(mFront, mWorldUp));
        mUp = glm::normalize(glm::cross(mRight, mFront));
    }
}