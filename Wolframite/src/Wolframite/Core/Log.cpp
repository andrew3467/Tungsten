//
// Created by Andrew Graser on 2/26/2024.
//

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>


namespace Tungsten {
    std::shared_ptr<spdlog::logger> Log::mCoreLogger;
    std::shared_ptr<spdlog::logger> Log::mClientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        mCoreLogger = spdlog::stdout_color_mt("TUNGSTEN");
        mCoreLogger->set_level(spdlog::level::trace);


        mClientLogger = spdlog::stdout_color_mt("APP");
        mClientLogger->set_level(spdlog::level::trace);
    }
}