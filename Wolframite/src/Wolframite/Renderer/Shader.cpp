//
// Created by Andrew Graser on 2/27/2024.
//

#include "Wolframite/Platform/OpenGL/OpenGLShader.h"
#include "Shader.h"


namespace Tungsten {

    Shader *Shader::Create(const std::string &path) {
        return new OpenGLShader(path);
    }
}