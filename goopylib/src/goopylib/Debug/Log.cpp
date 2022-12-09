#include "pch.h"
#include "Log.h"

namespace gp {
    std::shared_ptr<spdlog::logger> Log::CoreLogger;
    std::shared_ptr<spdlog::logger> Log::PythonLogger;
    std::shared_ptr<spdlog::logger> Log::ClientLogger;

    void Log::Init() {
        if (!spdlog::get("GOOPYLIB")) {
            std::vector<spdlog::sink_ptr> logSinks;
            logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
            logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("goopylib.log", true));

            logSinks[0]->set_pattern("%^[%T] %n: %v%$");
            logSinks[1]->set_pattern("[%T] [%l] %n: %v");

            CoreLogger = std::make_shared<spdlog::logger>("GOOPYLIB", begin(logSinks), end(logSinks));
            spdlog::register_logger(CoreLogger);
            CoreLogger->set_level(spdlog::level::trace);
            CoreLogger->flush_on(spdlog::level::trace);

            PythonLogger = std::make_shared<spdlog::logger>("PYTHON", begin(logSinks), end(logSinks));
            spdlog::register_logger(PythonLogger);
            PythonLogger->set_level(spdlog::level::trace);
            PythonLogger->flush_on(spdlog::level::trace);

            ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
            spdlog::register_logger(ClientLogger);
            ClientLogger->set_level(spdlog::level::trace);
            ClientLogger->flush_on(spdlog::level::trace);

            GP_CORE_TRACE("Initialized logger");
        }
    }

    std::shared_ptr<spdlog::logger> Log::getCoreLogger() {
        return CoreLogger;
    }

    std::shared_ptr<spdlog::logger> Log::getClientLogger() {
        return ClientLogger;
    }

    std::shared_ptr<spdlog::logger> Log::getPythonLogger() {
        return PythonLogger;
    }
}
