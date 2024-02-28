//
// Created by Andrew Graser on 2/27/2024.
//

#include "OpenGLGraphicsContext.h"
#include "Wolframite/Core/Core.h"
#include "Wolframite/Core/Log.h"


#include <Glad/glad.h>
#include <GLFW/glfw3.h>


namespace Tungsten {

    OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow *window)
        : mWindow(window)
    {
        TUNGSTEN_ASSERT(window, "Window must not be null")
    }

    void OpenGLGraphicsContext::Init() {
        glfwMakeContextCurrent(mWindow);

        int success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        TUNGSTEN_CORE_ASSERT(success, "Failed to load GLAD")

        TUNGSTEN_CORE_INFO("OpenGL Info:");
        TUNGSTEN_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        TUNGSTEN_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        TUNGSTEN_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLGraphicsContext::SwapBuffers() {
        glfwSwapBuffers(mWindow);
    }
}