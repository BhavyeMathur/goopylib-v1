#pragma once

#include "pch.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)

namespace gp {

    class Log {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger> &getCoreLogger() { return s_CoreLogger; }

        static std::shared_ptr<spdlog::logger> &getPythonLogger() { return s_PythonLogger; }

        static std::shared_ptr<spdlog::logger> &getClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_PythonLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector) {
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix) {
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion) {
    return os << glm::to_string(quaternion);
}

#if GP_LOGGING
// Core log macros
#define GP_CORE_TRACE(...)    ::gp::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GP_CORE_INFO(...)     ::gp::Log::getCoreLogger()->info(__VA_ARGS__)
#define GP_CORE_WARN(...)     ::gp::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GP_CORE_ERROR(...)    ::gp::Log::getCoreLogger()->error(__VA_ARGS__)
#define GP_CORE_CRITICAL(...) ::gp::Log::getCoreLogger()->critical(__VA_ARGS__)

// Python log macros
#define GP_PY_TRACE(...)    ::gp::Log::getPythonLogger()->trace(__VA_ARGS__)
#define GP_PY_INFO(...)     ::gp::Log::getPythonLogger()->info(__VA_ARGS__)
#define GP_PY_WARN(...)     ::gp::Log::getPythonLogger()->warn(__VA_ARGS__)
#define GP_PY_ERROR(...)    ::gp::Log::getPythonLogger()->error(__VA_ARGS__)
#define GP_PY_CRITICAL(...) ::gp::Log::getPythonLogger()->critical(__VA_ARGS__)

// Client log macros
#define GP_TRACE(...)         ::gp::Log::getClientLogger()->trace(__VA_ARGS__)
#define GP_INFO(...)          ::gp::Log::getClientLogger()->info(__VA_ARGS__)
#define GP_WARN(...)          ::gp::Log::getClientLogger()->warn(__VA_ARGS__)
#define GP_ERROR(...)         ::gp::Log::getClientLogger()->error(__VA_ARGS__)
#define GP_CRITICAL(...)      ::gp::Log::getClientLogger()->critical(__VA_ARGS__)
#else
// Core log macros
#define GP_CORE_TRACE(...)
#define GP_CORE_INFO(...)
#define GP_CORE_WARN(...)
#define GP_CORE_ERROR(...)
#define GP_CORE_CRITICAL(...)

// Client log macros
#define GP_TRACE(...)
#define GP_INFO(...)
#define GP_WARN(...)
#define GP_ERROR(...)
#define GP_CRITICAL(...)
#endif
