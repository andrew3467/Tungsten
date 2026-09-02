//
// Created by Andrew Graser on 8/29/2026.
//


#pragma once

#include "Tungsten.h"

#include "Example.h"


const glm::vec3 GRAVITY = {0.0f, -9.81f, 0.0f};


struct Particle {
    glm::vec3 Position{};
    glm::vec3 Velocity{};

    uint32_t Lifetime{};
};

class ParticleExample  : public Example {
public:
    ParticleExample() : Example("Particles") {}


    void Start() override {
        mParticleMaterial.Shader = Tungsten::Assets().Load<Tungsten::Shader>("shaders/Basic_Unlit.glsl");
        mParticleMaterial.Texture = Tungsten::Texture2D::Get("Default");

        CreateParticles(mNumParticles);
    }

    void Update() override {
        for (int i = 0; i < mNumParticles; ++i) {
            Tungsten::Renderer::Submit(*Tungsten::Primitive::Quad(), ParticleModel(mParticles[i]), mParticleMaterial);
        }

        for (int i = 0; i < mNumParticles; ++i) {
            UpdateParticle(mParticles[i]);
        }
    }

    void Unload() override {

    }

    void OnImGuiRender() override {
        if(ImGui::Button("Reset")) {
            CreateParticles(mNumParticles);
        }

        ImGui::InputInt("Particle Count", &mNumParticles);
    }

private:
    void CreateParticles(size_t count) {
        mParticles.clear();
        mParticles.resize(count);

        for (size_t i = 0; i < count; ++i) {
            ResetParticle(mParticles[i]);
        }
    }

    void UpdateParticle(Particle& p) {
        //p.Velocity += GRAVITY * Tungsten::Time::GetTime();
        p.Position += p.Velocity * Tungsten::Time::GetTime();
        p.Lifetime--;

        if(p.Lifetime <= 0) ResetParticle(p);
    }

    void ResetParticle(Particle& p) {
        p = {
                {
                        Tungsten::Random::Random(0.0, 5.0f),
                        Tungsten::Random::Random(0.0, 5.0f),
                        0.0f
                },
                {
                        Tungsten::Random::Random(-1.0f, 1.0f),
                        Tungsten::Random::Random(-1.0, 1.0f),
                        0.0f
                },
                (uint32_t)Tungsten::Random::Random(200, 1000)
        };
    }

    glm::mat4 ParticleModel(const Particle& p) {
        return glm::translate(glm::mat4(1.0f), p.Position);
    }

private:
    Tungsten::Material mParticleMaterial;

    int mNumParticles = 256;
    std::vector<Particle> mParticles;
};