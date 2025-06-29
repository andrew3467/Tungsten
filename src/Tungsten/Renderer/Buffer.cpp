//
// Created by Andrew Graser on 11/9/2024.
//

#include "Buffer.h"

#include <glad/glad.h>

namespace Tungsten {
    VertexBuffer::VertexBuffer(float *data, uint32_t count) {
        glGenBuffers(1, &mRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        SetData(data, count);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &mRendererID);
    }

    void VertexBuffer::SetData(float *data, uint32_t count) {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_DYNAMIC_DRAW);

        mCount = count;
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }




    IndexBuffer::IndexBuffer(uint32_t *data, uint32_t count)
    {
        glGenBuffers(1, &mRendererID);
        SetData(data, count);
    }

    void IndexBuffer::SetData(uint32_t *data, uint32_t count) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);

        mCount = count;
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &mRendererID);
    }

    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }

    void IndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}