//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_OPENGLSHADER_H
#define SANDBOX_OPENGLSHADER_H

#include <cstdint>
#include "Wolframite/Renderer/Shader.h"


#define TUNGSTEN_VERTEX_SHADER   0
#define TUNGSTEN_FRAGMENT_SHADER 1
#define TUNGSTEN_GEOMETRY_SHADER 2


namespace Tungsten {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& path);
        virtual ~OpenGLShader() override;

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        uint32_t mRendererID;
    };
}


#endif //SANDBOX_OPENGLSHADER_H
