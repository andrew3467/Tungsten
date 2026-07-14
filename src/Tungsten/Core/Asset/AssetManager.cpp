//
// Created by Andrew Graser on 7/12/2026.
//

#include <Core/Mesh.h>
#include <Renderer/Texture.h>
#include <Renderer/Shader.h>
#include "AssetManager.h"


namespace Tungsten {
    template<>
    std::shared_ptr<Shader> AssetManager::Load(const std::filesystem::path &path) {
        return Shader::Create(path);
    }

    template<>
    std::shared_ptr<Texture2D> AssetManager::Load(const std::filesystem::path &path) {
        return Texture2D::Create(path);
    }

    template<>
    std::shared_ptr<Mesh> AssetManager::Load(const std::filesystem::path &path) {


        return nullptr;
    }
} // Tungsten