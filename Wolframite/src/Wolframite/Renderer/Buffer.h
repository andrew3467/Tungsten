//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_BUFFER_H
#define SANDBOX_BUFFER_H


#include <cstdint>

namespace Tungsten {
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static VertexBuffer *Create(float *vertices, int count);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static IndexBuffer *Create(uint32_t *indices, int count);
    };
}


#endif //SANDBOX_BUFFER_H
