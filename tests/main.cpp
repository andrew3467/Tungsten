//
// Created by Andrew Graser on 7/1/2026.
//



#include "Tungsten.h"

using namespace Tungsten;


void Start() {

}

void Update() {

}

void OnImGuiRender() {

}


int main() {
    Engine engine("Tungsten tests");

    engine.Run(&Start, &Update, &OnImGuiRender);
}