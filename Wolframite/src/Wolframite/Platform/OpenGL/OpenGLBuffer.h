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

        virtual void SetLayout(const BufferLayout& layout) override {mLayout = layout;}
        virtual const BufferLayout& GetLayout() const { return mLayout;}

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t mRendererID;
        BufferLayout mLayout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, int count);
        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual uint32_t GetCount() override;

    private:
        uint32_t mRendererID;
        uint32_t mCount;
    };
}


#endif //SANDBOX_OPENGLBUFFER_H
