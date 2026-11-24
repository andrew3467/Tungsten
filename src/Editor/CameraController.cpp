//
// Created by Andrew Graser on 1/16/2025.
//

#include "CameraController.h"

#include "Tungsten.h"

CameraController::CameraController(const glm::vec3 &position)
{
    mCamera = Tungsten::Engine::MainCamera;
}

void CameraController::Update() {
    glm::vec3 moveVec = {};
    float velocity = Tungsten::Time::GetTime() * mMoveSpeed;

    if(Tungsten::Input::GetKey(GLFW_KEY_W)) {
        moveVec += mCamera->Forward() * velocity;
    }
    if(Tungsten::Input::GetKey(GLFW_KEY_S)) {
        moveVec -= mCamera->Forward() * velocity;
    }
    if(Tungsten::Input::GetKey(GLFW_KEY_A)) {
        moveVec -= mCamera->Right() * velocity;
    }
    if(Tungsten::Input::GetKey(GLFW_KEY_D)) {
        moveVec += mCamera->Right() * velocity;
    }
    if(Tungsten::Input::GetKey(GLFW_KEY_E)) {
        moveVec += mCamera->Up() * velocity;
    }
    if(Tungsten::Input::GetKey(GLFW_KEY_Q)) {
        moveVec -= mCamera->Up() * velocity;
    }

    mCamera->SetPosition(mCamera->GetPosition() + moveVec);

    static bool firstMouse = true;
    static bool firstScrollDown = true;

    if(Tungsten::Input::GetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE)) {
        Tungsten::Engine::Get().GetWindow().ToggleCursor(false);

        auto [x,y] = Tungsten::Input::GetMousePosition();
        if(firstMouse) {
            mPrevX = x;
            mPrevY = y;
            firstMouse = false;
        }

        if (firstScrollDown) {
            Tungsten::Input::SetMousePosition(mPrevX, mPrevY);
            firstScrollDown = false;
        }

        float xOffset = x - mPrevX;
        float yOffset = mPrevY - y;

        const float sensitivity = 2.f;
        mCamera->ProcessMouseMovement(xOffset, yOffset, sensitivity * Tungsten::Time::GetTime(), false);
        mPrevX = x;
        mPrevY = y;
    }else {
        Tungsten::Engine::Get().GetWindow().ToggleCursor(true);
        firstScrollDown = true;
    }
}
