//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef WOLFRAMITE_LOG_H
#define WOLFRAMITE_LOG_H



#include <spdlog/spdlog.h>


namespace Tungsten {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return mCoreLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return mClientLogger;}

    private:
        static std::shared_ptr<spdlog::logger> mCoreLogger;
        static std::shared_ptr<spdlog::logger> mClientLogger;
    };
}

//Logger Macros
#define TUNGSTEN_CORE_TRACE(...) ::Tungsten::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TUNGSTEN_CORE_INFO(...) ::Tungsten::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TUNGSTEN_CORE_WARN(...) ::Tungsten::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TUNGSTEN_CORE_ERROR(...) ::Tungsten::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TUNGSTEN_CORE_FATAL(...) ::Tungsten::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define TUNGSTEN_CORE_ASSERT(x, ...) {if(!(x)) {TUNGSTEN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);}}

#define TUNGSTEN_TRACE(...) ::Tungsten::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TUNGSTEN_INFO(...) ::Tungsten::Log::GetClientLogger()->info(__VA_ARGS__)
#define TUNGSTEN_WARN(...) ::Tungsten::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TUNGSTEN_ERROR(...) ::Tungsten::Log::GetClientLogger()->error(__VA_ARGS__)
#define TUNGSTEN_FATAL(...) ::Tungsten::Log::GetClientLogger()->critical(__VA_ARGS__)
#define TUNGSTEN_ASSERT(x, ...) {if(!(x)) {TUNGSTEN_ERROR("Assertion failed: {0}", __VA_ARGS__);}}


#endif //WOLFRAMITE_LOG_H
