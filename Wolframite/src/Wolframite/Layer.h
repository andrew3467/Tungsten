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
        Layer(const std::string &name = "Layer") : mDebugName(name) {

        }
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        virtual void OnUpdate(Timestep ts) {};
        virtual void OnRender() {};
        virtual void OnImGuiRender() {};

        virtual void OnEvent(Event &e) {};

        virtual void OnImguiRender() {};

    private:
        std::string mDebugName;
    };
}


#endif //SANDBOX_LAYER_H
