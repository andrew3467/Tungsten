//
// Created by Andrew Graser on 9/1/2026.
//


#pragma once

#include <glm/glm.hpp>

#include "Tungsten.h"
#include "Tungsten/Core/Components/Transform.h"
#include "Tungsten/Core/Primitive.h"

#include "Example.h"


class SolarSystemExample  : public Example {
    struct CelestialBody {
        glm::vec3 Position {};
        glm::vec3 Velocity {};

        glm::vec3 Rotation {};
        float RotationSpeed {};


        float Radius {};
        float Mass {};

        Tungsten::Material Material;
    };

    const float GRAVITATIONAL_CONSTANT = 6.6743E-11;

public:
    SolarSystemExample() : Example("Solar System") {}

    void Start() override {
        mSphere = Tungsten::Primitive::Sphere(36,18);

        mSun = {
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),

                glm::vec3(0.0f, 0.0f, 0.0f),
                0.0f,

                2.0f,
                10000.0f,


                {
                    Tungsten::Assets().Get<Tungsten::Shader>("shaders/Basic_Unlit.glsl"),
                    Tungsten::Texture2D::Get("Default"),

                    glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)
                }
        };

        mPlanet = {
                glm::vec3(10.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),

                glm::vec3(0.0f, 0.0f, 0.0f),
                2.0f,

                1.0f,
                1.0f,


                {
                        Tungsten::Assets().Get<Tungsten::Shader>("shaders/Basic_Unlit.glsl"),
                        Tungsten::Texture2D::Get("Default"),

                        glm::vec4(0.1f, 0.8f, 0.1f, 1.0f)
                }
        };
    }

    void Update() override {
        ApplyGravity(mPlanet, mSun, 1);

        Tungsten::Renderer::Submit(*mSphere, GetModelMatrix(mSun), mSun.Material);
        Tungsten::Renderer::Submit(*mSphere, GetModelMatrix(mPlanet), mPlanet.Material);
    }

    void OnImGuiRender() override {

    }

    void ApplyGravity(CelestialBody& target, CelestialBody& other, float dt) {
        glm::vec3 direction = other.Position - target.Position;
        float dist = glm::length(direction);

        glm::vec3 directionNorm = glm::normalize(direction);

        float forceMagnitude = GRAVITATIONAL_CONSTANT *
                               (target.Mass * other.Mass) /
                               (dist * dist);

        glm::vec3 force = directionNorm * forceMagnitude;

        glm::vec3 acceleration = force / target.Mass;

        target.Velocity += acceleration * dt;
        target.Position += target.Velocity * dt;
    }

    glm::mat4 GetModelMatrix(const CelestialBody& body) {
        Tungsten::Transform t = {
                body.Position,
                body.Rotation,
                glm::vec3(body.Radius)
        };
        return t.ModelMatrix();
    }


private:
    std::vector<CelestialBody> mBodies;

    std::shared_ptr<Tungsten::Mesh> mSphere;

    CelestialBody mSun;
    CelestialBody mPlanet;
};