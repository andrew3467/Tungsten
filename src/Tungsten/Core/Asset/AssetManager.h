//
// Created by Andrew Graser on 7/12/2026.
//


#pragma once

namespace Tungsten {
    class AssetManager {
    public:
        template<typename T>
        std::shared_ptr<T> Load(const std::filesystem::path& path);
    };
}
