#define GP_LOGGING_LEVEL 3

#include "Window.h"
#include "MouseCodes.h"
#include "debug/Error.h"

#include <opengl.h>

// TODO check_key should return an int. 0 is released, 1 is pressed, 2 is repeat. (v2.0.x)
// This would involve maintaining an unordered map of key codes to the key state
// Inside GLFW's key callback, this map would be updated

namespace gp {
    std::vector<Window *> Window::s_Instances;

    Window::Window(const int width, const int height, const std::string &title)
            : RenderingManager{width, height, title},
              m_xPos{50},
              m_yPos{50},
              m_WindowedWidth{m_Width},
              m_WindowedHeight{m_Height},
              m_WindowedXPos{m_xPos},
              m_WindowedYPos{m_yPos} {
        GP_CORE_INFO("gp::Window::Window({0}, {1} '{2}')", m_Width, m_Height, m_Title);

        GP_CHECK_GT(width, 0, "Window width must be greater than 0");
        GP_CHECK_GT(height, 0, "Window height must be greater than 0");

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, this);

        #if GP_USING_GLAD
        GP_CORE_DEBUG("gp::Window::Window() initialising GLAD");
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            GP_RUNTIME_ERROR("gp::Window::Window() failed to initialize GLAD");
        }
        #endif

        super();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GEQUAL);

        glClearDepth(0);

        s_Instances.push_back(this);
    }

    Window::~Window() {
        GP_CORE_INFO("gp::Window::~Window() - '{0}'", m_Title);

        destroy();
        std::erase(s_Instances, this);
    }

    void Window::super() {
        GP_CORE_DEBUG("gp::Window::super() - '{0}'", m_Title);

        init();

        setPosition(m_xPos, m_yPos);
        setSizeLimits(m_MinWidth, m_MinHeight, m_MaxWidth, m_MaxHeight);

        setResizeCallback(nullptr);
        setPositionCallback(nullptr);

        glfwSetMouseButtonCallback(
                m_Window,
                [](GLFWwindow *window, const int button, const int action, const int mods) {
                    auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
                    windowObject->_onMousePress(button, action, mods);
                });

        glfwSetKeyCallback(
                m_Window,
                [](GLFWwindow *window, const int key, const int scancode, const int action,
                   const int mods) {
                    auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
                    windowObject->_onKeyPress(key, scancode, action, mods);
                });
    }

    GLFWwindow *Window::getWindowGLFW() const {
        GP_CORE_TRACE("gp::Window::getWindowGLFW() - '{0}'", m_Title);
        return m_Window;
    }

    std::string Window::toString() const {
        if (m_IsDestroyed) {
            return {"Destroyed Window()"};
        }
        return strformat("Window(%i, %i, '%s')", m_Width, m_Height, m_Title.c_str());
    }

    bool Window::isOpen() const {
        GP_CORE_TRACE_ALL("gp::Window::isOpen() - '{0}'", m_Title);
        return !isClosed();
    }

    bool Window::isClosed() const {
        GP_CORE_TRACE_ALL("gp::Window::isClosed() - '{0}'", m_Title);
        return m_IsDestroyed or glfwWindowShouldClose(m_Window);
    }

    bool Window::isDestroyed() const {
        GP_CORE_TRACE("gp::Window::isDestroyed() - '{0}'", m_Title);
        return m_IsDestroyed;
    }

    void Window::update() {
        GP_CORE_TRACE_ALL("gp::Window::update() - '{0}'", m_Title);

        glfwMakeContextCurrent(m_Window);

        render();
        glfwSwapBuffers(m_Window);
    }

    void Window::destroy() {
        GP_CORE_INFO("gp::Window::destroy() - '{0}'", m_Title);

        if (!m_IsDestroyed) {
            glfwDestroyWindow(m_Window);
            m_IsDestroyed = true;

            if (m_DestroyCallback) {
                m_DestroyCallback(this);
            }
        }
    }
}

// Window getters & setters
namespace gp {
    void Window::setWidth(const int value) {
        GP_CORE_DEBUG("gp::Window::setWidth({1}) - '{0}'", m_Title, value);
        setSize(value, m_Height);
    }

    int Window::getWidth() const {
        GP_CORE_TRACE("gp::Window::getWidth() - '{0}'", m_Title);
        return m_Width;
    }

    void Window::setHeight(const int value) {
        GP_CORE_DEBUG("gp::Window::setHeight({1}) - '{0}'", m_Title, value);
        setSize(m_Width, value);
    }

    int Window::getHeight() const {
        GP_CORE_TRACE("gp::Window::getHeight() - '{0}'", m_Title);
        return m_Height;
    }

    void Window::setTitle(const std::string &value) {
        GP_CORE_DEBUG("gp::setTitle({1}) - '{0}'", m_Title, value);

        m_Title = value;
        glfwSetWindowTitle(m_Window, m_Title.c_str());
    }

    std::string Window::getTitle() const {
        GP_CORE_TRACE("gp::Window::getTitle() - '{0}'", m_Title);
        return m_Title;
    }

    void Window::setXPos(const int value) {
        GP_CORE_DEBUG("gp::Window::setXPos({1}) - '{0}'", m_Title, value);
        setPosition(value, m_yPos);
    }

    int Window::getXPos() const {
        GP_CORE_TRACE("gp::Window::getXPos() - '{0}'", m_Title);
        return m_xPos;
    }

    void Window::setYPos(const int value) {
        GP_CORE_DEBUG("gp::Window::setYPos({1}) - '{0}'", m_Title, value);
        setPosition(m_xPos, value);
    }

    int Window::getYPos() const {
        GP_CORE_TRACE("gp::Window::getYPos() - '{0}'", m_Title);
        return m_yPos;
    }

    void Window::setMinWidth(const int value) {
        GP_CORE_DEBUG("gp::Window::setMinWidth({1}) - '{0}'", m_Title, value);
        setMinSize(value, m_MinHeight);
    }

    int Window::getMinWidth() const {
        GP_CORE_TRACE("gp::Window::getMinWidth() - '{0}'", m_Title);
        return m_MinWidth;
    }

    void Window::setMinHeight(const int value) {
        GP_CORE_DEBUG("gp::Window::setMinHeight({1}) - '{0}'", m_Title, value);
        setMinSize(m_MinHeight, value);
    }

    int Window::getMinHeight() const {
        GP_CORE_TRACE("gp::Window::getMinHeight() - '{0}'", m_Title);
        return m_MinHeight;
    }

    void Window::setMaxWidth(const int value) {
        GP_CORE_DEBUG("gp::Window::setMaxWidth({1}) - '{0}'", m_Title, value);
        setMaxSize(value, m_MaxHeight);
    }

    int Window::getMaxWidth() const {
        GP_CORE_TRACE("gp::Window::getMaxWidth() - '{0}'", m_Title);
        return m_MaxWidth;
    }

    void Window::setMaxHeight(const int value) {
        GP_CORE_DEBUG("gp::Window::setMaxHeight({1}) - '{0}'", m_Title, value);
        setMaxSize(m_MaxWidth, value);
    }

    int Window::getMaxHeight() const {
        GP_CORE_TRACE("gp::Window::getMaxHeight() - '{0}'", m_Title);
        return m_MaxHeight;
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

// Window Get & Set methods
namespace gp {
    void Window::setSize(const int width, const int height) {
        GP_CORE_DEBUG("gp::Window::setSize({1}, {2}) - '{0}'", m_Title, width, height);

        GP_CHECK_GT(width, 0, "Window width must be greater than 0");
        GP_CHECK_GT(height, 0, "Window height must be greater than 0");

        m_Width = width;
        m_Height = height;

        glfwSetWindowSize(m_Window, m_Width, m_Height);
    }

    void Window::setSizeLimits(const int minWidth, const int minHeight, const int maxWidth, const int maxHeight) {
        GP_CORE_DEBUG("gp::Window::setSizeLimits({1}, {2}, {3}, {4}) - '{0}'",
                      m_Title, minWidth, minHeight, maxWidth, maxHeight);

        if (minWidth != GLFW_DONT_CARE) {
            GP_CHECK_GE(minWidth, 0, "Window minimum width must be greater than or equal to 0");
        }
        if (minHeight != GLFW_DONT_CARE) {
            GP_CHECK_GE(minHeight, 0, "Window minimum height must be greater than or equal to 0");
        }
        if (maxWidth != GLFW_DONT_CARE) {
            GP_CHECK_GE(maxWidth, minWidth, "Window maximum width must be greater than or equal to minimum width");
        }
        if (maxHeight != GLFW_DONT_CARE) {
            GP_CHECK_GE(maxHeight, minHeight, "Window maximum height must be greater than or equal to minimum height");
        }

        m_MinWidth = minWidth == GLFW_DONT_CARE ? 0 : minWidth;
        m_MinHeight = minHeight == GLFW_DONT_CARE ? 0 : minHeight;
        m_MaxWidth = maxWidth == GLFW_DONT_CARE ? INT_MAX : maxWidth;
        m_MaxHeight = maxHeight == GLFW_DONT_CARE ? INT_MAX : maxHeight;

        glfwSetWindowSizeLimits(m_Window, m_MinWidth, m_MinHeight, m_MaxWidth, m_MaxHeight);
    }

    void Window::setMinSize(const int minWidth, const int minHeight) {
        GP_CORE_DEBUG("gp::Window::setMinSize({1}, {2}) - '{0}'", m_Title, minWidth, minHeight);
        setSizeLimits(minWidth, minHeight, m_MaxWidth, m_MaxHeight);
    }

    void Window::setMaxSize(const int maxWidth, const int maxHeight) {
        GP_CORE_DEBUG("gp::Window::setMaxSize({1}, {2}) - '{0}'", m_Title, maxWidth, maxHeight);
        setSizeLimits(m_MinWidth, m_MinHeight, maxWidth, maxHeight);
    }

    void Window::setPosition(const int xPos, const int yPos) {
        GP_CORE_DEBUG("gp::Window::setPosition({1}, {2}) - '{0}'", m_Title, xPos, yPos);

        m_xPos = xPos;
        m_yPos = yPos;

        glfwSetWindowPos(m_Window, m_xPos, m_yPos);
    }

    Point Window::getPosition() const {
        return {m_xPos, m_yPos};
    }

    void Window::setAspectRatio(const int numerator, const int denominator) {
        GP_CORE_DEBUG("gp::Window::setAspectRatio({1}, {2}) - '{0}'", m_Title, numerator, denominator);

        if (numerator == -1 or denominator == -1) {
            glfwSetWindowAspectRatio(m_Window, -1, -1);
            return;
        }

        GP_CHECK_GT(numerator, 0, "Aspect ratio numerator must be greater than 0");
        GP_CHECK_GT(denominator, 0, "Aspect ratio denominator must be greater than 0");

        const int g = gcd(numerator, denominator);
        glfwSetWindowAspectRatio(m_Window, numerator / g, denominator / g);
        setSize(m_Width, (m_Width * denominator) / numerator);
    }

    AspectRatio Window::getAspectRatio() const {
        GP_CORE_TRACE("gp::Window::getAspectRatio() - '{0}'", m_Title);

        const int g = gcd(m_Width, m_Height);
        return AspectRatio{m_Width / g, m_Height / g};
    }
}

// Window state methods
namespace gp {
    void Window::restore() const {
        GP_CORE_INFO("gp::Window::restore() - '{0}'", m_Title);

        if (isFullscreen()) {
            glfwSetWindowMonitor(m_Window, nullptr,
                                 m_WindowedXPos, m_WindowedYPos, m_WindowedWidth, m_WindowedHeight, 0);
        } else {
            glfwRestoreWindow(m_Window);
        }
    }

    void Window::fullscreen() {
        GP_CORE_DEBUG("gp::Window::fullscreen() - '{0}'", m_Title);

        m_WindowedWidth = m_Width;
        m_WindowedHeight = m_Height;
        m_WindowedXPos = m_xPos;
        m_WindowedYPos = m_yPos;

        if (!isFullscreen()) {
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }

    bool Window::isFullscreen() const {
        GP_CORE_TRACE("gp::Window::isFullscreen() - '{0}'", m_Title);
        return static_cast<bool>(glfwGetWindowMonitor(m_Window));
    }

    void Window::minimize() const {
        GP_CORE_INFO("gp::Window::minimize() - '{0}'", m_Title);
        glfwIconifyWindow(m_Window);
    }

    bool Window::isMinimized() const {
        GP_CORE_TRACE("gp::Window::isMinimized() - '{0}'", m_Title);
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED));
    }

    void Window::maximize() const {
        GP_CORE_INFO("gp::Window::maximize() - '{0}'", m_Title);
        glfwMaximizeWindow(m_Window);
    }

    bool Window::isMaximized() const {
        GP_CORE_TRACE("gp::Window::isMaximized() - '{0}'", m_Title);
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED));
    }

    void Window::hide(const bool hide) const {
        GP_CORE_INFO("gp::Window::hide() - '{0}'", m_Title);
        if (hide) {
            glfwHideWindow(m_Window);
        } else {
            glfwShowWindow(m_Window);
        }
    }

    void Window::show() const {
        GP_CORE_INFO("gp::Window::show() - '{0}'", m_Title);
        glfwShowWindow(m_Window);
    }

    bool Window::isVisible() const {
        GP_CORE_TRACE("gp::Window::isVisible() - '{0}'", m_Title);
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_VISIBLE));
    }

    void Window::focus() const {
        GP_CORE_INFO("gp::Window::focus() - '{0}'", m_Title);
        glfwFocusWindow(m_Window);
    }

    bool Window::hasFocus() const {
        GP_CORE_TRACE("gp::Window::hasFocus() - '{0}'", m_Title);
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_FOCUSED));
    }

    void Window::requestAttention() const {
        GP_CORE_DEBUG("gp::Window::requestAttention() - '{0}'", m_Title);
        glfwRequestWindowAttention(m_Window);
    }
}


// Window attribute methods
namespace gp {
    bool Window::isResizable() const {
        GP_CORE_TRACE("gp::Window::isResizable() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_RESIZABLE);
    }

    void Window::setResizable(const bool value) const {
        GP_CORE_DEBUG("gp::Window::setResizable({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isDecorated() const {
        GP_CORE_TRACE("gp::Window::isDecorated() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_DECORATED);
    }

    void Window::setDecorated(const bool value) const {
        GP_CORE_DEBUG("gp::Window::setDecorated({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFloating() const {
        GP_CORE_TRACE("gp::Window::isFloating() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_FLOATING);
    }

    void Window::setFloating(const bool value) const {
        GP_CORE_DEBUG("gp::Window::setFloating({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FLOATING, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isAutoMinimized() const {
        GP_CORE_TRACE("gp::Window::isAutoMinimized() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY);
    }

    void Window::setAutoMinimized(const bool value) const {
        GP_CORE_DEBUG("gp::Window::setAutoMinimized({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, value ? GLFW_TRUE : GLFW_FALSE);
    }

    bool Window::isFocusedOnShow() const {
        GP_CORE_TRACE("gp::Window::isFocusedOnShow() - '{0}'", m_Title);
        return glfwGetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW);
    }

    void Window::setFocusedOnShow(const bool value) const {
        GP_CORE_DEBUG("gp::Window::setFocusedOnShow({1}) - '{0}'", m_Title, value);
        glfwSetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW, value ? GLFW_TRUE : GLFW_FALSE);
    }
}

// Window events
namespace gp {
    bool Window::isMouseHovering() const {
        GP_CORE_TRACE("gp::Window::isMouseHovering() - '{0}'", m_Title);
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_HOVERED));
    }

    Point Window::getMousePosition() const {
        GP_CORE_TRACE("gp::Window::getMousePosition() - '{0}'", m_Title);

        double xPos, yPos;
        glfwGetCursorPos(m_Window, &xPos, &yPos);
        return toWorld({static_cast<float>(xPos), static_cast<float>(yPos)});
    }

    void Window::setCursorMode(CursorMode mode) const {
        GP_CORE_DEBUG("gp::Window::setCursorMode({1}) - '{0}'", m_Title, static_cast<int>(mode));
        glfwSetInputMode(m_Window, GLFW_CURSOR, static_cast<int>(mode));
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

    int Window::checkKey(const int key) const {
        GP_CORE_TRACE("gp::Window::checkKey({1}) - '{0}'", m_Title, key);
        return glfwGetKey(m_Window, key);
    }

    bool Window::checkMouseButton(const int button) const {
        GP_CORE_TRACE("gp::Window::checkMouseButton({1}) - '{0}'", m_Title, button);
        return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
    }

    bool Window::checkLeftClick() const {
        return checkMouseButton(GP_MOUSE_LEFT_BUTTON);
    }

    bool Window::checkMiddleClick() const {
        return checkMouseButton(GP_MOUSE_MIDDLE_BUTTON);
    }

    bool Window::checkRightClick() const {
        return checkMouseButton(GP_MOUSE_RIGHT_BUTTON);
    }
}

namespace gp {
    void Window::setResizeCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_DEBUG("gp::Window::setResizeCallback() - '{0}'", m_Title);

        m_ResizeCallback = std::move(callback);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, const int width, const int height) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->_onResize(width, height);
        });
    }

    void Window::setCloseCallback(std::function<void(Window *)> callback) {
        GP_CORE_DEBUG("gp::Window::setCloseCallback() - '{0}'", m_Title);

        m_CloseCallback = std::move(callback);

        if (!m_CloseCallback) {
            glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *) {
            });
            return;
        }

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_CloseCallback(windowObject);
        });
    }

    void Window::setPositionCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_TRACE("gp::Window::setPositionCallback() - '{0}'", m_Title);

        m_PositionCallback = std::move(callback);

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow *window, const int xPos, const int yPos) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->_onMove(xPos, yPos);
        });
    }

    void Window::setMinimizeCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setMinimizeCallback() - '{0}'", m_Title);

        m_MinimizeCallback = std::move(callback);

        if (!m_MinimizeCallback) {
            glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *, int) {
            });
            return;
        }

        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow *window, const int iconified) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_MinimizeCallback(windowObject, iconified == GLFW_TRUE);
        });
    }

    void Window::setMaximizeCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setMaximizeCallback() - '{0}'", m_Title);

        m_MaximizeCallback = std::move(callback);

        if (!m_MaximizeCallback) {
            glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *, int) {
            });
            return;
        }

        // TODO fix issue with maximize callback not working. Tested on M1 macOS Monterey 12.4, 3.3.8 Cocoa NSGL EGL OSMesa dynamic, OpenGL 4.1
        glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *window, const int maximized) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_MaximizeCallback(windowObject, maximized == GLFW_TRUE);
        });
    }

    void Window::setFocusCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setFocusCallback() - '{0}'", m_Title);

        m_FocusedCallback = std::move(callback);

        if (!m_FocusedCallback) {
            glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *, int) {
            });
            return;
        }

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow *window, const int focused) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_FocusedCallback(windowObject, focused == GLFW_TRUE);
        });
    }

    void Window::setRefreshCallback(std::function<void(Window *)> callback) {
        GP_CORE_DEBUG("gp::Window::setRefreshCallback() - '{0}'", m_Title);

        m_RefreshCallback = std::move(callback);

        if (!m_RefreshCallback) {
            glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow *) {
            });
            return;
        }

        glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow *window) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_RefreshCallback(windowObject);
        });
    }

    void Window::setContentScaleCallback(std::function<void(Window *, float, float)> callback) {
        GP_CORE_DEBUG("gp::Window::setContentScaleCallback() - '{0}'", m_Title);

        m_ContentScaleCallback = std::move(callback);

        if (!m_ContentScaleCallback) {
            glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow *, float, float) {
            });
            return;
        }

        glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow *window, const float xScale, const float yScale) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_ContentScaleCallback(windowObject, xScale, yScale);
        });
    }

    void Window::setFramebufferSizeCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_DEBUG("gp::Window::setFramebufferSizeCallback() - '{0}'", m_Title);

        m_FramebufferSizeCallback = std::move(callback);

        if (!m_FramebufferSizeCallback) {
            glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *, int, int) {
            });
            return;
        }

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *window, const int width, const int height) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_FramebufferSizeCallback(windowObject, width, height);
        });
    }

    void Window::setMouseMotionCallback(std::function<void(Window *, float, float)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseMotionCallback() - '{0}'", m_Title);

        m_MouseMotionCallback = std::move(callback);

        if (!m_MouseMotionCallback) {
            glfwSetCursorPosCallback(m_Window, [](GLFWwindow *, double, double) {
            });
            return;
        }

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, const double xPos, const double yPos) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_MouseMotionCallback(windowObject, static_cast<float>(xPos), static_cast<float>(yPos));
        });
    }

    void Window::setMouseEnterCallback(std::function<void(Window *, bool)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseEnterCallback() - '{0}'", m_Title);

        m_MouseEnterCallback = std::move(callback);

        if (!m_MouseEnterCallback) {
            glfwSetCursorEnterCallback(m_Window, [](GLFWwindow *, int) {
            });
            return;
        }

        glfwSetCursorEnterCallback(m_Window, [](GLFWwindow *window, const int entered) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_MouseEnterCallback(windowObject, entered == GL_TRUE);
        });
    }

    void Window::setScrollCallback(std::function<void(Window *, float, float)> callback) {
        GP_CORE_DEBUG("gp::Window::setScrollCallback() - '{0}'", m_Title);

        m_ScrollCallback = std::move(callback);

        if (!m_ScrollCallback) {
            glfwSetScrollCallback(m_Window, [](GLFWwindow *, double, double) {
            });
            return;
        }

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, const double xScroll, const double yScroll) {
            auto *windowObject = static_cast<Window *>(glfwGetWindowUserPointer(window));
            windowObject->m_ScrollCallback(windowObject, xScroll, yScroll);
        });
    }
}

// Window callbacks
namespace gp {
    void Window::setDestroyCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("gp::Window::setDestroyCallback() - '{0}'", m_Title);
        m_DestroyCallback = std::move(callback);
    }

    void Window::_onResize(const int width, const int height) {
        GP_CORE_TRACE_ALL("gp::Window::on({1}, {2}) - '{0}'", m_Title, width, height);

        m_Width = width;
        m_Height = height;

        if (m_ResizeCallback) {
            m_ResizeCallback(this, width, height);
        }

        update();
    }

    void Window::_onMove(const int xPos, const int yPos) {
        GP_CORE_TRACE_ALL("gp::Window::_onMove({1}, {2}) - '{0}'", m_Title, xPos, yPos);

        m_xPos = xPos;
        m_yPos = yPos;

        if (m_PositionCallback) {
            m_PositionCallback(this, xPos, yPos);
        }
    }

    void Window::_onKeyPress(const int key, int, const int action, const int mods) {
        GP_CORE_TRACE_ALL("gp::Window::_onKeyPress({1}, {2}, {3}, {4}) - '{0}'", m_Title, key, scancode, action, mods);

        m_KeyModifiers = mods;
        if (m_KeyCallbacks.contains(key)) {
            m_KeyCallbacks[key](this, action);
        }
    }

    void Window::setKeyCallback(const int key, std::function<void(Window *window, int action)> callback) {
        GP_CORE_DEBUG("gp::Window::setKeyCallback({1}) - '{0}'", m_Title, key);

        if (callback) {
            m_KeyCallbacks[key] = std::move(callback);
        } else if (m_KeyCallbacks.contains(key)) {
            m_KeyCallbacks.erase(key);
        }
    }

    void Window::_onMousePress(const int button, const int action, const int mods) {
        GP_CORE_TRACE_ALL("gp::Window::_onMousePress({1}, {2}, {3}) - '{0}'", m_Title, button, action, mods);

        m_KeyModifiers = mods;
        if (m_MouseCallbacks.contains(button)) {
            m_MouseCallbacks[button](this, static_cast<bool>(action));
        }
    }

    void Window::setMouseButtonCallback(const int button, std::function<void(Window *window, bool pressed)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseButtonCallback({1}) - '{0}'", m_Title, button);

        if (callback) {
            m_MouseCallbacks[button] = std::move(callback);
        } else if (m_MouseCallbacks.contains(button)) {
            m_MouseCallbacks.erase(button);
        }
    }

    void Window::setLeftClickCallback(std::function<void(Window *, bool)> callback) {
        setMouseButtonCallback(GP_MOUSE_LEFT_BUTTON, std::move(callback));
    }

    void Window::setMiddleClickCallback(std::function<void(Window *, bool)> callback) {
        setMouseButtonCallback(GP_MOUSE_MIDDLE_BUTTON, std::move(callback));
    }

    void Window::setRightClickCallback(std::function<void(Window *, bool)> callback) {
        setMouseButtonCallback(GP_MOUSE_RIGHT_BUTTON, std::move(callback));
    }
}


// Window static methods
namespace gp {
    void Window::updateAll() {
        GP_CORE_TRACE_ALL("gp::Window::updateAll()");

        for (Window *&instance: s_Instances) {
            instance->update();
        }
    }

    void Window::destroyAll() {
        GP_CORE_DEBUG("gp::Window::destroyAll()");
        for (Window *&instance: s_Instances) {
            instance->destroy();
        }
    }
}
