#include "ext/config.h"

#if (GP_LOG_CAMERA != true) and (GP_LOG_CAMERA <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CAMERA
#endif

#if !GP_VALUE_CHECK_CAMERA
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"
