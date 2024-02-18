#include "Error.h"

#include "core/Core.h"

namespace gp {
    void setError(ErrorType type, const std::string& message) {
        if (isInitialized()) {
            GP_CORE_CRITICAL(message);
        }

        switch (type) {
            case ErrorType::ValueError:
                throw std::invalid_argument(message);
            case ErrorType::RuntimeError:
            case ErrorType::FileNotFoundError:
            default:
                throw std::runtime_error(message);
        }
    }
}
