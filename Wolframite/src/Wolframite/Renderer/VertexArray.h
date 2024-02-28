//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_VERTEXARRAY_H
#define SANDBOX_VERTEXARRAY_H

#include "Wolframite/Renderer/Buffer.h"

namespace Tungsten {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer) = 0;
        virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>& buffer) = 0;

        static VertexArray* Create();
    };
}

#endif //SANDBOX_VERTEXARRAY_H
