//
// Created by Andrew Graser on 7/4/2026.
//



#include "RenderState.h"

#include "glad/glad.h"



namespace Tungsten {
    void RenderState::ToggleWireframe(bool active) {
        glPolygonMode(GL_FRONT_AND_BACK, active ? GL_LINE : GL_FILL);
    }
} // Tungsten