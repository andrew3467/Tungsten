//
// Created by Andrew Graser on 2/27/2024.
//

#include "LayerStack.h"


namespace Tungsten {

    LayerStack::LayerStack() {

    }

    LayerStack::~LayerStack() {

    }

    void LayerStack::PushLayer(Layer *layer) {
        mLayers.emplace(mLayers.begin() + mInsertIndex, layer);
        mInsertIndex++;
    }
}