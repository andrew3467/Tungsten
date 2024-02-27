//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_LAYERSTACK_H
#define SANDBOX_LAYERSTACK_H


#include <vector>
#include <memory>
#include "Layer.h"

namespace Tungsten {
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();


        void PushLayer(Layer* layer);
        Layer* PopLayer(Layer* layer);

        std::vector<Layer*>::iterator begin() {return mLayers.begin();}
        std::vector<Layer*>::iterator end() {return mLayers.end();}

    private:
        std::vector<Layer*> mLayers;

        int mInsertIndex = 0;
    };
}


#endif //SANDBOX_LAYERSTACK_H
