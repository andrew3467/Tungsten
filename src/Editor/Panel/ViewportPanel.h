//
// Created by Andrew Graser on 11/24/2026.
//


#pragma once
#include "EditorPanel.h"

namespace TungstenEditor
{
    class ViewportPanel : public EditorPanel
    {
    public:
        ViewportPanel();

        void OnRender() const override;
        std::string GetName() const override;
    };
}
