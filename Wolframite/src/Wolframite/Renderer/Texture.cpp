//
// Created by Andrew Graser on 2/28/2024.
//

#include "Texture.h"
#include "Wolframite/Renderer/RendererAPI.h"
#include "Wolframite/Platform/OpenGL/OpenGLTexture.h"

namespace Tungsten {
    Texture2D *Tungsten::Texture2D::Create(const std::string &path) {
        switch (RendererAPI::GetAPI()) {
            case RendererAPI::API::None:                TUNGSTEN_CORE_ASSERT(false, "RendererAPI is not set!"); return nullptr;
            case RendererAPI::API::OpenGL:              return new OpenGLTexture2D(path);
        }
    }
}
