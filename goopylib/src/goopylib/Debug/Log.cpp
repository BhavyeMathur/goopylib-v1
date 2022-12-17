#include "Log.h"

namespace gp {
    Ref<spdlog::logger> Log::CoreLogger;
    Ref<spdlog::logger> Log::PythonLogger;
    Ref<spdlog::logger> Log::ClientLogger;

    void Log::init() {
        if (!spdlog::get("GOOPYLIB")) {
            std::vector<spdlog::sink_ptr> logSinks;
            logSinks.emplace_back(CreateRef<spdlog::sinks::stdout_color_sink_mt>());
            logSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("goopylib.log", true));

            logSinks[0]->set_pattern("%^[%T] %n: %v%$");
            logSinks[1]->set_pattern("[%T] [%l] %n: %v");

            CoreLogger = CreateRef<spdlog::logger>("GOOPYLIB", begin(logSinks), end(logSinks));
            spdlog::register_logger(CoreLogger);
            CoreLogger->flush_on(spdlog::level::trace);

            PythonLogger = CreateRef<spdlog::logger>("PYTHON", begin(logSinks), end(logSinks));
            spdlog::register_logger(PythonLogger);
            PythonLogger->flush_on(spdlog::level::trace);

            ClientLogger = CreateRef<spdlog::logger>("APP", begin(logSinks), end(logSinks));
            spdlog::register_logger(ClientLogger);
            ClientLogger->flush_on(spdlog::level::trace);

            GP_CORE_INFO("Initialized logger");
        }
    }

    Ref<spdlog::logger> Log::getCoreLogger() {
        return CoreLogger;
    }

    Ref<spdlog::logger> Log::getClientLogger() {
        return ClientLogger;
    }

    Ref<spdlog::logger> Log::getPythonLogger() {
        return PythonLogger;
    }
}
