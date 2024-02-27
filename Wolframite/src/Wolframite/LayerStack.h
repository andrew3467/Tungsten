//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_LAYERSTACK_H
#define SANDBOX_LAYERSTACK_H


#include "Layer.h"

namespace Tungsten {
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();


        void PushLayer(Layer* layer);
        Layer* PopLayer();
    };
}


#endif //SANDBOX_LAYERSTACK_H
