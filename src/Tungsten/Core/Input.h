//
// Created by Andrew Graser on 1/16/2025.
//


#pragma once

namespace Tungsten {
    class Input {
    public:
        static bool GetKey(uint32_t keycode);
        static bool GetMouseButton(uint32_t mousecode);
        static std::pair<double, double> GetMousePosition();
        static void SetMousePosition(double x, double y);
    };
}
