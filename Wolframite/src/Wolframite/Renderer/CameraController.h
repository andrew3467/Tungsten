//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_CAMERACONTROLLER_H
#define SANDBOX_CAMERACONTROLLER_H

#include <memory>

#include "Camera.h"
#include "Wolframite/Core/Timestep.h"

namespace Tungsten {
    class CameraController {
    public:
        CameraController();
        ~CameraController();


        Camera& GetCamera() const {return *mCamera;}


        void OnUpdate(Timestep ts);


    private:
        std::unique_ptr<Camera> mCamera;

        glm::vec3 mPosition = {0.0f, 0.0f, 0.0f};
        glm::vec3 mRotation = {0.0f, 0.0f, 0.0f};

        float mMoveSpeed = 0.05f;
        float mSensitivity = 1.0f;

        float mLastX, mLastY;
        bool mFirstMouse = true;
        float mYaw = 0.0f, mPitch = 0.0f;
    };
}


#endif //SANDBOX_CAMERACONTROLLER_H
