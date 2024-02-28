//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_WINDOWSINPUT_H
#define SANDBOX_WINDOWSINPUT_H


#include "Wolframite/Core/Input.h"

namespace Tungsten {
    class WindowsInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
        virtual std::pair<float, float> GetMousePosImpl() override;
    };
}


#endif //SANDBOX_WINDOWSINPUT_H
