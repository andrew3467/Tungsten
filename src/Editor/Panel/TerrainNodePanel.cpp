//
// Created by Andrew Graser on 11/26/2026.
//

#include "TerrainNodePanel.h"

#include "imgui.h"


using namespace TungstenEditor;

TerrainNodePanel::TerrainNodePanel()
{

}

void TerrainNodePanel::OnRender()
{
    ImGui::Begin(GetName().c_str());



    ImGui::End();
}

void TerrainNodePanel::OnUpdate()
{

}

std::string TerrainNodePanel::GetName() const
{
    return "Terrain Node Editor";
}
