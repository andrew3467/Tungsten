//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_RENDERER_H
#define SANDBOX_RENDERER_H

#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

namespace Tungsten {
     class Renderer {
     public:
         static void StartScene(Camera& camera);
         static void EndScene();

         static void Submit(std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray>& vertexArray);

     private:
         struct SceneData {
             glm::mat4 ViewProjection;
         };

         static SceneData* mSceneData;
     };
 }


#endif //SANDBOX_RENDERER_H
