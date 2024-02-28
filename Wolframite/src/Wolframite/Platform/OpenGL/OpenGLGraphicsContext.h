//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_OPENGLGRAPHICSCONTEXT_H
#define SANDBOX_OPENGLGRAPHICSCONTEXT_H


#include "Wolframite/Renderer/GraphicsContext.h"

class GLFWwindow;

namespace Tungsten {
    class OpenGLGraphicsContext : public GraphicsContext {
    public:
        OpenGLGraphicsContext(GLFWwindow* window);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* mWindow;
    };
}


#endif //SANDBOX_OPENGLGRAPHICSCONTEXT_H
