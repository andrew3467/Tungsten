//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_CAMERA_H
#define SANDBOX_CAMERA_H

#include <glm/glm.hpp>

namespace Tungsten {
    class Camera {
    public:
        Camera(float left, float right, float bottom, float top);
        ~Camera();


        const glm::vec3& GetPosition() const {return mPosition;}
        float GetRotation() const {return mRotation;}

        void SetPosition(const glm::vec3& position){mPosition = position; RecalculateViewMatrix();}
        void SetRotation(const float rotation){mRotation = rotation; RecalculateViewMatrix();}

        const glm::mat4& GetProjectionMatrix() const {return mProjectionMatrix;}
        const glm::mat4& GetViewMatrix() const {return mViewMatrix;}
        const glm::mat4& GetViewProjectionMatrix() const {return mViewProjectionMatrix;}



    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 mProjectionMatrix;
        glm::mat4 mViewMatrix;
        glm::mat4 mViewProjectionMatrix;

        glm::vec3 mPosition;
        float mRotation;
    };
}


#endif //SANDBOX_CAMERA_H
