//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_VERTEXARRAY_H
#define SANDBOX_VERTEXARRAY_H

namespace Tungsten {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static VertexArray* Create();
    };
}

#endif //SANDBOX_VERTEXARRAY_H
