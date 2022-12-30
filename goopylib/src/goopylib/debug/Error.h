#pragma once

#include "Log.h"

namespace gp {
    enum class ErrorType {
        RuntimeError,
        ValueError,
        FileNotFoundError,
    };

    template<typename... Args>
        void setError(ErrorType type, const char *message, Args &&... args) {
            GP_CORE_CRITICAL(message, std::forward<Args>(args)...);

            switch (type) {
                case ErrorType::ValueError:
                    throw std::invalid_argument(message);
                case ErrorType::RuntimeError:
                    throw std::runtime_error(message);
                case ErrorType::FileNotFoundError:
                    // Because C++98 (needed for the Python extension) does not have std::filestyle::filestyle_error
                    throw std::runtime_error(message);
            }
        }
}

#define GP_RUNTIME_ERROR(...) gp::setError(gp::ErrorType::RuntimeError, __VA_ARGS__)
#define GP_VALUE_ERROR(...) gp::setError(gp::ErrorType::ValueError, __VA_ARGS__)
#define GP_FILENOTFOUND_ERROR(...) gp::setError(gp::ErrorType::FileNotFoundError, __VA_ARGS__)

#if GP_VALUE_CHECKING
#define GP_CHECK_EQUALS(variable, val, error) do { if ((variable) != (val)) { GP_VALUE_ERROR(error); } } while (0)
#define GP_CHECK_NOT_EQUALS(variable, val, error) do { if ((variable) == (val)) { GP_VALUE_ERROR(error); } } while (0)

#define GP_CHECK_GT(variable, val, error) do { if ((variable) <= (val)) { GP_VALUE_ERROR(error); } } while (0)
#define GP_CHECK_GE(variable, val, error) do { if ((variable) < (val)) { GP_VALUE_ERROR(error); } } while (0)

#define GP_CHECK_LT(variable, val, error) do { if ((variable) >= (val)) { GP_VALUE_ERROR(error); } } while (0)
#define GP_CHECK_LE(variable, val, error) do { if ((variable) > (val)) { GP_VALUE_ERROR(error); } } while (0)

#define GP_CHECK_INCLUSIVE_RANGE(variable, min, max, error) do { if ((variable) < (min) or (variable) > (max)) { GP_VALUE_ERROR(error); } } while (0)
#define GP_CHECK_EXCLUSIVE_RANGE(variable, min, max, error) do { if ((variable) <= (min) or (variable) >= (max)) { GP_VALUE_ERROR(error); } } while (0)
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
