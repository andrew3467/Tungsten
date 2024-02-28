//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_OPENGLBUFFER_H
#define SANDBOX_OPENGLBUFFER_H

#include "Wolframite/Renderer/Buffer.h"


namespace Tungsten {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, int count);
        virtual ~OpenGLVertexBuffer() override;

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t mRendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, int count);
        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t mRendererID;
    };
}


#endif //SANDBOX_OPENGLBUFFER_H
