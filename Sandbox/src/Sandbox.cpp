//
// Created by Andrew Graser on 2/26/2024.
//

#include "Wolframite/Tungsten.h"

class Sandbox : public Tungsten::Application {
public:
    Sandbox() {
        TUNGSTEN_CORE_INFO("Creating Sandbox");
    }

    ~Sandbox() override {

    }
};

Tungsten::Application* CreateApplication() {
    return new Sandbox;
}
