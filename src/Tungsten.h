//
// Created by Andrew Graser on 11/4/2024.
//


#pragma once



#include "Tungsten/Core/Logger.h"
#include "Tungsten/Core/Window.h"

#include "Tungsten/Renderer/Renderer.h"



namespace Tungsten
{
    Window Init(const std::string& title)
    {
        Logger::Init();
        Tungsten::InitGLFW();

        Window defaultWindow({1280, 720, title});

        Renderer::Init();


        return defaultWindow;
    }
}