//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_LAYER_H
#define SANDBOX_LAYER_H

#include "Wolframite/Events/Event.h"
#include "Wolframite/Core/Timestep.h"

namespace Tungsten {
    class Layer {
    public:
        virtual ~Layer() = default;

        virtual void OnStart() {};
        virtual void OnUpdate(Timestep ts) {};
        virtual void OnRender() {};

        virtual void OnEvent(Event &e) {};

        virtual void OnImguiRender() {};
    };
}


#endif //SANDBOX_LAYER_H
