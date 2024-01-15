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

        static shared_ptr<spdlog::logger> getCoreLogger();

        GPAPI static shared_ptr<spdlog::logger> getClientLogger();

        GPAPI static shared_ptr<spdlog::logger> getPythonLogger();

    private:
        static shared_ptr<spdlog::logger> s_CoreLogger;
        static shared_ptr<spdlog::logger> s_PythonLogger;
        static shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

namespace gp {
    template<typename ... Args>
        std::string strformat(const std::string &format, Args ... args) {
            int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
            if (size_s <= 0) {
                throw std::runtime_error("Error during string formatting");
            }
            auto size = static_cast<size_t>( size_s );
            const unique_ptr<char[]> buf(new char[size]);
            if (std::snprintf(buf.get(), size, format.c_str(), args ...) < 0) {
                throw std::runtime_error("Error during string formatting");
            }
            return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
        }
}
