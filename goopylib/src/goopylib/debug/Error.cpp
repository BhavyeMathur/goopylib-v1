#include "Error.h"
#include "Log.h"

namespace gp {
    static const char* errormessage;
    static ErrorType errortype = ErrorType::None;

    void _setError(ErrorType type, const char* message) {
        errormessage = message;
        errortype = type;
    }

    ErrorType getErrorCode() {
        GP_CORE_TRACE_ALL("gp::getErrorCode() -> {0}", (int) errortype);
        return errortype;
    }

    const char* getErrorMessage() {
        GP_CORE_TRACE_ALL("gp::getErrorMessage() -> '{0}'", errormessage);
        return errormessage;
    }
}
