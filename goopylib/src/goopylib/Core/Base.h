#pragma once

#include "goopylib/Debug/Log.h"
#include "goopylib/Color/W3CX11.h"
#include "Platform/Independent/BaseWindow.h"

namespace gp {
    GPAPI extern bool glfw_initialized;

    GPAPI int initialize();

    GPAPI void terminate();

    GPAPI void update();

    #if GP_USING_GLFW

    GPAPI void updateOnEvent();

    GPAPI void updateTimeout(double timeout);

    GPAPI std::string glfwCompiledVersion();

    GPAPI std::string glfwCurrentVersion();

    GPAPI int getRefreshRate();

    GPAPI int getScreenWidth();

    GPAPI int getScreenHeight();

    GPAPI int getNumberOfMonitors();

    GPAPI void setBufferSwapInterval(int interval);

    #endif

    #if GP_USING_OPENGL

    GPAPI std::string openglVersion();

    #endif
}
