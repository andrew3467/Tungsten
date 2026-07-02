//
// Created by Andrew Graser on 7/1/2026.
//



#include "Tungsten.h"

#include "imgui.h"


#include "CameraController.h"
#include "Tests/LitCube.h"
#include "Tests/MultipleLit.h"

using namespace Tungsten;


int TestSelection = 0;
int PrevTestSelection = 0;
std::array<std::unique_ptr<Test>, 2> Tests {
        std::make_unique<LitCubeTest>(),
        std::make_unique<MultipleLitTest>(),
};


std::unique_ptr<CameraController> CamController;


void Start() {
    CamController = std::make_unique<CameraController>(glm::vec3(0,0,-10));
}

void Update() {
    CamController->Update();
    Renderer::UpdateViewPos(CamController->GetPosition());

    if (TestSelection == -1) return;


    if (TestSelection != PrevTestSelection) {
        Tests[PrevTestSelection]->Unload();
        Tests[TestSelection]->Start();
    }


    Tests[TestSelection]->Update();
}


bool SelectionState[16] {
        true
};
void DrawTestSelection() {
    PrevTestSelection = TestSelection;
    for (int i = 0; i < Tests.size(); ++i) {
        if(ImGui::Checkbox(Tests[i]->Name().c_str(), &SelectionState[i])) {
            if(SelectionState[i]) {
                for (int j = 0; j < 16; ++j) {
                    if(j != i) SelectionState[j] = false;
                }

                TestSelection = i;
            }
        }
    }
}

void OnImGuiRender() {
    Renderer::OnImGUIDrawRenderer();


    ImGui::Begin("Test Options");

    DrawTestSelection();


    ImGui::End();
}

int main() {
    Engine engine("Tungsten tests");

    engine.Run(&Update, &Start, &OnImGuiRender);
}