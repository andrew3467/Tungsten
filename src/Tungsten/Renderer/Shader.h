//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once

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


    private:
        uint32_t mRendererID;
        std::string mFileLoc;
        std::string mName;

        std::unordered_map<std::string, uint32_t> mUniforms;
    };
}
