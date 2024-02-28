//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_SHADER_H
#define SANDBOX_SHADER_H


#include <string>
#include <glm/glm.hpp>

namespace Tungsten {
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetUniformInt(const std::string& name, int v) = 0;
        virtual void SetUniformInt2(const std::string& name, const glm::ivec2& v) = 0;
        virtual void SetUniformInt3(const std::string& name, const glm::ivec3& v) = 0;
        virtual void SetUniformInt4(const std::string& name, const glm::ivec4& v) = 0;

        virtual void SetUniformFloat(const std::string& name, float v) = 0;
        virtual void SetUniformFloat2(const std::string& name, const glm::vec2& v) = 0;
        virtual void SetUniformFloat3(const std::string& name, const glm::vec3& v) = 0;
        virtual void SetUniformFloat4(const std::string& name, const glm::vec4& v) = 0;

        virtual void SetUniformMat3(const std::string& name, const glm::mat3& v) = 0;
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& v) = 0;

        static Shader* Create(const std::string& path);
    };
}


#endif //SANDBOX_SHADER_H
