//
// Created by Andrew Graser on 2/27/2024.
//

#ifndef SANDBOX_LAYER_H
#define SANDBOX_LAYER_H


class Layer {
public:
    virtual ~Layer() = default;

    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;

    virtual void OnImguiRender() = 0;
};


#endif //SANDBOX_LAYER_H
