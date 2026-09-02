//
// Created by Andrew Graser on 8/29/2026.
//


#pragma once

#include <random>

namespace Tungsten {
    namespace Random {
        static std::random_device sRandomDevice;
        static std::mt19937_64  sEngine(sRandomDevice());
        static std::uniform_real_distribution<float> sUniformDistribution;

        static float Random(float min, float max) {
            return min + (max - min) * sUniformDistribution(sEngine);
        }
    }
}
