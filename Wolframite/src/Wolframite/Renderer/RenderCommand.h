//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_RENDERCOMMAND_H
#define SANDBOX_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Tungsten {
    class RenderCommand {
    public:
        static void SetClearColor(const glm::vec4& color) {
            mRendererAPI->SetClearColor(color);
        }

        static void Clear() {
            mRendererAPI->Clear();
        }

        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray){
            mRendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* mRendererAPI;
    };
}

#endif //SANDBOX_RENDERCOMMAND_H
