//
// Created by Andrew Graser on 6/24/2025.
//

#include "Mesh.h"

#include "../Renderer/Buffer.h"


namespace Tungsten {
    std::shared_ptr<Mesh> Mesh::Create(){
        return std::make_shared<Mesh>();
    }

    Mesh::Mesh() {
        mVA = VertexArray::Create();

        auto VB = VertexBuffer::Create(reinterpret_cast<float*>(&mVertices), mVertices.size());

        BufferLayout layout = {
                {ShaderDataType::Float3, "aPosition"},
                {ShaderDataType::Float3, "aNormal"},
                {ShaderDataType::Float2, "aTexCoord"},
        };
        VB->SetLayout(layout);

        auto IB = IndexBuffer::Create(mIndices.data(), mIndices.size());

        mVA->AddVertexBuffer(VB);
        mVA->SetIndexBuffer(IB);
    }

    void Mesh::RecalculateNormals() {

    }

    void Mesh::SetVertices(const std::vector<Vertex> &vertices) {
        mVertices = vertices;
        mDirty = true;
    }

    void Mesh::SetIndices(const std::vector<uint32_t> &indices) {
        mIndices = indices;
        mDirty = true;
    }

    const std::shared_ptr<VertexArray>& Mesh::GetVertexArray() {
        if(mDirty) {
            mVA->LoadNewBufferData(0, &mVertices[0].Position.x, mVertices.size() * (sizeof(Tungsten::Vertex) / sizeof(float)));
            mVA->LoadNewIndexData(mIndices.data(), mIndices.size());

            mDirty = false;
        }

        return mVA;
    }
}
