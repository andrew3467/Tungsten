//
// Created by Andrew Graser on 2/28/2024.
//

#include "OpenGLRendererAPI.h"

#include <Glad/glad.h>

void Tungsten::OpenGLRendererAPI::Init() {

}

void Tungsten::OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
    glEnable(GL_BLEND);
    glClearColor(color.x, color.y, color.z, color.w);
}

void Tungsten::OpenGLRendererAPI::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tungsten::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
