//
// Created by Andrew Graser on 1/16/2025.
//


#pragma once

#include "Tungsten/Core/Camera.h"

#include <glm/vec3.hpp>



class CameraController {
public:
    CameraController() : CameraController(glm::vec3(0)) {}
    CameraController(const glm::vec3& position);
    ~CameraController() = default;


    void Update();


    float* GetSpeed() {return &mMoveSpeed;}
    const glm::vec3& GetPosition() {return mCamera->GetPosition();}


private:
    std::shared_ptr<Tungsten::Camera> mCamera;

    float mMoveSpeed = 10.f;
    float mSensitivity = 20.f;

    float mPrevX, mPrevY;
};
