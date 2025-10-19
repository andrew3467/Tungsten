//
// Created by Andrew Graser on 6/24/2025.
//

#include <glm/geometric.hpp>
#include <glm/mat3x3.hpp>
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

///Loop over all triangles in mesh
///Calculate normal for each triangle
///Add normal to each vertex within triangle
///normalize final result
    void Mesh::RecalculateNormals() {
        for(int i = 0; i < mIndices.size(); i+=3) {
            auto& v0 = mVertices[mIndices[i]];
            auto& v1 = mVertices[mIndices[i + 1]];
            auto& v2 = mVertices[mIndices[i + 2]];

            glm::vec3 edge1 = v1.Position - v0.Position;
            glm::vec3 edge2 = v2.Position - v0.Position;

            glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

            v0.Normal += faceNormal;
            v1.Normal += faceNormal;
            v2.Normal += faceNormal;
        }
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
