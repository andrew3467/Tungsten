//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_INPUT_H
#define SANDBOX_INPUT_H

#include <utility>

namespace Tungsten {
    class Input {
    public:
        inline static bool IsKeyPressed(int keycode) {return mInstance->IsKeyPressedImpl(keycode);}

        inline static bool IsMouseButtonPressed(int button) {return mInstance->IsMouseButtonPressedImpl(button);}
        inline static float GetMouseX() {return mInstance->GetMouseXImpl();}
        inline static float GetMouseY() {return mInstance->GetMouseYImpl();}
        inline static std::pair<float, float> GetMousePos() {return mInstance->GetMousePosImpl();}

    protected:
        //Per platform implementations
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;

    public:
        static Input* mInstance;
    };
}

#endif //SANDBOX_INPUT_H
