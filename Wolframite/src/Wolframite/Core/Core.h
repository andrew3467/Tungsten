//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_CORE_H
#define SANDBOX_CORE_H

#include "Log.h"


#define BIT(x) (1 << x)

#define TUNGSTEN_ASSERT(x, ...) {if(!(x)) {TUNGSTEN_ERROR("Assertion failed: {0}", __VA_ARGS__);}}
#define TUNGSTEN_CORE_ASSERT(x, ...) {if(!(x)) {TUNGSTEN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);}}

#endif //SANDBOX_CORE_H
