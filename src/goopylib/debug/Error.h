#pragma once

#include "gp.h"
#include "Log.h"

namespace gp {
    enum class ErrorType {
        RuntimeError,
        ValueError,
        FileNotFoundError,
    };

    GPAPI void setError(ErrorType type, const std::string& message);
}

#define GP_RUNTIME_ERROR(msg, ...) gp::setError(gp::ErrorType::RuntimeError, gp::strformat(msg, __VA_ARGS__))
#define GP_VALUE_ERROR(msg, ...) gp::setError(gp::ErrorType::ValueError, gp::strformat(msg, __VA_ARGS__))
#define GP_FILENOTFOUND_ERROR(msg, ...) gp::setError(gp::ErrorType::FileNotFoundError, strformat(msg, __VA_ARGS__))

#if GP_VALUE_CHECKING
#define GP_CHECK_EQUALS(variable, val, error) if ((variable) != (val)) { GP_VALUE_ERROR(error); }
#define GP_CHECK_NOT_EQUALS(variable, val, error) if ((variable) == (val)) { GP_VALUE_ERROR(error); }

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
