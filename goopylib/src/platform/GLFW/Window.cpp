#include "goopylib/core/Window.h"

#if (GP_LOG_WINDOW != true) and (GP_LOG_WINDOW <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_WINDOW
#endif

#if !GP_VALUE_CHECK_WINDOW
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"

namespace gp {
    Window::Window(int width, int height, const char *title)
            : m_Width(width),
              m_Height(height),
              m_Title(title),
              m_Background(Color(255, 255, 255)),

              m_xPos(0),
              m_yPos(0),
              m_WindowedXPos(m_xPos),
              m_WindowedYPos(m_yPos),

              m_WindowedWidth(m_Width),
              m_WindowedHeight(m_Height),

              m_Renderer((float) m_Width, (float) m_Height) {
        GP_CORE_INFO("gp::Window::Window({0}, {1} '{2}')", m_Width, m_Height, m_Title);

        GP_CHECK_GT(width, 0, "Window width must be greater than 0");
        GP_CHECK_GT(height, 0, "Window height must be greater than 0");

        m_Window = glfwCreateWindow(m_Width,
                                    m_Height,
                                    m_Title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, this);

        super();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);

        s_Instances.push_back(this);
    }

    Window::~Window() {
        GP_CORE_INFO("gp::Window::~Window() - '{0}'", m_Title);
        destroy();

        s_Instances.erase(std::remove(s_Instances.begin(), s_Instances.end(), this), s_Instances.end());
    }

    GLFWwindow *Window::getWindowGLFW() {
        GP_CORE_TRACE("gp::Window::getWindowGLFW() - '{0}'", m_Title);
        return m_Window;
    }

    bool Window::isClosed() const {
        GP_CORE_TRACE_ALL("gp::Window::isClosed() - '{0}'", m_Title);
        return m_IsDestroyed or glfwWindowShouldClose(m_Window);
    }
}

// Window Getter & Setters
namespace gp {
    // Title
    void Window::setTitle(const char *value) {
        GP_CORE_DEBUG("gp::setTitle({1}) - '{0}'", m_Title, value);

        m_Title = value;
        glfwSetWindowTitle(m_Window, m_Title);
    }

    WindowFrame Window::getFrameSize() const {
        GP_CORE_TRACE("gp::Window::getFrameSize() - '{0}'", m_Title);

        WindowFrame value{};
        glfwGetWindowFrameSize(m_Window, &value.left, &value.top, &value.right, &value.bottom);
        return value;
    }

    ContentScale Window::getContentScale() const {
        GP_CORE_TRACE("gp::Window::getContentScale() - '{0}'", m_Title);

        ContentScale value{};
        glfwGetWindowContentScale(m_Window, &value.xScale, &value.yScale);
        return value;
    }

    FramebufferSize Window::getFramebufferSize() const {
        GP_CORE_TRACE("gp::Window::getFramebufferSize() - '{0}'", m_Title);

        FramebufferSize value{};
        glfwGetFramebufferSize(m_Window, &value.width, &value.height);
        return value;
    }
}

// Window attribute methods
namespace gp {
    bool Window::isResizable() const {
        GP_CORE_TRACE("gp::Window::isResizable() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_RESIZABLE);
    }

    void Window::setResizable(bool value) {
        GP_CORE_DEBUG("gp::Window::setResizable({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isDecorated() const {
        GP_CORE_TRACE("gp::Window::isDecorated() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_DECORATED);
    }

    void Window::setDecorated(bool value) {
        GP_CORE_DEBUG("gp::Window::setDecorated({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFloating() const {
        GP_CORE_TRACE("gp::Window::isFloating() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_FLOATING);
    }

    void Window::setFloating(bool value) {
        GP_CORE_DEBUG("gp::Window::setFloating({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FLOATING, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isAutoMinimized() const {
        GP_CORE_TRACE("gp::Window::isAutoMinimized() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY);
    }

    void Window::setAutoMinimized(bool value) {
        GP_CORE_DEBUG("gp::Window::setAutoMinimized({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFocusedOnShow() const {
        GP_CORE_TRACE("gp::Window::isFocusedOnShow() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW);
    }

    void Window::setFocusedOnShow(bool value) {
        GP_CORE_DEBUG("gp::Window::setFocusedOnShow({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW, value ? GLFW_TRUE : GLFW_FALSE);
    }
}

// Window state methods
namespace gp {
    bool Window::isFullscreen() const {
        GP_CORE_TRACE("gp::Window::isFullscreen() - '{0}'", m_Title);
        return (bool) glfwGetWindowMonitor(m_Window);
    }

    void Window::maximize() {
        GP_CORE_INFO("gp::Window::maximize() - '{0}'", m_Title);
        glfwMaximizeWindow(m_Window);
    }

    bool Window::isMaximized() const {
        GP_CORE_TRACE("gp::Window::isMaximized() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED);
    }

    void Window::minimize() {
        GP_CORE_INFO("gp::Window::minimize() - '{0}'", m_Title);
        glfwIconifyWindow(m_Window);
    }

    bool Window::isMinimized() const {
        GP_CORE_TRACE("gp::Window::isMinimized() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED);
    }

    void Window::hide() {
        GP_CORE_INFO("gp::Window::hide() - '{0}'", m_Title);
        glfwHideWindow(m_Window);
    }

    void Window::show() {
        GP_CORE_INFO("gp::Window::show() - '{0}'", m_Title);
        glfwShowWindow(m_Window);
    }

    bool Window::isVisible() const {
        GP_CORE_TRACE("gp::Window::isVisible() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_VISIBLE);
    }

    void Window::focus() {
        GP_CORE_INFO("gp::Window::focus() - '{0}'", m_Title);
        glfwFocusWindow(m_Window);
    }

    bool Window::hasFocus() const {
        GP_CORE_TRACE("gp::Window::hasFocus() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
    }

    void Window::requestAttention() const {
        GP_CORE_DEBUG("gp::Window::requestAttention() - '{0}'", m_Title);
        glfwRequestWindowAttention(m_Window);
    }
}

// Window input events
namespace gp {
    bool Window::isMouseHovering() const {
        GP_CORE_TRACE("gp::Window::isMouseHovering() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_HOVERED);
    }

    Point Window::getMousePosition() const {
        GP_CORE_TRACE("gp::Window::getMousePosition() - '{0}'", m_Title);

        double xPos, yPos;
        glfwGetCursorPos(m_Window, &xPos, &yPos);
        return {(float) xPos, (float) yPos};
    }

    void Window::setCursorMode(CursorMode mode) const {
        GP_CORE_DEBUG("gp::Window::setCursorMode({1}) - '{0}'", m_Title, (int) mode);
        glfwSetInputMode(m_Window, GLFW_CURSOR, (int) mode);
    }

    bool Window::checkShiftKey() const {
        GP_CORE_TRACE("gp::Window::checkShiftKey() - '{0}'", m_Title);
        return m_KeyModifiers & (1 << 0);
    }

    bool Window::checkControlKey() const {
        GP_CORE_TRACE("gp::Window::checkControlKey() - '{0}'", m_Title);
        return m_KeyModifiers & (1 << 1);
    }

    bool Window::checkAltKey() const {
        GP_CORE_TRACE("gp::Window::checkAltKey() - '{0}'", m_Title);
        return m_KeyModifiers & (1 << 2);
    }

    bool Window::checkSuperKey() const {
        GP_CORE_TRACE("gp::Window::checkSuperKey() - '{0}'", m_Title);
        return m_KeyModifiers & (1 << 3);
    }

    int Window::checkKey(int key) const {
        GP_CORE_TRACE("gp::Window::checkKey({1}) - '{0}'", m_Title, key);
        return glfwGetKey(m_Window, key);
    }

    bool Window::checkMouseButton(int button) const {
        GP_CORE_TRACE("gp::Window::checkMouseButton({1}) - '{0}'", m_Title, button);
        return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
    }
}

// Window private methods
namespace gp {
    void Window::_swapBuffers() const {
        GP_CORE_TRACE_ALL("gp::Window::_swapBuffers() - {0}", m_Title);
        glfwSwapBuffers(m_Window);
    }

    void Window::_destroy() const {
        GP_CORE_TRACE("gp::Window::_destroy() - '{0}'", m_Title);
        glfwDestroyWindow(m_Window);
    }

    void Window::_updateSize() const {
        GP_CORE_TRACE("gp::Window::_updateSize() - '{0}' - ({1}, {2})", m_Title, m_Width, m_Height);
        glfwSetWindowSize(m_Window, m_Width, m_Height);
    }

    void Window::_updatePosition() const {
        GP_CORE_TRACE("gp::Window::_updatePosition() - '{0}'", m_Title);
        glfwSetWindowPos(m_Window, m_xPos, m_yPos);
    }

    void Window::_updateBackground() const {
        GP_CORE_TRACE_ALL("gp::Window::_updateBackground() - '{0}'", m_Title);
        glfwMakeContextCurrent(m_Window);
        glClearColor(m_Background.getRedf(),
                     m_Background.getGreenf(),
                     m_Background.getBluef(), 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::_updateSizeLimits() const {
        GP_CORE_TRACE("gp::Window::_updateSizeLimits() - '{0}'", m_Title);
        glfwSetWindowSizeLimits(m_Window, m_MinWidth, m_MinHeight,
                                m_MaxWidth, m_MaxHeight);
    }

    void Window::_updateAspectRatio(int numerator, int denominator) const {
        GP_CORE_TRACE("gp::Window::_updateAspectRatio() - '{0}'", m_Title);
        glfwSetWindowAspectRatio(m_Window, numerator, denominator);
    }
}

// Window private state methods
namespace gp {
    void Window::_fullscreen() const {
        GP_CORE_TRACE("gp::Window::_fullscreen() - '{0}'", m_Title);

        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    void Window::_unfullscreen(int width, int height, int xPos, int yPos) const {
        GP_CORE_TRACE("gp::Window::_unfullscreen() - '{0}'", m_Title);
        glfwSetWindowMonitor(m_Window, nullptr, xPos, yPos, width, height, 0);
    }

    void Window::_restore() const {
        GP_CORE_TRACE("gp::Window::_restore() - '{0}'", m_Title);
        glfwRestoreWindow(m_Window);
    }
}

// Window callbacks
namespace gp {
    void Window::setResizeCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_DEBUG("gp::Window::setResizeCallback() - '{0}'", m_Title);

        m_ResizeCallback = std::move(callback);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onResize(width, height);
        });
    }

    void Window::setCloseCallback(std::function<void(Window *)> callback) {
        GP_CORE_DEBUG("gp::Window::setCloseCallback() - '{0}'", m_Title);

        m_CloseCallback = std::move(callback);

        if (!m_CloseCallback) {
            glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            });
            return;
        }

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onClose();
        });
    }

    void Window::setPositionCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_TRACE("gp::Window::setPositionCallback() - '{0}'", m_Title);

        m_PositionCallback = std::move(callback);

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow *window, int xPos, int yPos) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMove(xPos, yPos);
            return;
        });
    }

    void Window::setMinimizeCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setMinimizeCallback() - '{0}'", m_Title);

        m_MinimizeCallback = std::move(callback);

        if (!m_MinimizeCallback) {
            glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *window, int iconified) {
            });
            return;
        }

        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *window, int iconified) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMinimize(iconified == GLFW_TRUE);
        });
    }

    void Window::setMaximizeCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setMaximizeCallback() - '{0}'", m_Title);

        m_MaximizeCallback = std::move(callback);

        if (!m_MaximizeCallback) {
            glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *window, int maximized) {
            });
            return;
        }

        // TODO fix issue with maximize callback not working. Tested on M1 MacOS Monterey 12.4, 3.3.8 Cocoa NSGL EGL OSMesa dynamic, OpenGL 4.1
        glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *window, int maximized) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMaximize(maximized == GLFW_TRUE);
        });
    }

    void Window::setFocusCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setFocusCallback() - '{0}'", m_Title);

        m_FocusedCallback = std::move(callback);

        if (!m_FocusedCallback) {
            glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *window, int focused) {
            });
            return;
        }

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *window, int focused) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onFocus(focused == GLFW_TRUE);
        });
    }

    void Window::setRefreshCallback(std::function<void(Window *)> callback) {
        GP_CORE_DEBUG("gp::Window::setRefreshCallback() - '{0}'", m_Title);

        m_RefreshCallback = std::move(callback);

        if (!m_RefreshCallback) {
            glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow *window) {
            });
            return;
        }

        glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow *window) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onRefreshRequired();
        });
    }

    void Window::setContentScaleCallback(std::function<void(Window *, float, float)> callback) {
        GP_CORE_DEBUG("gp::Window::setContentScaleCallback() - '{0}'", m_Title);

        m_ContentScaleCallback = std::move(callback);

        if (!m_ContentScaleCallback) {
            glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow *window, float xScale, float yScale) {
            });
            return;
        }

        glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow *window, float xScale, float yScale) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onContentScale(xScale, yScale);
        });
    }

    void Window::setFramebufferSizeCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_DEBUG("gp::Window::setFramebufferSizeCallback() - '{0}'", m_Title);

        m_FramebufferSizeCallback = std::move(callback);

        if (!m_FramebufferSizeCallback) {
            glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            });
            return;
        }

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onFramebufferSize(width, height);
        });
    }

    void Window::setMouseMotionCallback(std::function<void(Window *, float, float)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseMotionCallback() - '{0}'", m_Title);

        m_MouseMotionCallback = std::move(callback);

        if (!m_MouseMotionCallback) {
            glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            });
            return;
        }

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMouseMotion((float) xPos, (float) yPos);
        });
    }

    void Window::setMouseEnterCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseEnterCallback() - '{0}'", m_Title);

        m_MouseEnterCallback = std::move(callback);

        if (!m_MouseEnterCallback) {
            glfwSetCursorEnterCallback(m_Window, [](GLFWwindow *window, int entered) {
            });
            return;
        }

        glfwSetCursorEnterCallback(m_Window, [](GLFWwindow *window, int entered) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMouseEnter((bool) entered);
        });
    }

    void Window::setScrollCallback(std::function<void(Window *, float, float)> callback) {
        GP_CORE_DEBUG("gp::Window::setScrollCallback() - '{0}'", m_Title);

        m_ScrollCallback = std::move(callback);

        if (!m_ScrollCallback) {
            glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xScroll, double yScroll) {
            });
            return;
        }

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xScroll, double yScroll) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onScroll((float) xScroll, (float) yScroll);
        });
    }

    void Window::_setKeyCallback() const {
        GP_CORE_DEBUG("gp::Window::_setKeyCallback() - '{0}'", m_Title);

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onKeyPress(key, scancode, action, mods);
        });
    }

    void Window::_setMouseButtonCallback() const {
        GP_CORE_DEBUG("gp::Window::_setMouseButtonCallback() - '{0}'", m_Title);

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMousePress(button, action, mods);
        });
    }
}
