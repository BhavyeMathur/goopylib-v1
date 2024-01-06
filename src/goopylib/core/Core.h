#pragma once

#include "gp.h"

namespace gp {
    /**
     * Initializes goopylib internally.
     *
     * @throws std::runtime_error: if the initialization fails
    */
    GPAPI void init();

    /**
     * Terminates goopylib internally and destroys all open windows.\n
     * You should call this function before the program ends.
     *
     * @note goopylib can be reinitialized using gp::init()
     */
    GPAPI void terminate();

    /**
     *
     * @return whether goopylib has been initialized
     */
    GPAPI bool isInitialized();

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
     * Sets the rate of swapping window buffers.
     * @param interval the number of refreshes to wait before swapping buffers.
     * @throws std::invalid_argument: if interval is less than 0
     */
    GPAPI void setBufferSwapInterval(int32_t interval);

    /**
     *
     * @return the refresh rate of the primary monitor in Hertz
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    [[nodiscard]] GPAPI int getRefreshRate();

    /**
     *
     * @return the screen width in screen coordinates
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    [[nodiscard]] GPAPI int getScreenWidth();

    /**
     *
     * @return the screen height in screen coordinates
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    [[nodiscard]] GPAPI int getScreenHeight();

    /**
     *
     * @return the number of monitors connected.
     * @throws std::runtime_error: if goopylib has not been initialized
     */
    [[nodiscard]] GPAPI int getNumberOfMonitors();

    /**
     *
     * @return the number of seconds since goopylib was initialized
     */
    [[nodiscard]] GPAPI float getTime();

    /**
     *
     * @return whether a graphics context is currently active
     */
    [[nodiscard]] GPAPI bool hasActiveContext();

    /**
     *
     * @return the version of GLFW that goopylib was compiled with.
     */
    [[nodiscard]] GPAPI std::string glfwCompiledVersion();

    /**
     *
     * @return the version of GLFW that is currently running.
     */
    [[nodiscard]] GPAPI std::string glfwCurrentVersion();

    #endif

    #if GP_USING_OPENGL

    /**
     *
     * @return the version of OpenGL being used.
     */
    [[nodiscard]] GPAPI std::string openglVersion();

    #endif
}
