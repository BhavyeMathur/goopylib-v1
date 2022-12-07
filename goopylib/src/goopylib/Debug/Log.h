#pragma once

namespace gp {
    extern void loggerInit();

    extern std::shared_ptr<spdlog::logger> CoreLogger;
    extern std::shared_ptr<spdlog::logger> PythonLogger;
    extern std::shared_ptr<spdlog::logger> ClientLogger;
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
#define GP_CORE_TRACE(...)    gp::CoreLogger->trace(__VA_ARGS__)
#define GP_CORE_INFO(...)     gp::CoreLogger->info(__VA_ARGS__)
#define GP_CORE_WARN(...)     gp::CoreLogger->warn(__VA_ARGS__)
#define GP_CORE_ERROR(...)    gp::CoreLogger->error(__VA_ARGS__)
#define GP_CORE_CRITICAL(...) gp::CoreLogger->critical(__VA_ARGS__)

// Python log macros
#define GP_PY_TRACE(...)    gp::PythonLogger->trace(__VA_ARGS__)
#define GP_PY_INFO(...)     gp::PythonLogger->info(__VA_ARGS__)
#define GP_PY_WARN(...)     gp::PythonLogger->warn(__VA_ARGS__)
#define GP_PY_ERROR(...)    gp::PythonLogger->error(__VA_ARGS__)
#define GP_PY_CRITICAL(...) gp::PythonLogger->critical(__VA_ARGS__)

// Client log macros
#define GP_TRACE(...)         gp::ClientLogger->trace(__VA_ARGS__)
#define GP_INFO(...)          gp::ClientLogger->info(__VA_ARGS__)
#define GP_WARN(...)          gp::ClientLogger->warn(__VA_ARGS__)
#define GP_ERROR(...)         gp::ClientLogger->error(__VA_ARGS__)
#define GP_CRITICAL(...)      gp::ClientLogger->critical(__VA_ARGS__)
#else
// Core log macros
#define GP_CORE_TRACE(...)
#define GP_CORE_INFO(...)
#define GP_CORE_WARN(...)
#define GP_CORE_ERROR(...)
#define GP_CORE_CRITICAL(...)

// Python log macros
#define GP_PY_TRACE(...)
#define GP_PY_INFO(...)
#define GP_PY_WARN(...)
#define GP_PY_ERROR(...)
#define GP_PY_CRITICAL(...)

// Client log macros
#define GP_TRACE(...)
#define GP_INFO(...)
#define GP_WARN(...)
#define GP_ERROR(...)
#define GP_CRITICAL(...)
#endif

#if GP_LOGGING_WINDOW
#define GP_WINDOW_TRACE(...) GP_CORE_TRACE("WINDOW: " __VA_ARGS__)
#define GP_WINDOW_INFO(...) GP_CORE_INFO("WINDOW: " __VA_ARGS__)

#define GP_PY_WINDOW_TRACE(...) GP_PY_TRACE("WINDOW: " __VA_ARGS__)
#define GP_PY_WINDOW_INFO(...) GP_PY_INFO("WINDOW: " __VA_ARGS__)
#else
#define GP_WINDOW_TRACE(...)
#define GP_WINDOW_INFO(...)

#define GP_PY_WINDOW_TRACE(...)
#define GP_PY_WINDOW_INFO(...)
#endif

#if GP_LOGGING_COLORS
#define GP_COLOR_TRACE(...) GP_PY_TRACE("COLOR: " __VA_ARGS__)
#define GP_COLOR_INFO(...) GP_PY_INFO("COLOR: " __VA_ARGS__)

#define GP_PY_COLOR_TRACE(...) GP_PY_TRACE("COLOR: " __VA_ARGS__)
#define GP_PY_COLOR_INFO(...) GP_PY_INFO("COLOR: " __VA_ARGS__)
#else
#define GP_COLOR_TRACE(...)
#define GP_COLOR_INFO(...)

#define GP_PY_COLOR_TRACE(...)
#define GP_PY_COLOR_INFO(...)
#endif
