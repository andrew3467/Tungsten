//
// Created by Andrew Graser on 2/10/2024.
//

#ifndef PEARL_IMGUILAYER_H
#define PEARL_IMGUILAYER_H

#include "Wolframite/Layer.h"
#include "Wolframite/Events/MouseEvent.h"
#include "Wolframite/Events/KeyEvent.h"
#include "Wolframite/Events/ApplicationEvent.h"

namespace Tungsten {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();


        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();


    private:
        float mTime = 0.0f;
    };
}


#endif //PEARL_IMGUILAYER_H
