#include "camera_controller.h"

#include "ext/config.h"

#if (GP_LOG_CAMERA_CONTROLLER != true) and (GP_LOG_CAMERA_CONTROLLER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CAMERA_CONTROLLER
#endif

#if !GP_VALUE_CHECK_CAMERA_CONTROLLER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "ext/debug.h"
