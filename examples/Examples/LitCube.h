//
// Created by Andrew Graser on 7/2/2026.
//


#pragma once

#include <Tungsten/Core/Material.h>
#include <Tungsten/Core/Primitive.h>
#include <Tungsten/Core/Components/Transform.h>
#include "Example.h"



class LitCubeExample : public Example {
public:
    LitCubeExample() : Example("Lit Cube") {}

    void Start() override {
        Example::Start();

        mCubeMesh = Tungsten::Primitive::Cube();
        mMaterial = std::make_shared<Tungsten::Material>(Tungsten::Shader::Get("Basic_Lit"), Tungsten::Texture2D::Get("Default"));
        mLightMaterial = std::make_shared<Tungsten::Material>(Tungsten::Shader::Get("Basic_Unlit"), Tungsten::Texture2D::Get("Default"));

        mLightMaterial->Shader = Tungsten::Shader::Get("Basic_Unlit");

        mLightTransform.Scale = glm::vec3(0.25);
        mLightTransform.Position = glm::vec3(3, 2, 0.25);
    }

     void Update() override {
        //Move Light in circle around cube
        mLightTransform.Position.x = (glm::cos(mAngle) * mOrbitRadius);
        mLightTransform.Position.z = (glm::sin(mAngle) * mOrbitRadius);

        mAngle += mOrbitSpeed * Tungsten::Time::GetTime();

        //Rotate Cube
        //mCubeTransform.Rotate({0,1,0}, glm::radians(180.f) * Tungsten::Time::GetTime());

        mLight.Position = {mLightTransform.Position, 0};
        mLight.Color = mLightMaterial->Albedo;
        Tungsten::Renderer::SetLightData({mLight}, mDirLight);

        Tungsten::Renderer::Draw(*mCubeMesh, mCubeTransform.ModelMatrix(), *mMaterial);
        Tungsten::Renderer::Draw(*mCubeMesh, mLightTransform.ModelMatrix(), *mLightMaterial);
    }

    void Unload() override {

    }

    void OnImGuiRender() override {
        ImGui::ColorPicker3("Cube Color", &mMaterial->Albedo.x);
        ImGui::ColorPicker3("Light Color", &mLightMaterial->Albedo.x);

        ImGui::SliderFloat("Shininess", &mMaterial->Shininess, 0.0f, 256.0f);
        ImGui::SliderFloat("Metallic", &mMaterial->Metallic, 0.0f, 1.0f);
        ImGui::SliderFloat("Roughness", &mMaterial->Roughness, 0.0f, 1.0f);

        ImGui::Separator();
        ImGui::SliderFloat("Orbit Radius", &mOrbitRadius, 1.0f, 10.0f);
        ImGui::SliderFloat("Orbit Speed", &mOrbitSpeed, 1.0f, 10.0f);
        ImGui::SliderFloat3("Light Position", &mLightTransform.Position.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Sun Rotation", &mDirLight.Direction.x, -180.f, 180.f);
    }


private:
    std::shared_ptr<Tungsten::Mesh> mCubeMesh;
    std::shared_ptr<Tungsten::Material> mMaterial;
    std::shared_ptr<Tungsten::Material> mLightMaterial;
    Tungsten::Transform mCubeTransform;
    Tungsten::Transform mLightTransform;

    Tungsten::PointLight mLight;
    Tungsten::PointLight mLight2;
    Tungsten::DirectionalLight mDirLight;

    float mOrbitRadius = 2.0f;
    float mOrbitSpeed = 1.0f;
    float mAngle = 0.0f;
};