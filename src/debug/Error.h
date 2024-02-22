#pragma once

#include "gp.h"

namespace gp {
    enum class ErrorType {
        RuntimeError,
        ValueError,
        FileNotFoundError,
    };

    void setError(ErrorType type, const std::string &message);
}

#if GP_VALUE_CHECKING
#define GP_CHECK_EQUALS(variable, val, error) if ((variable) != (val)) { GP_VALUE_ERROR(error); }
#define GP_CHECK_NOT_EQUALS(variable, val, error) if ((variable) == (val)) { GP_VALUE_ERROR(error); }
#define GP_CHECK_RENDERER_ID(error) if (m_RendererID == 0) { GP_RUNTIME_ERROR(error " object is uninitialized"); }
#define GP_CHECK_NOT_NULL(variable) GP_CHECK_NOT_EQUALS(variable, nullptr, #variable " must not be a nullptr")

#define GP_CHECK_GT(variable, val, error) if ((variable) <= (val)) { GP_VALUE_ERROR(error); }
#define GP_CHECK_GE(variable, val, error) if ((variable) < (val)) { GP_VALUE_ERROR(error); }

#define GP_CHECK_LT(variable, val, error) if ((variable) >= (val)) { GP_VALUE_ERROR(error); }
#define GP_CHECK_LE(variable, val, error) if ((variable) > (val)) { GP_VALUE_ERROR(error); }

#define GP_CHECK_INCLUSIVE_RANGE(variable, min, max, error) if ((variable) < (min) or (variable) > (max)) { GP_VALUE_ERROR(error); }
#define GP_CHECK_EXCLUSIVE_RANGE(variable, min, max, error) if ((variable) <= (min) or (variable) >= (max)) { GP_VALUE_ERROR(error); }
#else
#define GP_CHECK_EQUALS(variable, val, error) {}
#define GP_CHECK_NOT_EQUALS(variable, val, error) {}

#define GP_CHECK_GT(variable, val, error) {}
#define GP_CHECK_GE(variable, val, error) {}

#define GP_CHECK_LT(variable, val, error) {}
#define GP_CHECK_LE(variable, val, error) {}

#define GP_CHECK_INCLUSIVE_RANGE(variable, min, max, error) {}
#define GP_CHECK_EXCLUSIVE_RANGE(variable, min, max, error) {}
#endif

#if GP_ERROR_CHECKING
#define GP_CHECK_INITIALISED(src) do {if (!isInitialized()) { GP_RUNTIME_ERROR(src " goopylib must be initialized first!"); }} while (0)
#define GP_CHECK_ACTIVE_CONTEXT(src) do {if (!glfwGetCurrentContext()) { GP_RUNTIME_ERROR(src " goopylib must have an active window!"); }} while (0)
#define GP_RUNTIME_ERROR(...) gp::setError(gp::ErrorType::RuntimeError, gp::strformat(__VA_ARGS__))
#define GP_VALUE_ERROR(...) gp::setError(gp::ErrorType::ValueError, gp::strformat(__VA_ARGS__))
#define GP_FILENOTFOUND_ERROR(...) gp::setError(gp::ErrorType::FileNotFoundError, strformat(__VA_ARGS__))
#else
#define GP_CHECK_INITIALISED(src) nullptr
#define GP_RUNTIME_ERROR(...) nullptr
#define GP_VALUE_ERROR(...) nullptr
#define GP_FILENOTFOUND_ERROR(...) nullptr
#endif
