//
// Created by Andrew Graser on 11/9/2024.
//

#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

namespace Tungsten::Renderer
{
    void Init()
    {
        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        TUNGSTEN_ASSERT(success, "Failed to load OpenGL functions");

        Shader::Init();

        auto shader = Shader::Get("Basic_Unlit");
    }

    void SetClearColor(float r, float g, float b)
    {
        glClearColor(r, g, b, 1.0f);
    }

    void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
} // Tungsten::Renderer