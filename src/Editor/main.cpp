//
// Created by Andrew Graser on 7/1/2026.
//



#include "Tungsten.h"

#include "imgui.h"


#include "CameraController.h"


using namespace Tungsten;


std::unique_ptr<CameraController> CamController;


void Start() {
    CamController = std::make_unique<CameraController>(glm::vec3(0,0,-10));
}

void Update() {
    CamController->Update();
}

void OnImGuiRender() {

}

int main() {
    Engine engine("Tungsten Editor");

    engine.Run(&Update, &Start, &OnImGuiRender);
}