#pragma once

namespace gp {
    extern bool glfw_initialized;

    int Initialize();

    void Terminate();

    void Update();

    #if GP_USING_GLFW

    void UpdateOnEvent();

    void UpdateTimeout(double timeout);

    std::string GLFWCompiledVersion();

    std::string GLFWCurrentVersion();

    int GetRefreshRate();

    int GetScreenWidth();

    int GetScreenHeight();

    int GetNumberOfMonitors();

    void SetBufferSwapInterval(int interval);

    #endif

    #if GP_USING_OPENGL

    std::string OpenGLVersion();

    #endif
}
