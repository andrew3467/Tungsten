//
// Created by Andrew Graser on 12/7/2024.
//

#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Engine.h"


namespace Tungsten
{
    Camera::Camera(const glm::vec3 &position)
            : mNear(0.1f), mFar(1000.0f) {
        SetPosition(position);


        RecalculateMatrices();
    }

    void Camera::RecalculateMatrices() {
        float aspect = Engine::Get().GetWindow().GetAspect();


        glm::vec3 front = {
                cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)),
                sin(glm::radians(mPitch)),
                sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))
        };

        mFront = glm::normalize(front);

        mRight = glm::normalize(glm::cross(mFront, mWorldUp));
        mUp = glm::normalize(glm::cross(mRight, mFront));

        mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
        mProjection = glm::perspective(glm::radians(mFOV), aspect, mNear, mFar);
        mViewProjection = mProjection * mView;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, float sensitivity, bool constrainPitch) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        mYaw += xoffset;
        mPitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            //mPitch = glm::clamp(mPitch, CAMERA_MIN_PITCH, CAMERA_MAX_PITCH);
        }

        RecalculateMatrices();
    }
}
