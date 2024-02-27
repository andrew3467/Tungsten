//
// Created by Andrew Graser on 2/26/2024.
//

#include "Wolframite/Tungsten.h"


class ExampleLayer : public Tungsten::Layer {
public:
    ExampleLayer() {

    }

    ~ExampleLayer() {

    }

    void OnStart() override {

    }

    void OnUpdate() override {
        TUNGSTEN_CORE_INFO("Wolfy is dumb");
    }

    void OnRender() override {

    }

    void OnImguiRender() override {

    }
};


class Sandbox : public Tungsten::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() override {

    }
};

Tungsten::Application* CreateApplication() {
    return new Sandbox;
}
