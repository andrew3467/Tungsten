//
// Created by Andrew Graser on 2/28/2024.
//

#include "WindowsInput.h"
#include "Application.h"

#include <GLFW/glfw3.h>


namespace Tungsten {
    Input* Input::mInstance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float WindowsInput::GetMouseXImpl() {
        auto[x, y] = GetMousePosImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl() {
        auto[x, y] = GetMousePosImpl();
        return y;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl() {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { xpos, ypos };
    }
}