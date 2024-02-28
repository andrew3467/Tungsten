//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_TEXTURE_H
#define SANDBOX_TEXTURE_H


#include <cstdint>
#include <string>

namespace Tungsten {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual void Bind(uint32_t index = 0) = 0;
    };

    class Texture2D : public Texture {
    public:
        virtual ~Texture2D() = default;

        virtual void Bind(uint32_t index = 0) = 0;

        static Texture2D* Create(const std::string& path);
    };
}


#endif //SANDBOX_TEXTURE_H
