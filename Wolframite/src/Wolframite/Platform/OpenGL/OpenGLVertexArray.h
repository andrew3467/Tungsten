//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_OPENGLVERTEXARRAY_H
#define SANDBOX_OPENGLVERTEXARRAY_H

#include <Wolframite/Renderer/Buffer.h>
#include <memory>
#include <vector>
#include "Wolframite/Renderer/VertexArray.h"


namespace Tungsten {
    struct VertexAttribLayout {

    };


    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() override;
        virtual void Unbind() override;

        void AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer>& buffer) override;

        virtual bool HasIndexBuffer() const override {return mHasIndexBuffer;}

        inline std::shared_ptr<IndexBuffer>& GetIndexBuffer() {return mIndexBuffer;}
        virtual std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override {return mVertexBuffers;}

    private:
        uint32_t mRendererID;

        VertexAttribLayout mLayout;

        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;

        bool mHasIndexBuffer = false;
    };
}


#endif //SANDBOX_OPENGLVERTEXARRAY_H
