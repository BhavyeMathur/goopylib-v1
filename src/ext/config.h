#pragma once

#define GP_USING_GLFW true
#define GP_USING_OPENGL true

#define GP_ERROR_CHECKING true
#define GP_TYPE_CHECKING true
#define GP_VALUE_CHECKING true

/*
 0 - No Logging
 1 - Fatals Enabled
 2 - Errors Enabled
 3 - Warnings Enabled
 4 - Info Enabled
 5 - Debug Enabled
 6 - Trace Enabled
 7 - All Enabled
 */
#define GP_PY_LOGGING_LEVEL 3

/* Module Specific Config --------------------------------------------------------------------------------------------*/

// core

#define GP_VALUE_CHECK_CORE true
#define GP_LOG_CORE 5

#define GP_VALUE_CHECK_WINDOW true
#define GP_LOG_WINDOW 5

// math

#define GP_LOG_EASING true
#define GP_VALUE_CHECK_EASING true

// color

#define GP_LOG_COLOR true
#define GP_VALUE_CHECK_COLOR true

#define GP_LOG_COLOR_CONVERSIONS true
#define GP_VALUE_CHECKING_COLOR_CONVERSIONS true

// objects

#define GP_LOG_RENDERABLE true
#define GP_VALUE_CHECK_RENDERABLE true
