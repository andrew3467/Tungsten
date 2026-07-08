//
// Created by Andrew Graser on 7/2/2026.
//


#pragma once

#include <Tungsten/Core/Material.h>
#include "Example.h"



class LitCubeExample : public Example {
public:
    LitCubeExample() : Example("Lit Cube") {}

    void Start() override {
        Example::Start();
    }

     void Update() override {
        Tungsten::Renderer::SetLightData({mLight}, mDirLight);

        Tungsten::Renderer::Draw(mCubeMesh, mMaterial);
    }

    void Unload() override {

    }

    void OnImGuiRender() override {
        ImGui::ColorPicker3("Cube Color", &mCubeColor.x);
        ImGui::ColorPicker3("Light Color", &mLight.Color.x);
        ImGui::SliderFloat3("Light Position", &mLight.Position.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Sun Rotation", &mDirLight.Direction.x, -180.f, 180.f);
    }


private:
    Tungsten::Mesh mCubeMesh;
    Tungsten::Material mMaterial;

    glm::vec3 mCubeColor {1};
    Tungsten::PointLight mLight;
    Tungsten::DirectionalLight mDirLight;
};