//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_GRAPHICSCONTEXT_H
#define SANDBOX_GRAPHICSCONTEXT_H

namespace Tungsten {
    class GraphicsContext {
    public:

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif //SANDBOX_GRAPHICSCONTEXT_H
