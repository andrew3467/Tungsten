//
// Created by Andrew Graser on 2/27/2024.
//


#include <Wolframite/Platform/OpenGL/OpenGLVertexArray.h>

namespace Tungsten {

    VertexArray *VertexArray::Create() {
        return new OpenGLVertexArray();
    }
}