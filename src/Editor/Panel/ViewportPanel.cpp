//
// Created by Andrew Graser on 11/24/2026.
//

#include "ViewportPanel.h"

#include "imgui.h"
#include "Tungsten/Core/Engine.h"
#include "Tungsten/Renderer/Renderer.h"

TungstenEditor::ViewportPanel::ViewportPanel()
{
    mFramebufferOutput = Tungsten::Engine::Get().Assets().Get<Tungsten::Texture2D>("FramebufferOutput");
}

void TungstenEditor::ViewportPanel::OnRender() const
{
    ImGui::Begin("ViewportPanel");
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();

    ImGui::Image(
        (ImTextureID)(intptr_t)mFramebufferOutput->GetID(),
        viewportSize,
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    int width = viewportSize.x;
    int height = viewportSize.y;

    Tungsten::Renderer::ResizeFrameBuffer(width, height);
    Tungsten::Engine::MainCamera->SetViewportSize(width, height);

    ImGui::End();
}

std::string TungstenEditor::ViewportPanel::GetName() const
{
    return "Viewport";
}
