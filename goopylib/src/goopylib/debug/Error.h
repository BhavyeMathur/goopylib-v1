#pragma once

#include "Log.h"

#if !GP_VALUE_CHECKING
#undef GP_VALUE_CHECK_EASING
#endif

namespace gp {
    enum class ErrorType {
        None = 0,
        RuntimeError = 1,
        ValueError = 2,
    };

    template<typename... Args>
        void setError(ErrorType type, const char *message, Args &&... args) {
            GP_CORE_CRITICAL(message, std::forward<Args>(args)...);
            switch (type) {
                case ErrorType::ValueError:
                    throw std::invalid_argument(message);
                default:
                    throw std::runtime_error(message);
            }
        }
}

#define GP_RUNTIME_ERROR(...) gp::setError(gp::ErrorType::RuntimeError, __VA_ARGS__)
#define GP_VALUE_ERROR(...) gp::setError(gp::ErrorType::ValueError, __VA_ARGS__)

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
