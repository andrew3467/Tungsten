//
// Created by Andrew Graser on 7/7/2026.
//

#include "UniformBuffer.h"


#include <glad/glad.h>

namespace Tungsten {

    UniformBuffer::UniformBuffer(size_t size, uint32_t binding) : mBinding(binding) {
        glGenBuffers(1, &mRendererID);

        glBindBuffer(GL_UNIFORM_BUFFER, mRendererID);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glBindBufferRange(GL_UNIFORM_BUFFER, binding, mRendererID, 0, size);
    }

    void UniformBuffer::SetData(const void *data, size_t size, size_t offset) {
        glBindBuffer(GL_UNIFORM_BUFFER, mRendererID);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }

    void UniformBuffer::Bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, mRendererID);
    }

    void UniformBuffer::Unbind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
} // Tungsten