//
// Created by Andrew Graser on 2/28/2024.
//

#include <Wolframite/Platform/OpenGL/OpenGLRendererAPI.h>
#include "Wolframite/Renderer/RenderCommand.h"

namespace Tungsten {
    RendererAPI* RenderCommand::mRendererAPI = new OpenGLRendererAPI;
}