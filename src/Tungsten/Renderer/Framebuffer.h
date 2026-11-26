//
// Created by Andrew Graser on 11/24/2026.
//


#pragma once
#include "Texture.h"

namespace Tungsten
{
    struct FramebufferSpecification
    {
        int Width, Height;
    };

    class Framebuffer
    {
    public:
        static std::shared_ptr<Framebuffer> Create(FramebufferSpecification spec) {return std::make_shared<Framebuffer>(spec);}


    public:
        Framebuffer(FramebufferSpecification spec);
        ~Framebuffer() = default;

        void Resize(int width, int height);
        void Invalidate();

        int Width() const {return mSpec.Width;}
        int Height() const {return mSpec.Height;}

        void Bind() const;
        void Unbind();

        void Clear();


    private:
        uint32_t mRendererID;
        uint32_t mDepthAttachment;
        FramebufferSpecification mSpec;

        std::shared_ptr<Texture2D> mOutputTexture;
    };
}
