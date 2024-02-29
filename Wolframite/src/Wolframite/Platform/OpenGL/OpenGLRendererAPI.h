//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_OPENGLRENDERERAPI_H
#define SANDBOX_OPENGLRENDERERAPI_H

#include "Wolframite/Renderer/RendererAPI.h"


namespace Tungsten {
    class OpenGLRendererAPI : public RendererAPI {
        virtual void Init() override;

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
        virtual void DrawArrays(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}


#endif //SANDBOX_OPENGLRENDERERAPI_H
