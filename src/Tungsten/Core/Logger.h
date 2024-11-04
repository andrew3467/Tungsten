//
// Created by Andrew Graser on 11/4/2024.
//


#pragma once

#include <memory>

#include <spdlog/spdlog.h>


namespace Tungsten {
    class Logger {
    public:
        static void Init();

        static spdlog::logger& GetCoreLogger() {return *sCoreLogger;}
        static spdlog::logger& GetClientLogger() {return *sClientLogger;}


    private:
        static std::shared_ptr<spdlog::logger> sClientLogger;
        static std::shared_ptr<spdlog::logger> sCoreLogger;
    };
}

//Logging macros
#define TUNGSTEN_TRACE(...) ::Tungsten::Logger::GetCoreLogger().trace(__VA_ARGS__)
#define TUNGSTEN_INFO(...) ::Tungsten::Logger::GetCoreLogger().info(__VA_ARGS__)
#define TUNGSTEN_WARN(...) ::Tungsten::Logger::GetCoreLogger().warn(__VA_ARGS__)
#define TUNGSTEN_ERROR(...) ::Tungsten::Logger::GetCoreLogger().error(__VA_ARGS__)
#define TUNGSTEN_FATAL(...) ::Tungsten::Logger::GetCoreLogger().critital(__VA_ARGS__)
#define TUNGSTEN_ASSERT(x, ...) { if(!(x)) { TUNGSTEN_ERROR(__VA_ARGS__); }}