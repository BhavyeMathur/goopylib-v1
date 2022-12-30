#include "Log.h"
#include "LogMacros.h"

namespace gp {
    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_PythonLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::init() {
        if (!spdlog::get("GOOPYLIB")) {
            std::vector<spdlog::sink_ptr> logSinks;
            auto colorSink = CreateRef<spdlog::sinks::stdout_color_sink_mt>();
            logSinks.emplace_back(colorSink);
            logSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("goopylib.log", true));

            logSinks[0]->set_pattern("%^[%T] %n: %v%$");
            logSinks[1]->set_pattern("[%T] [%l] %n: %v");
            colorSink->set_color(spdlog::level::critical, "\033[91m\033[1m");

            s_CoreLogger = CreateRef<spdlog::logger>("GOOPYLIB", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_CoreLogger);
            s_CoreLogger->flush_on(spdlog::level::trace);
            s_CoreLogger->set_level(spdlog::level::trace);

            GP_CORE_DEBUG("gp::Log::init()");

            s_PythonLogger = CreateRef<spdlog::logger>("PYTHON", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_PythonLogger);
            s_PythonLogger->flush_on(spdlog::level::trace);
            s_PythonLogger->set_level(spdlog::level::trace);

            s_ClientLogger = CreateRef<spdlog::logger>("APP", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_ClientLogger);
            s_ClientLogger->flush_on(spdlog::level::trace);
            s_ClientLogger->set_level(spdlog::level::trace);
        }
    }

    Ref<spdlog::logger> Log::getCoreLogger() {
        return s_CoreLogger;
    }

    Ref<spdlog::logger> Log::getClientLogger() {
        return s_ClientLogger;
    }

    Ref<spdlog::logger> Log::getPythonLogger() {
        return s_PythonLogger;
    }
}
