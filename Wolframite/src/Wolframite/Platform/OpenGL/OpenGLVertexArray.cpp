//
// Created by Andrew Graser on 2/27/2024.
//

#include "OpenGLVertexArray.h"

#include <Glad/glad.h>

namespace Tungsten {

    OpenGLVertexArray::OpenGLVertexArray() {

    }

    OpenGLVertexArray::~OpenGLVertexArray() {

    }

    void OpenGLVertexArray::Bind() {
        glBindVertexArray(mRendererID);
    }

    void OpenGLVertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer) {

    }

    void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer) {

    }
}