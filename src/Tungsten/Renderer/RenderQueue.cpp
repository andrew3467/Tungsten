//
// Created by Andrew Graser on 11/21/2026.
//

#include "RenderQueue.h"

namespace Tungsten
{
    void RenderQueue::Submit(Mesh* mesh, Material* material, const glm::mat4& model)
    {
        mRenderCommands.emplace_back(mesh, material, model);
    }

    void RenderQueue::Clear()
    {
        mRenderCommands.clear();
        mBatches.clear();
    }

    void RenderQueue::Sort()
    {
        for (auto& cmd : mRenderCommands)
        {
            bool found = false;

            for (auto& batch : mBatches)
            {
                if (batch.Material == cmd.Material && batch.Mesh == cmd.Mesh)
                {
                    batch.Transforms.push_back(cmd.Model);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                RenderBatch batch;
                batch.Material = cmd.Material;
                batch.Mesh = cmd.Mesh;
                batch.Transforms.push_back(cmd.Model);
                mBatches.push_back(std::move(batch));
            }
        }
    }
}
