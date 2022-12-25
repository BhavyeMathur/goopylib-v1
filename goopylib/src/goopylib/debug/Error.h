#pragma once

#include "Log.h"

namespace gp {
    enum class ErrorType {
        None = 0,
        RuntimeError = 1,
        ValueError = 2,
    };

    void _setError(ErrorType type, const char* message);

    template<typename... Args>
    void setError(ErrorType type, const char* message, Args &&... args) {
        GP_CORE_CRITICAL(message, std::forward<Args>(args)...);
        _setError(type, message);
    }

    ErrorType getErrorCode();

    const char* getErrorMessage();
}

#define GP_RUNTIME_ERROR(...) gp::setError(gp::ErrorType::RuntimeError, __VA_ARGS__)
