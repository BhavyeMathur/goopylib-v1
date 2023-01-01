#pragma once

#include "gp.h"
#include <cstring>

namespace gp {
    extern bool glfw_initialized;

    /**
     * Initializes goopylib internally.
     *
     * @throws std::runtime_error: if the initialization fails
    */
    GPAPI void init();

    /**
     * Terminates goopylib internally and destroys all open Windows.
     *
     * @note goopylib can be reinitialized using gp::init()
     */
    GPAPI void terminate();

    /**
     * Updates goopylib and its windows.
     *
     * The following is a standard goopylib mainloop:
     *
     * @code{.cpp}
     *      auto window = gp::Window({500, 500});
     *
     *      while (window.isOpen()) {
     *          gp::update();
     *      }
     * @endcode
     */
    GPAPI void update();

    #if GP_USING_GLFW

    /**
     * Updates goopylib every time an event occurs.
     */
    GPAPI void updateOnEvent();

    /**
     * Updates goopylib after a duration has passed.
     * @param timeout the duration (seconds) to wait between updates. Defaults to 0.
     * @throws std::invalid_argument: if timeout is less than 0
     */
    GPAPI void updateTimeout(double timeout = 0);

    /**
     *
     * @return the version of GLFW that goopylib was compiled with.
     */
    GPAPI std::string glfwCompiledVersion();

    /**
     *
     * @return the version of GLFW that is currently running.
     */
    GPAPI std::string glfwCurrentVersion();

    /**
     *
     * @return the refresh rate of the primary monitor in Hertz
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    GPAPI int getRefreshRate();

    /**
     *
     * @return the screen width in screen coordinates
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    GPAPI int getScreenWidth();

    /**
     *
     * @return the screen height in screen coordinates
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    GPAPI int getScreenHeight();

    /**
     *
     * @return the number of monitors connected.
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    GPAPI int getNumberOfMonitors();

    /**
     * Sets the rate of swapping Window buffers.
     * @param interval the number of refreshes to wait before swapping buffers.
     * @throws std::invalid_argument: if interval is less than 0
     */
    GPAPI void setBufferSwapInterval(int32_t interval);

    /**
     *
     * @return the number of seconds since goopylib was initialized
     */
    GPAPI float getTime();

    #endif

    #if GP_USING_OPENGL

    /**
     *
     * @return the version of OpenGL being used.
     */
    GPAPI std::string openglVersion();

    #endif
}
