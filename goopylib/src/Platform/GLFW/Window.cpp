#include "pch.h"
#include "goopylib/Core/Window.h"

#if GP_USING_GLFW

namespace gp {
    Window::Window(const WindowConfig &config) : BaseWindow(config) {
        GP_WINDOW_INFO("Creating window '{0}' ({1}, {2})", config.title, config.width, config.height);

        m_Window = glfwCreateWindow((int) m_Data.width,
                                    (int) m_Data.height,
                                    m_Data.title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, this);

        super();
    }

    Window::~Window() {
        GP_WINDOW_INFO("Deallocating window '{0}'", m_Data.title);

        if (!m_isDestroyed) {
            destroy();
        }
    }
}


// Window attribute methods
namespace gp {
    bool Window::isResizable() const {
        return glfwGetWindowAttrib(m_Window, GLFW_RESIZABLE);
    }

    void Window::setResizable(bool value) {
        GP_WINDOW_TRACE("Set '{0}' resizable -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isDecorated() const {
        return glfwGetWindowAttrib(m_Window, GLFW_DECORATED);
    }

    void Window::setDecorated(bool value) {
        GP_WINDOW_TRACE("Set '{0}' decorated -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFloating() const {
        return glfwGetWindowAttrib(m_Window, GLFW_FLOATING);
    }

    void Window::setFloating(bool value) {
        GP_WINDOW_TRACE("Set '{0}' floating -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FLOATING, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isAutoMinimized() const {
        return glfwGetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY);
    }

    void Window::setAutoMinimized(bool value) {
        GP_WINDOW_TRACE("Set '{0}' auto minimized -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFocusedOnShow() const {
        return glfwGetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW);
    }

    void Window::setFocusedOnShow(bool value) {
        GP_WINDOW_TRACE("Set '{0}' focused on show -> {1}", m_Data.title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW, value ? GLFW_TRUE : GLFW_FALSE);
    }
}

// Window state methods
namespace gp {
    bool Window::isFullscreen() const {
        return glfwGetWindowMonitor(m_Window);
    }

    bool Window::isMaximized() const {
        return glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED);
    }

    bool Window::isMinimized() const {
        return glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED);
    }

    bool Window::isVisible() const {
        return glfwGetWindowAttrib(m_Window, GLFW_VISIBLE);
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
}

// Window private methods
namespace gp {
    bool Window::_isClosed() const {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::_update() const {
        glfwMakeContextCurrent(m_Window);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_Window);
    }

    void Window::_destroy() const {
        glfwDestroyWindow(m_Window);
    }

    void Window::_updateSize() const {
        glfwSetWindowSize(m_Window, (int) m_Data.width, (int) m_Data.height);
    }

    void Window::_updatePosition() const {
        glfwSetWindowPos(m_Window, m_Data.xPos, m_Data.yPos);
    }

    void Window::_updateTitle() const {
        glfwSetWindowTitle(m_Window, m_Data.title);
    }

    void Window::_updateSizeLimits() const {
        glfwSetWindowSizeLimits(m_Window, (int) m_Data.minWidth, (int) m_Data.minHeight,
                                (int) m_Data.maxWidth, (int) m_Data.maxHeight);
    }
}

#endif
