//
// Created by Andrew Graser on 11/26/2026.
//


#pragma once
#include "EditorPanel.h"

namespace TungstenEditor
{
    class TerrainNodePanel : public EditorPanel
    {
    public:
        TerrainNodePanel();

        void OnRender() override;
        void OnUpdate() override;

        std::string GetName() const override;



    private:

    };
}

