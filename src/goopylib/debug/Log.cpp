#include "Log.h"
#include "LogMacros.h"

namespace gp {
    shared_ptr<spdlog::logger> Log::s_CoreLogger;
    shared_ptr<spdlog::logger> Log::s_PythonLogger;
    shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::init() {
        if (!spdlog::get("GOOPYLIB")) {
            std::vector<spdlog::sink_ptr> logSinks;
            auto colorSink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
            logSinks.emplace_back(colorSink);

            logSinks[0]->set_pattern("%^[%T] %n: %v%$");

            #if GP_LOGGING_LEVEL >= 4
            logSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("goopylib.log", true));
            logSinks[1]->set_pattern("[%T] [%l] %n: %v");
            #endif

            #if !__WINDOWS__
            colorSink->set_color(spdlog::level::critical, "\033[91m\033[1m");
            #endif

            s_CoreLogger = make_shared<spdlog::logger>("GOOPYLIB", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_CoreLogger);
            s_CoreLogger->flush_on(spdlog::level::trace);
            s_CoreLogger->set_level(spdlog::level::trace);

            GP_CORE_DEBUG("gp::Log::init()");

            s_PythonLogger = make_shared<spdlog::logger>("PYTHON", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_PythonLogger);
            s_PythonLogger->flush_on(spdlog::level::trace);
            s_PythonLogger->set_level(spdlog::level::trace);

            s_ClientLogger = make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_ClientLogger);
            s_ClientLogger->flush_on(spdlog::level::trace);
            s_ClientLogger->set_level(spdlog::level::trace);
        }
    }

    shared_ptr<spdlog::logger> Log::getCoreLogger() {
        return s_CoreLogger;
    }

    shared_ptr<spdlog::logger> Log::getClientLogger() {
        return s_ClientLogger;
    }

    shared_ptr<spdlog::logger> Log::getPythonLogger() {
        return s_PythonLogger;
    }
}
