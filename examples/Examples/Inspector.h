//
// Created by Andrew Graser on 7/9/2026.
//


#pragma once

#include "Example.h"


class InspectorExample : public Example {
public:
    InspectorExample() : Example("Inspector") {}


    void Start() override {
        Example::Start();
    }

    void Update() override {

    }

    void Unload() override {

    }

    void OnImGuiRender() override {

    }
};
