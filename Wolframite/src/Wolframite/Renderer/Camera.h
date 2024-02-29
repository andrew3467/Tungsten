//
// Created by Andrew Graser on 2/28/2024.
//


#ifndef SANDBOX_CAMERA_H
#define SANDBOX_CAMERA_H

#include <glm/glm.hpp>

namespace Tungsten {
    class Camera {
    public:
        Camera(float aspect, const glm::vec3& position);
        Camera();
        ~Camera();

        void SetPosition(const glm::vec3& position) {mPosition = position; CalculateMatrices();}
        void SetRotation(const glm::vec3& rotation);

        const glm::vec3& GetFront() const {return mFront;}
        const glm::vec3& GetUp() const {return mUp;}
        const glm::vec3& GetRight() const {return mRight;}

        const glm::vec3& GetPosition() const {return mPosition;}
        const glm::vec3& GetRotation() const {return mFront;}

        const glm::mat4& GetProjection() {return mProjection;}
        const glm::mat4& GetView() {return mView;}
        const glm::mat4& GetViewProjection() {return mViewProjection;}

    private:
        void CalculateMatrices();


    private:
        glm::mat4 mProjection;
        glm::mat4 mView;
        glm::mat4 mViewProjection;

        glm::vec3 mPosition = {0.0f, 0.0f, 0.0f};
        glm::vec3 mFront = {0.0f, 0.0f, -1.0f};
        glm::vec3 mUp = {0.0f, 1.0f, 0.0f};
        glm::vec3 mRight = {1.0f, 0.0f,0.0f};
        glm::vec3 mWorldUp = {0.0f, 1.0f, 0.0f};

        float mFOV = 60.0f;
        float mAspectRatio;
        float mNear = 0.1f, mFar = 100.0f;
    };
}


#endif //SANDBOX_CAMERA_H
