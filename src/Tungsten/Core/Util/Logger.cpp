//
// Created by Andrew Graser on 11/4/2024.
//

#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>


namespace Tungsten {
    std::shared_ptr<spdlog::logger> Logger::sClientLogger = nullptr;
    std::shared_ptr<spdlog::logger> Logger::sCoreLogger = nullptr;

    void Logger::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        sClientLogger = spdlog::stdout_color_mt("Client");
        sClientLogger->set_level(spdlog::level::trace);

        sCoreLogger = spdlog::stdout_color_mt("Tungsten");
        sCoreLogger->set_level(spdlog::level::trace);
    }
}


