//
// Created by Andrew Graser on 11/9/2024.
//

#include "VertexArray.h"

#include <glad/glad.h>

#include "Buffer.h"

namespace Tungsten {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
        }

        TUNGSTEN_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &mRendererID);
        glBindVertexArray(mRendererID);
    }

    void VertexArray::Bind() {
        glBindVertexArray(mRendererID);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer, bool instanced) {
        mVertexBuffers.push_back(buffer);

        glBindVertexArray(mRendererID);
        buffer->Bind();


        const auto& layout = buffer->GetLayout();
        for(const auto& element : layout) {
            switch (element.Type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(mVertexBufferIndex);
                    glVertexAttribPointer(mVertexBufferIndex,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        element.Normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        (const void*)element.Offset);
                    mVertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(mVertexBufferIndex);
                    glVertexAttribIPointer(mVertexBufferIndex,
                        element.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        layout.GetStride(),
                        (const void*)element.Offset);

                    if(instanced)
                        glVertexAttribDivisor(0,1);

                    mVertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint8_t count = element.GetComponentCount();
                    for (uint8_t i = 0; i < count; i++)
                    {
                        glEnableVertexAttribArray(mVertexBufferIndex);
                        glVertexAttribPointer(mVertexBufferIndex,
                            count,
                            ShaderDataTypeToOpenGLBaseType(element.Type),
                            element.Normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            (const void*)(element.Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(mVertexBufferIndex, 1);
                        mVertexBufferIndex++;
                    }

                    if(instanced)
                        glVertexAttribDivisor(0,1);
                    break;
                }
                default:
                    TUNGSTEN_ASSERT(false, "Unknown ShaderDataType!");
            }
        }
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer) {
        mIndexBuffer = buffer;

        glBindVertexArray(mRendererID);
        buffer->Bind();
    }

    void VertexArray::LoadNewBufferData(int targetBufferIndex, float *data, uint32_t count) {
        glBindVertexArray(mRendererID);
        mVertexBuffers[targetBufferIndex]->SetData(data, count);
    }

    void VertexArray::LoadNewIndexData(uint32_t* data, uint32_t count) {
        glBindVertexArray(mRendererID);
        mIndexBuffer->SetData(data, count);
    }
} // Tungsten