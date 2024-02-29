//
// Created by Andrew Graser on 2/27/2024.
//

#include "OpenGLVertexArray.h"

#include <Glad/glad.h>

namespace Tungsten {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type){
        switch (type) {
            case ShaderDataType::Float:             return GL_FLOAT;
            case ShaderDataType::Float2:            return GL_FLOAT;
            case ShaderDataType::Float3:            return GL_FLOAT;
            case ShaderDataType::Float4:            return GL_FLOAT;

            case ShaderDataType::Int:               return GL_INT;
            case ShaderDataType::Int2:              return GL_INT;
            case ShaderDataType::Int3:              return GL_INT;
            case ShaderDataType::Int4:              return GL_INT;

            case ShaderDataType::Mat3:              return GL_FLOAT;
            case ShaderDataType::Mat4:              return GL_FLOAT;

            case ShaderDataType::Bool:              return GL_BOOL;
        }

        TUNGSTEN_CORE_ASSERT(false, "Unknown shader data type!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &mRendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &mRendererID);
    }

    void OpenGLVertexArray::Bind() {
        glBindVertexArray(mRendererID);
    }

    void OpenGLVertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer) {
        TUNGSTEN_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");


        glBindVertexArray(mRendererID);
        buffer->Bind();


        uint32_t index = 0;
        const auto& layout = buffer->GetLayout();
        for(const auto& element : layout){
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetElementCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void*)element.Offset);
            index++;
        }

        mVertexBuffers.push_back(buffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& buffer) {
        glBindVertexArray(mRendererID);
        buffer->Bind();

        mIndexBuffer = buffer;
        mHasIndexBuffer = true;
    }
}