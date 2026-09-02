//
// Created by Andrew Graser on 8/19/2026.
//

#include "random"

#include "UUID.h"

namespace Tungsten {
    static std::random_device sRandomDevice;
    static std::mt19937_64  sEngine(sRandomDevice());
    static std::uniform_int_distribution<uint64_t> sUniformDistribution;

    UUID::UUID()
            : mUUID(sUniformDistribution(sEngine))
    {

    }

    UUID::UUID(uint64_t uuid)
            : mUUID(uuid)
    {

    }
} // Tungsten