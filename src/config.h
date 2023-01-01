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
#define GP_LOGGING_LEVEL 3

/* Module Specific Config --------------------------------------------------------------------------------------------*/

// core

#define GP_VALUE_CHECK_CORE true
#define GP_LOG_CORE 3

#define GP_VALUE_CHECK_BUFFER true
#define GP_LOG_BUFFER 3

#define GP_VALUE_CHECK_TEXTURE2D true
#define GP_LOG_TEXTURE2D true

#define GP_VALUE_CHECK_VERTEX_ARRAY true
#define GP_LOG_VERTEX_ARRAY 3

#define GP_VALUE_CHECK_WINDOW true
#define GP_LOG_WINDOW 3

#define GP_VALUE_CHECK_SHADER true
#define GP_LOG_SHADER 3

// math

#define GP_VALUE_CHECK_EASING true
#define GP_LOG_EASING 3

// color

#define GP_VALUE_CHECK_COLOR true
#define GP_LOG_COLOR 3

#define GP_VALUE_CHECK_COLOR_UTIL true
#define GP_LOG_COLOR_UTIL 3

#define GP_VALUE_CHECK_W3CX11 true
#define GP_LOG_W3CX11 3

#define GP_LOG_COLOR_CONVERSIONS true
#define GP_VALUE_CHECKING_COLOR_CONVERSIONS true

// scene

#define GP_VALUE_CHECK_CAMERA true
#define GP_LOG_CAMERA 3

#define GP_VALUE_CHECK_CAMERA_CONTROLLER true
#define GP_LOG_CAMERA_CONTROLLER 3

#define GP_VALUE_CHECK_RENDERER true
#define GP_LOG_RENDERER true

// objects

#define GP_VALUE_CHECK_LINE true
#define GP_LOG_LINE 3

#define GP_VALUE_CHECK_TRIANGLE true
#define GP_LOG_TRIANGLE 3

#define GP_VALUE_CHECK_QUAD true
#define GP_LOG_QUAD 3

#define GP_VALUE_CHECK_ELLIPSE true
#define GP_LOG_ELLIPSE 3

#define GP_VALUE_CHECK_CIRCLE true
#define GP_LOG_CIRCLE 3

#define GP_VALUE_CHECK_IMAGE true
#define GP_LOG_IMAGE true

#define GP_VALUE_CHECK_RENDERABLE true
#define GP_LOG_RENDERABLE 3
