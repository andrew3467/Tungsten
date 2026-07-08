//
// Created by Andrew Graser on 7/1/2026.
//


#pragma once


#include <string>

class Example {


public:
    Example(const std::string& name = "Example") : mName(name) {}


    virtual void Start() {TUNGSTEN_INFO("Loading {0} Example", mName.c_str());}
    virtual void Update() = 0;
    virtual void OnImGuiRender() = 0;

    virtual void Unload() = 0;

    const std::string& Name() {return mName;}

protected:
    std::string mName {};
};