//
// Created by Andrew Graser on 2/26/2024.
//

#include "Wolframite/Core/Log.h"




int main() {
    //Move to entry point
    Tungsten::Log::Init();
 q  

    TUNGSTEN_CORE_INFO("Print: {0}", 10);
    TUNGSTEN_CORE_FATAL("FATAL");

    return 0;
}
