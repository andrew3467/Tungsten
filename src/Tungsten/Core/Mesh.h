//
// Created by Andrew Graser on 6/24/2025.
//


#pragma once


#include "../Renderer/VertexArray.h"
#include "Vertex.h"

namespace Tungsten {
    class Mesh {
    public:
        static std::shared_ptr<Mesh> Create();


        Mesh();
        ~Mesh() = default;


        void SetVertices(const std::vector<Vertex>& vertices);
        void SetIndices(const std::vector<uint32_t>& indices);

        const std::shared_ptr<VertexArray>& GetVertexArray();

        const uint32_t GetVertexCount() const {return mVertices.size();}


        void RecalculateNormals();

    private:
        bool mDirty = true;

        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;

        std::shared_ptr<VertexArray> mVA;
    };
}
