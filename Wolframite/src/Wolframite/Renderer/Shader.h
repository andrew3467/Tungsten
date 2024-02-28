//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_SHADER_H
#define SANDBOX_SHADER_H


#include <string>

namespace Tungsten {
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static Shader* Create(const std::string& path);
    };
}


#endif //SANDBOX_SHADER_H
