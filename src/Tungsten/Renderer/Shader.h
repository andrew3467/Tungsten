//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once
#include <glm/glm.hpp>

namespace Tungsten
{
    class Shader {
    public:
        static std::shared_ptr<Shader> Create(const std::string& srcPath) {return std::make_shared<Shader>(srcPath);}
        static void Init();

        static std::shared_ptr<Shader> Get(const std::string& name);
        static std::unordered_map<std::string, std::shared_ptr<Shader>> GetShaders();

        [[nodiscard]] const std::string& GetName() const {return mName;}

        Shader(const std::string &srcPath);
        ~Shader();



        void Bind() const;
        void Unbind() const;


        uint32_t GetUniformLoc(const std::string& name);

        void SetBool(const std::string& name, bool value);

        void SetFloat(const std::string& name, float v);
        void SetFloat2(const std::string& name, const glm::vec2& v);
        void SetFloat3(const std::string& name, const glm::vec3& v);
        void SetFloat4(const std::string& name, const glm::vec4& v);

        void SetInt(const std::string& name, int v);
        void SetInt2(const std::string& name, const glm::ivec2& v);
        void SetInt3(const std::string& name, const glm::ivec3& v);
        void SetInt4(const std::string& name, const glm::ivec4& v);

        void SetFloat4x4(const std::string& name, const glm::mat4& v);
        void SetFloat3x3(const std::string& name, const glm::mat3& v);


    private:
        uint32_t mRendererID;
        std::string mFileLoc;
        std::string mName;

        std::unordered_map<std::string, uint32_t> mUniforms;
    };
}
