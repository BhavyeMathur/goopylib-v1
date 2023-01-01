#pragma once

#include "gp.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace gp {
    class Log {

    public:
        static void init();

        static Ref<spdlog::logger> getCoreLogger();

        static Ref<spdlog::logger> getClientLogger();

        static Ref<spdlog::logger> getPythonLogger();

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_PythonLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}
