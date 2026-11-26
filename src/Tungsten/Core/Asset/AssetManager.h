//
// Created by Andrew Graser on 7/12/2026.
//


#pragma once

#include "Asset.h"

namespace Tungsten {
    class AssetManager {
    public:
        template<typename T>
        std::shared_ptr<T> Load(const std::filesystem::path& path) {
            if(path.empty()) return nullptr;

            auto p = std::filesystem::path(ASSET_DIR) / path;

            if(mPathMap.contains(p)) return Get<T>(mPathMap[p]);

            TUNGSTEN_INFO("Loading file at {0}", p.string());

            std::shared_ptr<T> asset = T::Create(p);

            mAssetMap.emplace(asset->Handle(), asset);
            mNameMap.emplace(asset->GetName(), asset->Handle());
            mPathMap.emplace(p, asset->Handle());

            return std::static_pointer_cast<T>(asset);
        }

        template<typename T>
        std::shared_ptr<T> Get(const AssetHandle& handle) {
            if(!mAssetMap.contains(handle)) return nullptr;

            return std::static_pointer_cast<T>(mAssetMap[handle]);
        }

        template<typename T>
        std::shared_ptr<T> Get(const std::string& name) {
            if(mNameMap.contains(name)) return Get<T>(mNameMap[name]);

            TUNGSTEN_ERROR("Tried To load asset: {}", name);
            return nullptr;
        }

        template<typename T, typename... Args>
        requires std::derived_from<T, Asset>
        std::shared_ptr<T> Create(Args&&... args)
        {
            std::shared_ptr<T> asset = T::Create(std::forward<Args>(args)...);

            mAssetMap.emplace(asset->Handle(), asset);
            mNameMap.emplace(asset->GetName(), asset->Handle());

            return asset;
        }

    private:
        std::unordered_map<AssetHandle, std::shared_ptr<Asset>> mAssetMap;
        std::unordered_map<std::string, AssetHandle> mNameMap;
        std::unordered_map<std::filesystem::path, AssetHandle> mPathMap;
    };
}
