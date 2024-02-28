//
// Created by Andrew Graser on 2/27/2024.
//

#include "Wolframite/Platform/OpenGL/OpenGLBuffer.h"
#include "Buffer.h"


namespace Tungsten {

    VertexBuffer *VertexBuffer::Create(float *vertices, int count) {
        return new OpenGLVertexBuffer(vertices, count);
    }

    IndexBuffer *IndexBuffer::Create(uint32_t *indices, int count) {
        return new OpenGLIndexBuffer(indices, count);
    }
}