//
// Created by Andrew Graser on 7/1/2026.
//



#include "Tungsten.h"

#include "imgui.h"


#include "CameraController.h"
#include "imgui_internal.h"
#include "Panel/EditorPanel.h"
#include "Panel/TerrainNodePanel.h"
#include "Panel/ViewportPanel.h"
#include "Tungsten/Core/Primitive.h"


using namespace Tungsten;
using namespace TungstenEditor;


static Material mat;

static std::vector<EditorPanel*> EditorPanels;

void UpdateEditorPanels()
{
    for (auto& panel : EditorPanels)
    {
        panel->OnUpdate();
    }
}


void Start() {
    mat.Shader = Engine::Get().Assets().Load<Shader>("shaders/Basic_Unlit.glsl");
    mat.Texture = Texture2D::Get("Default");

    EditorPanels.push_back(new ViewportPanel());
    EditorPanels.push_back(new TerrainNodePanel());
}

void Update() {
    UpdateEditorPanels();

    Renderer::Submit(
          Primitive::Cube().get(),
          &mat,
          glm::mat4(1.0)
    );
}

void OnImGuiRender() {
    ImGui::Begin("Debug");

    ImGui::ColorPicker4("Color", &mat.Albedo.x);

    ImGui::End();

    for (auto& panel : EditorPanels)
    {
        panel->OnRender();
    }
}

int main() {
    Engine engine("Tungsten Editor");

    engine.Run(&Update, &Start, &OnImGuiRender);
}