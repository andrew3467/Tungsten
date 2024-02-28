//
// Created by Andrew Graser on 2/28/2024.
//

#ifndef SANDBOX_OPENGLTEXTURE_H
#define SANDBOX_OPENGLTEXTURE_H


#include <Wolframite/Renderer/Texture.h>

namespace Tungsten {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D() override;

        virtual void Bind(uint32_t index = 0) override;

    private:
        uint32_t mWidth, mHeight;
        uint32_t mRendererID;
        std::string mPath;
    };
}


#endif //SANDBOX_OPENGLTEXTURE_H
