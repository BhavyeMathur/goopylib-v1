#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace gp {
    class Log {

    public:
        static void init();

        static std::shared_ptr<spdlog::logger> getCoreLogger();

        static std::shared_ptr<spdlog::logger> getClientLogger();

        static std::shared_ptr<spdlog::logger> getPythonLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_PythonLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}
