//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_CORE_H
#define SANDBOX_CORE_H

#include "Log.h"


#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


#endif //SANDBOX_CORE_H
