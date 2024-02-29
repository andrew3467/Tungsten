//
// Created by Andrew Graser on 2/28/2024.
//

#include <Wolframite/Input/KeyCodes.h>
#include <Wolframite/Input/MouseButtonCodes.h>
#include "CameraController.h"
#include "Wolframite/Input/Input.h"


namespace Tungsten {

    CameraController::CameraController() {
        mCamera = std::make_unique<Camera>();
    }

    CameraController::~CameraController() {

    }

    void CameraController::OnUpdate(Timestep ts) {
        if(Input::IsKeyPressed(TUNGSTEN_KEY_W)){
            mPosition += mCamera->GetFront() * mMoveSpeed * ts.GetMilliseconds();
        }

        if(Input::IsKeyPressed(TUNGSTEN_KEY_S)){
            mPosition -= mCamera->GetFront() * mMoveSpeed * ts.GetMilliseconds();
        }

        if(Input::IsKeyPressed(TUNGSTEN_KEY_A)){
            mPosition -= mCamera->GetRight() * mMoveSpeed * ts.GetMilliseconds();
        }

        if(Input::IsKeyPressed(TUNGSTEN_KEY_D)){
            mPosition += mCamera->GetRight() * mMoveSpeed * ts.GetMilliseconds();
        }

        if(Input::IsKeyPressed(TUNGSTEN_KEY_E)){
            mPosition += mCamera->GetUp() * mMoveSpeed * ts.GetMilliseconds();
        }

        if(Input::IsKeyPressed(TUNGSTEN_KEY_Q)){
            mPosition -= mCamera->GetUp() * mMoveSpeed * ts.GetMilliseconds();
        }

        mCamera->SetPosition(mPosition);


        if(Input::IsMouseButtonPressed(TUNGSTEN_MOUSE_BUTTON_MIDDLE)){
            static float mouseX, mouseY;
            mouseX = Input::GetMouseX();
            mouseY = Input::GetMouseY();
            if (mFirstMouse) {
                mLastX = mouseX;
                mLastY = mouseY;
                mFirstMouse = false;
            }

            float xoffset = (mouseX - mLastX) * mSensitivity;
            float yoffset = (mLastY - mouseY) * mSensitivity;

            mLastX = mouseX;
            mLastY = mouseY;

            mYaw += xoffset;
            mPitch += yoffset;

            mPitch = glm::clamp(mPitch, -89.0f, 89.0f);

            mCamera->SetRotation({
                                         cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)),
                                         sin(glm::radians(mPitch)),
                                         sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))
                                 });
        }
    }
}