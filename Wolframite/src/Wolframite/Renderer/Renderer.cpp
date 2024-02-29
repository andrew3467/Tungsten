//
// Created by Andrew Graser on 2/28/2024.
//

#include "Renderer.h"
#include "RenderCommand.h"

namespace Tungsten {

    Renderer::SceneData* Renderer::mSceneData = new Renderer::SceneData();

    void Renderer::StartScene(Camera &camera) {
        mSceneData->ViewProjection = camera.GetViewProjection();
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(std::shared_ptr<Shader> &shader, std::shared_ptr<VertexArray>& vertexArray) {
        shader->Bind();
        shader->SetUniformMat4("uViewProjection", mSceneData->ViewProjection);
        shader->SetUniformMat4("uTransform", glm::mat4(1.0f));

        vertexArray->Bind();
        if(vertexArray->HasIndexBuffer()){
            RenderCommand::DrawIndexed(vertexArray);
        } else {
            RenderCommand::DrawArrays(vertexArray);
        }
    }
}
