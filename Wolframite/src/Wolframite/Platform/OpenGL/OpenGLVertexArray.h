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

        void AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer);
        void SetIndexBuffer(std::shared_ptr<IndexBuffer>& buffer);

        inline std::shared_ptr<IndexBuffer> GetIndexBuffer() {return mIndexBuffer;}

    private:
        uint32_t mRendererID;

        VertexAttribLayout mLayout;

        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
}


#endif //SANDBOX_OPENGLVERTEXARRAY_H
