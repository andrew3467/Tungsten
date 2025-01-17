//
// Created by Andrew Graser on 1/16/2025.
//

#include <GLFW/glfw3.h>
#include "Input.h"
#include "Engine.h"


namespace Tungsten {
    bool Input::GetKey(uint32_t keycode) {
        return glfwGetKey((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), keycode);
    }

    bool Input::GetMouseButton(uint32_t mousecode) {
        return glfwGetMouseButton((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), mousecode);
    }

    std::pair<double, double> Input::GetMousePosition() {
        double x,y;
        glfwGetCursorPos((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), &x, &y);
        return std::make_pair(x, y);
    }

    void Input::SetMousePosition(double x, double y) {
        glfwSetCursorPos((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), x, y);
    }
}