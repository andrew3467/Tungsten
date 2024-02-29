//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_RENDERERAPI_H
#define SANDBOX_RENDERERAPI_H


#include <glm/vec4.hpp>
#include "VertexArray.h"

namespace Tungsten {
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };


        virtual void Init() = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        virtual void DrawArrays(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() {return sAPI;}


    private:
        static API sAPI;
    };
}


#endif //SANDBOX_RENDERERAPI_H
