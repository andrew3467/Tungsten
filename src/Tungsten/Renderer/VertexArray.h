//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once

namespace Tungsten {
    class VertexBuffer;
    class IndexBuffer;

    class VertexArray {
    public:
        static std::shared_ptr<VertexArray> Create() {return std::make_shared<VertexArray>();}


    public:
        VertexArray();
        ~VertexArray() = default;

        void Bind();
        void Unbind();

        std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() { return mVertexBuffers;}
        IndexBuffer& GetIndexBuffer() { return *mIndexBuffer;}

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer> & vb, bool instanced = false);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);



    private:
        uint32_t mRendererID;
        uint32_t mVertexBufferIndex = 0;

        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
    }
