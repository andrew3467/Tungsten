//
// Created by Andrew Graser on 7/1/2026.
//



#include "Tungsten.h"

#include "imgui.h"


#include "CameraController.h"
#include "Examples/LitCube.h"
#include "Examples/MultipleLit.h"
using namespace Tungsten;


int TestSelection = 0;
int PrevTestSelection = 0;
std::array<std::unique_ptr<Example>, 2> Tests {
        std::make_unique<LitCubeExample>(),
        std::make_unique<MultipleLitExample>(),
};


std::unique_ptr<CameraController> CamController;


void Start() {
    CamController = std::make_unique<CameraController>(glm::vec3(0,0,-10));
}

void Update() {
    CamController->Update();

    if (TestSelection == -1) return;


    if (TestSelection != PrevTestSelection) {
        Tests[PrevTestSelection]->Unload();
        Tests[TestSelection]->Start();
    }


    Tests[TestSelection]->Update();
}

void DrawTestSelection() {
    PrevTestSelection = TestSelection;
    for(int i = 0; i < Tests.size(); i++) {
        ImGui::RadioButton(Tests[i]->Name().c_str(),
                           &TestSelection,
                           i);
    }
}

void OnImGuiRender() {
    Renderer::OnImGUIDrawRenderer();


    ImGui::Begin("Example Options");

    DrawTestSelection();

    ImGui::SeparatorText(Tests[TestSelection]->Name().c_str());
    Tests[TestSelection]->OnImGuiRender();


    ImGui::End();
}

int main() {
    Engine engine("Tungsten examples");

    engine.Run(&Update, &Start, &OnImGuiRender);
}