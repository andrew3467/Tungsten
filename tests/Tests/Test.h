//
// Created by Andrew Graser on 7/1/2026.
//


#pragma once


#include <string>

class Test {


public:
    Test(const std::string& name = "Test") : mName(name) {}


    virtual void Start() {TUNGSTEN_INFO("Loading {0} Test", mName.c_str());}
    virtual void Update() = 0;
    virtual void OnImgGuiRender() {}

    virtual void Unload() = 0;

    const std::string& Name() {return mName;}

protected:
    std::string mName {};
};