//
// Created by Andrew Graser on 11/24/2026.
//

#include "Framebuffer.h"

#include <glad/glad.h>

#include "Tungsten/Core/Engine.h"

namespace Tungsten
{
    Framebuffer::Framebuffer(FramebufferSpecification spec)
        : mSpec(spec)
    {
        mOutputTexture = Engine::Get().Assets().Create<Texture2D>(mSpec.Width, mSpec.Height, "FramebufferOutput");

        Invalidate();
    }

    void Framebuffer::Resize(int width, int height)
    {
        if (width == 0 || height == 0) return;
        if (width == mSpec.Width || height == mSpec.Height) return;

        mSpec.Width = width;
        mSpec.Height = height;

        Engine::MainCamera->RecalculateMatrices();

        Invalidate();
    }

    void Framebuffer::Invalidate()
    {
        if (mRendererID)
        {
            glDeleteFramebuffers(1, &mRendererID);
            glDeleteRenderbuffers(1, &mDepthAttachment);
        }

        glCreateFramebuffers(1, &mRendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);

        //Reset Output Texture

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            mOutputTexture->GetID(),
            0
            );

        glCreateRenderbuffers(1, &mDepthAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthAttachment);

        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH24_STENCIL8,
            mSpec.Width,
            mSpec.Height
            );

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            TUNGSTEN_ERROR("Framebuffer is incomplete!");

        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        mOutputTexture->Resize(mSpec.Width, mSpec.Height);
    }

    void Framebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Clear()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
