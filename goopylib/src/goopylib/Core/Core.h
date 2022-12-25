#pragma once

#include "gp.h"

namespace gp {
    extern bool glfw_initialized;

    int initialize();

    void terminate();

    void update();

    #if GP_USING_GLFW

    void updateOnEvent();

    void updateTimeout(double timeout);

    std::string glfwCompiledVersion();

    std::string glfwCurrentVersion();

    int getRefreshRate();

    int getScreenWidth();

    int getScreenHeight();

    int getNumberOfMonitors();

    void setBufferSwapInterval(int interval);

    #endif

    #if GP_USING_OPENGL

    std::string openglVersion();

    #endif
}
