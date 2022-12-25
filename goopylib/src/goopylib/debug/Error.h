#pragma once

namespace gp {
    enum class ErrorType {
        None = 0,
        RuntimeError = 1,
        ValueError = 2,
    };

    void setError(ErrorType type, const char* message);

    ErrorType getErrorCode();

    const char* getErrorMessage();
}

#define GP_RUNTIME_ERROR(string) setError(gp::ErrorType::RuntimeError, string)
