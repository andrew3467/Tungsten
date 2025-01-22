//
// Created by Andrew Graser on 1/21/2025.
//


#pragma once

namespace Tungsten {
    class ImGuiLayer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void Init();

        void Begin();
        void End();

    private:
        void SetupDockspace();
    };
}
