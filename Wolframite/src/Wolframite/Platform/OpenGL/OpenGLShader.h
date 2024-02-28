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

        int GetLocation(const std::string& name);

        virtual void SetUniformInt(const std::string& name, int v) override;
        virtual void SetUniformInt2(const std::string& name, const glm::ivec2& v) override;
        virtual void SetUniformInt3(const std::string& name, const glm::ivec3& v) override;
        virtual void SetUniformInt4(const std::string& name, const glm::ivec4& v) override;

        virtual void SetUniformFloat(const std::string& name, float v) override;
        virtual void SetUniformFloat2(const std::string& name, const glm::vec2& v) override;
        virtual void SetUniformFloat3(const std::string& name, const glm::vec3& v) override;
        virtual void SetUniformFloat4(const std::string& name, const glm::vec4& v) override;

        virtual void SetUniformMat3(const std::string& name, const glm::mat3& v) override;
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& v) override;

    private:
        uint32_t mRendererID;
    };
}


#endif //SANDBOX_OPENGLSHADER_H
