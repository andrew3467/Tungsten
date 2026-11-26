//
// Created by Andrew Graser on 8/3/2026.
//


#pragma once


#include <filesystem>


#include "../Util/UUID.h"



namespace Tungsten {
    using AssetHandle = UUID;

    enum class AssetType {
        Texture,
        Mesh,
        Shader
    };


    struct AssetMetaData {
        AssetType Type;
        std::filesystem::path Path;
    };

    class Asset {
    public:
        ~Asset() = default;

        const AssetHandle& Handle() const {return mUUID;}

    protected:
        std::string mName;

    private:
        AssetHandle mUUID;
    };
}
