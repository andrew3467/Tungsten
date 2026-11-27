//
// Created by Andrew Graser on 11/24/2026.
//


#pragma once
#include "EditorPanel.h"
#include "Editor/CameraController.h"
#include "Tungsten/Renderer/Texture.h"

namespace TungstenEditor
{
    class ViewportPanel : public EditorPanel
    {
    public:
        ViewportPanel();

        void OnRender() override;
        void OnUpdate() override;

        std::string GetName() const override;




    private:
        std::shared_ptr<Tungsten::Texture2D> mFramebufferOutput;
        std::unique_ptr<CameraController> mCamController;

        bool mIsHovered = false;
        bool mIsFocused = false;
    };
}
