#include "pch.h"
#include "goopylib/Core/Window.h"

#if GP_USING_GLFW

namespace gp {
    Window::Window(const WindowConfig &config) : BaseWindow(config) {
        GP_CORE_INFO("Creating window '{0}' ({1}, {2})", config.title, config.width, config.height);

        m_Window = glfwCreateWindow(m_Data.width,
                                    m_Data.height,
                                    m_Data.title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, this);

        super();
    }

    Window::~Window() {
        GP_CORE_INFO("Deallocating window '{0}'", m_Data.title);
        destroy();
    }

    GLFWwindow *Window::getWindowGLFW() {
        return m_Window;
    }
}

// Window attribute methods
namespace gp {
    bool Window::isResizable() const {
        return glfwGetWindowAttrib(m_Window, GLFW_RESIZABLE);
    }

    void Window::setResizable(bool value) {
        GP_CORE_TRACE("Set '{0}' resizable -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isDecorated() const {
        return glfwGetWindowAttrib(m_Window, GLFW_DECORATED);
    }

    void Window::setDecorated(bool value) {
        GP_CORE_TRACE("Set '{0}' decorated -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFloating() const {
        return glfwGetWindowAttrib(m_Window, GLFW_FLOATING);
    }

    void Window::setFloating(bool value) {
        GP_CORE_TRACE("Set '{0}' floating -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FLOATING, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isAutoMinimized() const {
        return glfwGetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY);
    }

    void Window::setAutoMinimized(bool value) {
        GP_CORE_TRACE("Set '{0}' auto minimized -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFocusedOnShow() const {
        return glfwGetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW);
    }

    void Window::setFocusedOnShow(bool value) {
        GP_CORE_TRACE("Set '{0}' focused on show -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW, value ? GLFW_TRUE : GLFW_FALSE);
    }

    WindowFrame Window::getFrameSize() const {
        WindowFrame value{};
        glfwGetWindowFrameSize(m_Window, &value.left, &value.top, &value.right, &value.bottom);
        return value;
    }

    ContentScale Window::getContentScale() const {
        ContentScale value{};
        glfwGetWindowContentScale(m_Window, &value.xScale, &value.yScale);
        return value;
    }

    FramebufferSize Window::getFramebufferSize() const {
        FramebufferSize value{};
        glfwGetFramebufferSize(m_Window, &value.width, &value.height);
        return value;
    }
}

// Window state methods
namespace gp {
    bool Window::isFullscreen() const {
        return (bool) glfwGetWindowMonitor(m_Window);
    }

    bool Window::isMaximized() const {
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED);
    }

    bool Window::isMinimized() const {
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED);
    }

    bool Window::isVisible() const {
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_VISIBLE);
    }

    bool Window::hasFocus() const {
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
    }

    void Window::requestAttention() const {
        glfwRequestWindowAttention(m_Window);
    }
}

// Window callbacks
namespace gp {
    void Window::_setResizeCallback() const {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onResize(width, height);
        });
    }

    void Window::_setCloseCallback() const {
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onClose();
        });
    }

    void Window::_setPositionCallback() const {
        glfwSetWindowPosCallback(m_Window, [](GLFWwindow *window, int xPos, int yPos) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMove(xPos, yPos);
        });
    }

    void Window::_setMinimizeCallback() const {
        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *window, int iconified) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMinimize(iconified == GLFW_TRUE);
        });
    }

    void Window::_setMaximizeCallback() const {
        glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *window, int maximized) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onMaximize(maximized == GLFW_TRUE);
        });
    }

    void Window::_setFocusedCallback() const {
        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *window, int focused) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onFocus(focused == GLFW_TRUE);
        });
    }

    void Window::_setRefreshCallback() const {
        glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow *window) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onRefreshRequired();
        });
    }

    void Window::_setContentScaleCallback() const {
        glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow *window, float xScale, float yScale) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onContentScale(xScale, yScale);
        });
    }

    void Window::_setFramebufferSizeCallback() const {
        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onFramebufferSize(width, height);
        });
    }

    void Window::_setKeyCallback() const {
        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            Window *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->onKeyPress(key, scancode, action, mods);
        });
    }
}

// Window input events

namespace gp {
    bool Window::isMouseHovering() const {
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_HOVERED);
    }

    bool Window::checkShiftKey() const {
        return m_KeyModifiers & (1 << 0);
    }

    bool Window::checkControlKey() const {
        return m_KeyModifiers & (1 << 1);
    }

    bool Window::checkAltKey() const {
        return m_KeyModifiers & (1 << 2);
    }

    bool Window::checkSuperKey() const {
        return m_KeyModifiers & (1 << 3);
    }

    int Window::checkKey(int key) const {
        return glfwGetKey(m_Window, key);
    }
}

// Window private methods
namespace gp {
    bool Window::_isClosed() const {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::_update() const {
        glfwMakeContextCurrent(m_Window);
        glfwSwapBuffers(m_Window);
    }

    void Window::_destroy() const {
        GP_CORE_TRACE("_destroy() '{0}'", m_Data.title);
        glfwDestroyWindow(m_Window);
    }

    void Window::_fullscreen() const {
        if (!isFullscreen()) {
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }

    void Window::_unfullscreen(int width, int height, int xPos, int yPos) const {
        glfwSetWindowMonitor(m_Window, nullptr, xPos, yPos, width, height, 0);
    }

    void Window::_restore() const {
        glfwRestoreWindow(m_Window);
    }

    void Window::_maximize() const {
        glfwMaximizeWindow(m_Window);
    }

    void Window::_minimize() const {
        glfwIconifyWindow(m_Window);
    }

    void Window::_show() const {
        glfwShowWindow(m_Window);
    }

    void Window::_hide() const {
        glfwHideWindow(m_Window);
    }

    void Window::_focus() const {
        glfwFocusWindow(m_Window);
    }
}

// Window private update methods
namespace gp {
    void Window::_updateSize() const {
        glfwSetWindowSize(m_Window, m_Data.width, m_Data.height);
    }

    void Window::_updateTitle() const {
        glfwSetWindowTitle(m_Window, m_Data.title);
    }

    void Window::_updatePosition() const {
        glfwSetWindowPos(m_Window, m_Data.xPos, m_Data.yPos);
    }

    void Window::_updateBackground() const {
        glClearColor(m_Data.background.getRedf(),
                     m_Data.background.getGreenf(),
                     m_Data.background.getBluef(), 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::_updateSizeLimits() const {
        glfwSetWindowSizeLimits(m_Window, m_Data.minWidth, m_Data.minHeight,
                                m_Data.maxWidth, m_Data.maxHeight);
    }

    void Window::_updateAspectRatio(int numerator, int denominator) const {
        glfwSetWindowAspectRatio(m_Window, numerator, denominator);
    }
}

#endif
