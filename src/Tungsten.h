//
// Created by Andrew Graser on 11/4/2024.
//


#pragma once

#ifdef _DEBUG
#include <glad/glad.h>

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
        abort();
    }
}

#define GL_ERROR_CHECK(func) do { \
            func; \
            CheckOpenGLError(#func, __FILE__, __LINE__); \
        } while (0)
#else
    #define GL_CHECK(stmt) stmt
#endif

#include "Tungsten/Core/Engine.h"
#include "Tungsten/Core/Input.h"

#include "Tungsten/Core/Light.h"
#include "Tungsten/Core/Mesh.h"
#include "Tungsten/Core/Vertex.h"

#include "Tungsten/Core/Logger.h"
#include "Tungsten/Core/Window.h"
#include "Tungsten/Core/Time.h"
#include "Tungsten/Core/Camera.h"

#include "Tungsten/Core/Physics/2D/BoxCollider2D.h"

#include "Tungsten/Renderer/Renderer.h"
#include "Tungsten/Renderer/Texture.h"
