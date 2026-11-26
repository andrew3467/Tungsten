//
// Created by Andrew Graser on 7/1/2026.
//



#include "Tungsten.h"

#include "imgui.h"


#include "CameraController.h"
#include "imgui_internal.h"
#include "Panel/EditorPanel.h"
#include "Panel/ViewportPanel.h"
#include "Tungsten/Core/Primitive.h"


using namespace Tungsten;
using namespace TungstenEditor;


std::unique_ptr<CameraController> CamController;

Material mat;

static std::vector<EditorPanel*> EditorPanels;

void Start() {
    CamController = std::make_unique<CameraController>(glm::vec3(0,0,-10));
    mat.Shader = Engine::Get().Assets().Load<Shader>("shaders/Basic_Lit.glsl");
    mat.Texture = Texture2D::Get("Default");

    EditorPanels.push_back(new ViewportPanel());
}

void Update() {
    CamController->Update();

    Renderer::Submit(
          Primitive::Cube().get(),
          &mat,
          glm::mat4(1.0)
    );
}

void OnImGuiRender() {
    ImGui::Begin("Debug");
    if (ImGui::Button("Reset Docking Data")) ImGui::ClearIniSettings();
    ImGui::ColorPicker3("Color", &mat.Albedo.x);
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