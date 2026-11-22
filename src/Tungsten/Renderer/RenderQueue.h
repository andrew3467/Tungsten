//
// Created by Andrew Graser on 11/21/2026.
//


#pragma once
#include <glm/glm.hpp>

namespace Tungsten
{
    struct Material;
    class Mesh;

    struct RenderCommand {
        Mesh* Mesh = nullptr;
        Material* Material = nullptr;
        glm::mat4 Model;
    };

    struct RenderBatch
    {
        Mesh* Mesh = nullptr;
        Material* Material = nullptr;

        std::vector<glm::mat4> Transforms;
    };

    class RenderQueue
    {
    public:
        void Submit(Mesh* mesh, Material* material, const glm::mat4& model);
        void Clear();
        void Sort();

        std::vector<RenderBatch> GetBatches() const {return mBatches;}

    private:
        std::vector<RenderCommand> mRenderCommands;
        std::vector<RenderBatch> mBatches;
    };
}
