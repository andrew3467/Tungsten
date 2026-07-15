//
// Created by Andrew Graser on 7/9/2026.
//


#pragma once

#include "Example.h"


class PBRExample : public Example {
    struct Cube {
        Tungsten::Transform Transform;
        Tungsten::Material Material;
    };

public:
    PBRExample() : Example("PBR") {}


    void Start() override {
        Example::Start();

        Tungsten::ScopedTimer("Start Func");

        mSphere = Tungsten::Primitive::Sphere(36, 18);

        mLightMaterial = std::make_shared<Tungsten::Material>(Tungsten::Shader::Get("Basic_Unlit"), Tungsten::Texture2D::Get("Default"));

        mLightTransform.Scale = glm::vec3(0.25f);
        mLightTransform.Position.y = 5.f;

        //Populate cubes array
        mCubes.resize(mCubesPerLine * mCubesPerLine);
        for(int x = 0; x < mCubesPerLine; x++) {
            for (int y = 0; y < mCubesPerLine; y++) {
                int index = x * mCubesPerLine + y;

                mCubes[index] = {
                        {
                            {x * mSpacing, y * mSpacing, 0},
                            {1, 0, 0, 0},
                            {1, 1, 1}
                        },
                        {
                                Tungsten::Shader::Get("PBR"),
                                Tungsten::Texture2D::Get("Default"),
                                0.0f,
                                (float)x / (float)mCubesPerLine,
                                (float)y / 4.0f,
                                {1, 0, 0, 1}
                        }
                };
            }
        }
    }

    void Update() override {
        Tungsten::ScopedTimer("Update Func");

        mLightTransform.Position.x = (glm::cos(mAngle) * mOrbitRadius) + 5.f;
        mLightTransform.Position.z = (glm::sin(mAngle) * mOrbitRadius);
        mLight.Position = glm::vec4(mLightTransform.Position, 0.0);

        mAngle += mOrbitSpeed * Tungsten::Time::GetTime();


        Tungsten::Renderer::SetLightData({mLight}, {});
        Tungsten::Renderer::Submit(*Tungsten::Primitive::Cube(), mLightTransform.ModelMatrix(), *mLightMaterial);
        for(int x = 0; x < mCubesPerLine; x++) {
            for (int y = 0; y < mCubesPerLine; y++) {
                auto& cubeToDraw = mCubes[x * mCubesPerLine + y];
                Tungsten::Renderer::Submit(*mSphere, cubeToDraw.Transform.ModelMatrix(), cubeToDraw.Material);
            }
        }
    }

    void Unload() override {

    }

    void OnImGuiRender() override {
        ImGui::SeparatorText("Light");
        ImGui::SliderFloat("Orbit Radius", &mOrbitRadius, 1.0f, 10.0f);
        ImGui::SliderFloat("Orbit Speed", &mOrbitSpeed, 1.0f, 10.0f);
    }


private:
    std::shared_ptr<Tungsten::Material> mLightMaterial;
    std::shared_ptr<Tungsten::Mesh> mSphere;
    Tungsten::Transform mLightTransform;
    Tungsten::PointLight mLight;

    std::vector<Cube> mCubes;
    float mSpacing = 2.5f;
    int mCubesPerLine = 5;


    float mOrbitRadius = 10.0f;
    float mOrbitSpeed = 1.0f;
    float mAngle = 0.0f;
};
