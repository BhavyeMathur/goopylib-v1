#pragma once

#include "src/pch.h"

namespace gp {
    class GPAPI Log {

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

#if (GP_LOGGING >= 1)
#define GP_CORE_CRITICAL(...) gp::Log::getCoreLogger()->critical(__VA_ARGS__)
#define GP_PY_CRITICAL(...) gp::Log::getPythonLogger()->critical(__VA_ARGS__)
#define GP_CRITICAL(...)      gp::Log::ClientLogger()->critical(__VA_ARGS__)
#else
#define GP_CORE_CRITICAL(...) nullptr
#define GP_PY_CRITICAL(...) nullptr
#define GP_CRITICAL(...) nullptr
#endif

#if (GP_LOGGING >= 2)
#define GP_CORE_ERROR(...)    gp::Log::getCoreLogger()->error(__VA_ARGS__)
#define GP_PY_ERROR(...)    gp::Log::getPythonLogger()->error(__VA_ARGS__)
#define GP_ERROR(...)         gp::Log::getClientLogger()->error(__VA_ARGS__)
#else
#define GP_CORE_ERROR(...) nullptr
#define GP_PY_ERROR(...) nullptr
#define GP_ERROR(...) nullptr
#endif

#if (GP_LOGGING >= 3)
#define GP_CORE_WARN(...)     gp::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GP_PY_WARN(...)     gp::Log::getPythonLogger()->warn(__VA_ARGS__)
#define GP_WARN(...)          gp::Log::getClientLogger()->warn(__VA_ARGS__)
#else
#define GP_CORE_WARN(...) nullptr
#define GP_PY_WARN(...) nullptr
#define GP_WARN(...) nullptr
#endif

#if (GP_LOGGING >= 4)
#define GP_CORE_INFO(...)     gp::Log::getCoreLogger()->info(__VA_ARGS__)
#define GP_PY_INFO(...)     gp::Log::getPythonLogger()->info(__VA_ARGS__)
#define GP_INFO(...)          gp::Log::getClientLogger()->info(__VA_ARGS__)
#else
#define GP_CORE_INFO(...) nullptr
#define GP_PY_INFO(...) nullptr
#define GP_INFO(...) nullptr
#endif

#if (GP_LOGGING >= 5)
#define GP_CORE_DEBUG(...)    gp::Log::getCoreLogger()->debug(__VA_ARGS__)
#define GP_PY_DEBUG(...)    gp::Log::getPythonLogger()->debug(__VA_ARGS__)
#define GP_DEBUG(...)         gp::Log::getClientLogger()->debug(__VA_ARGS__)
#else
#define GP_CORE_DEBUG(...) nullptr
#define GP_PY_DEBUG(...) nullptr
#define GP_DEBUG(...) nullptr
#endif

#if (GP_LOGGING >= 6)
#define GP_CORE_TRACE(...)    gp::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GP_PY_TRACE(...)    gp::Log::getPythonLogger()->trace(__VA_ARGS__)
#define GP_TRACE(...)         gp::Log::getClientLogger()->trace(__VA_ARGS__)
#else
#define GP_CORE_TRACE(...) nullptr
#define GP_PY_TRACE(...) nullptr
#define GP_TRACE(...) nullptr
#endif
