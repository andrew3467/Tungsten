//
// Created by Andrew Graser on 2/28/2024.
//

#include "OpenGLRendererAPI.h"

#include <Glad/glad.h>

namespace Tungsten {
    void OpenGLRendererAPI::Init() {

    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
        glEnable(GL_BLEND);
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::DrawArrays(const std::shared_ptr<VertexArray> &vertexArray) {
        glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexBuffers()[0]->GetCount());
    }
}
