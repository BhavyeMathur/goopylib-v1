#pragma once

#include "goopylib/Debug/Log.h"
#include "goopylib/Color/W3CX11.h"
#include "Platform/Independent/BaseWindow.h"

namespace gp {
    GPAPI extern bool glfw_initialized;

    GPAPI int Initialize();

    GPAPI void Terminate();

    GPAPI void Update();

    #if GP_USING_GLFW

    GPAPI void UpdateOnEvent();

    GPAPI void UpdateTimeout(double timeout);

    GPAPI std::string GLFWCompiledVersion();

    GPAPI std::string GLFWCurrentVersion();

    GPAPI int GetRefreshRate();

    GPAPI int GetScreenWidth();

    GPAPI int GetScreenHeight();

    GPAPI int GetNumberOfMonitors();

    GPAPI void SetBufferSwapInterval(int interval);

    #endif

    #if GP_USING_OPENGL

    GPAPI std::string OpenGLVersion();

    #endif
}
