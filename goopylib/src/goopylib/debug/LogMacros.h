#pragma once

#include <glm/gtx/string_cast.hpp>

#if (GP_LOGGING_LEVEL >= 1)
#define GP_CORE_CRITICAL(...) gp::Log::getCoreLogger()->critical(__VA_ARGS__)
#define GP_CRITICAL(...)      gp::Log::ClientLogger()->critical(__VA_ARGS__)
#else
#define GP_CORE_CRITICAL(...) nullptr
#define GP_CRITICAL(...) nullptr
#endif

#if (GP_LOGGING_LEVEL >= 2)
#define GP_CORE_ERROR(...)    gp::Log::getCoreLogger()->error(__VA_ARGS__)
#define GP_ERROR(...)         gp::Log::getClientLogger()->error(__VA_ARGS__)
#else
#define GP_CORE_ERROR(...) nullptr
#define GP_ERROR(...) nullptr
#endif

#if (GP_LOGGING_LEVEL >= 3)
#define GP_CORE_WARN(...)     gp::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GP_WARN(...)          gp::Log::getClientLogger()->warn(__VA_ARGS__)
#else
#define GP_CORE_WARN(...) nullptr
#define GP_WARN(...) nullptr
#endif

#if (GP_LOGGING_LEVEL >= 4)
#define GP_CORE_INFO(...)     gp::Log::getCoreLogger()->info(__VA_ARGS__)
#define GP_INFO(...)          gp::Log::getClientLogger()->info(__VA_ARGS__)
#else
#define GP_CORE_INFO(...) nullptr
#define GP_INFO(...) nullptr
#endif

#if (GP_LOGGING_LEVEL >= 5)
#define GP_CORE_DEBUG(...)    gp::Log::getCoreLogger()->debug(__VA_ARGS__)
#define GP_DEBUG(...)         gp::Log::getClientLogger()->debug(__VA_ARGS__)
#else
#define GP_CORE_DEBUG(...) nullptr
#define GP_DEBUG(...) nullptr
#endif

#if (GP_LOGGING_LEVEL >= 6)
#define GP_CORE_TRACE(...)    gp::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GP_TRACE(...)         gp::Log::getClientLogger()->trace(__VA_ARGS__)
#else
#define GP_CORE_TRACE(...) nullptr
#define GP_TRACE(...) nullptr
#endif

#if (GP_LOGGING_LEVEL >= 7)
#define GP_CORE_TRACE_ALL(...)    gp::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GP_TRACE_ALL(...)         gp::Log::getClientLogger()->trace(__VA_ARGS__)
#else
#define GP_CORE_TRACE_ALL(...) nullptr
#define GP_TRACE_ALL(...) nullptr
#endif
