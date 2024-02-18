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

    Window::Window(int width, int height, const char *title)
        : RenderingManager(*this, width, height, title),

          m_xPos(50),
          m_yPos(50),

          m_WindowedWidth(m_Width),
          m_WindowedHeight(m_Height),
          m_WindowedXPos(m_xPos),
          m_WindowedYPos(m_yPos) {
        GP_CORE_INFO("gp::Window::Window({0}, {1} '{2}')", m_Width, m_Height, m_Title);

        GP_CHECK_GT(width, 0, "Window width must be greater than 0");
        GP_CHECK_GT(height, 0, "Window height must be greater than 0");

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(m_Width,
                                    m_Height,
                                    m_Title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, this);

#if GP_USING_GLAD
        GP_CORE_DEBUG("gp::Window::Window() initialising GLAD");
#if GP_USING_GLFW
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            GP_RUNTIME_ERROR("gp::Window::Window() failed to initialize GLAD");
        }
#else
        if (!gladLoadGL()) {
            GP_RUNTIME_ERROR("gp::Window::Window() failed to initialize GLAD");
        }
#endif
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

        s_Instances.erase(std::remove(s_Instances.begin(), s_Instances.end(), this), s_Instances.end());
    }

    void Window::super() {
        GP_CORE_DEBUG("gp::Window::super() - '{0}'", m_Title);

        init();

        _updatePosition();
        _updateSizeLimits();

        setResizeCallback(nullptr);
        setPositionCallback(nullptr);
        _setKeyCallback();
        _setMouseButtonCallback();
    }

    GLFWwindow *Window::getWindowGLFW() {
        GP_CORE_TRACE("gp::Window::getWindowGLFW() - '{0}'", m_Title);
        return m_Window;
    }

    std::string Window::toString() {
        if (m_IsDestroyed) {
            return {"Destroyed Window()"};
        }
        return strformat("Window(%i, %i, '%s')", m_Width, m_Height, m_Title);
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
        _swapBuffers();
    }

    void Window::destroy() {
        GP_CORE_INFO("gp::Window::destroy() - '{0}'", m_Title);

        if (!m_IsDestroyed) {
            _destroy();
            m_IsDestroyed = true;
            _onDestroy();
        }
    }
}

// Window getters & setters
namespace gp {
    void Window::setTitle(const char *value) {
        GP_CORE_DEBUG("gp::setTitle({1}) - '{0}'", m_Title, value);

        m_Title = value;
        glfwSetWindowTitle(m_Window, m_Title);
    }

    const char *Window::getTitle() const {
        GP_CORE_TRACE("gp::Window::getTitle() - '{0}'", m_Title);
        return m_Title;
    }

    void Window::setXPos(int value) {
        GP_CORE_DEBUG("gp::Window::setXPos({1}) - '{0}'", m_Title, value);

        m_xPos = value;
        _updatePosition();
    }

    int Window::getXPos() const {
        GP_CORE_TRACE("gp::Window::getXPos() - '{0}'", m_Title);
        return m_xPos;
    }

    void Window::setYPos(int value) {
        GP_CORE_DEBUG("gp::Window::setYPos({1}) - '{0}'", m_Title, value);

        m_yPos = value;
        _updatePosition();
    }

    int Window::getYPos() const {
        GP_CORE_TRACE("gp::Window::getYPos() - '{0}'", m_Title);
        return m_yPos;
    }

    void Window::setMinWidth(int value) {
        GP_CORE_DEBUG("gp::Window::setMinWidth({1}) - '{0}'", m_Title, value);

        GP_CHECK_GE(value, 0, "Window minimum width must be greater than or equal to 0");

        m_MinWidth = value;
        _updateSizeLimits();
    }

    int Window::getMinWidth() const {
        GP_CORE_TRACE("gp::Window::getMinWidth() - '{0}'", m_Title);
        return m_MinWidth;
    }

    void Window::setMinHeight(int value) {
        GP_CORE_DEBUG("gp::Window::setMinHeight({1}) - '{0}'", m_Title, value);

        GP_CHECK_GE(value, 0, "Window minimum height must be greater than or equal to 0");

        m_MinHeight = value;
        _updateSizeLimits();
    }

    int Window::getMinHeight() const {
        GP_CORE_TRACE("gp::Window::getMinHeight() - '{0}'", m_Title);
        return m_MinHeight;
    }

    void Window::setMaxWidth(int value) {
        GP_CORE_DEBUG("gp::Window::setMaxWidth({1}) - '{0}'", m_Title, value);

        GP_CHECK_GE(value, m_MinWidth, "Window maximum width must be greater than or equal to its minimum width");

        m_MaxWidth = value;
        _updateSizeLimits();
    }

    int Window::getMaxWidth() const {
        GP_CORE_TRACE("gp::Window::getMaxWidth() - '{0}'", m_Title);
        return m_MaxWidth;
    }

    void Window::setMaxHeight(int value) {
        GP_CORE_DEBUG("gp::Window::setMaxHeight({1}) - '{0}'", m_Title, value);

        GP_CHECK_GE(value, m_MinHeight, "Window maximum height must be greater than or equal to its minimum height");

        m_MaxHeight = value;
        _updateSizeLimits();
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
    // Size
    void Window::setSize(int width, int height) {
        GP_CORE_DEBUG("gp::Window::setSize({1}, {2}) - '{0}'", m_Title, width, height);

        GP_CHECK_GT(width, 0, "Window width must be greater than 0");
        GP_CHECK_GT(height, 0, "Window height must be greater than 0");

        m_Width = width;
        m_Height = height;

        _updateSize();
    }

    // Size Limits
    void Window::setSizeLimits(int minWidth, int minHeight, int maxWidth,
                               int maxHeight) {
        GP_CORE_DEBUG("gp::Window::setSizeLimits({1}, {2}, {3}, {4}) - '{0}'",
                      m_Title, minWidth, minHeight, maxWidth, maxHeight);

        GP_CHECK_GE(minWidth, 0, "Window minimum width must be greater than or equal to 0");
        GP_CHECK_GE(minHeight, 0, "Window minimum height must be greater than or equal to 0");
        GP_CHECK_GE(maxWidth, minWidth, "Window maximum width must be greater than or equal to its minimum width");
        GP_CHECK_GE(maxHeight, minHeight, "Window maximum height must be greater than or equal to its minimum height");

        m_MinWidth = minWidth;
        m_MinHeight = minHeight;
        m_MaxWidth = maxWidth;
        m_MaxHeight = maxHeight;

        _updateSizeLimits();
    }

    void Window::setMinSize(int minWidth, int minHeight) {
        GP_CORE_DEBUG("gp::Window::setMinSize({1}, {2}) - '{0}'", m_Title, minWidth, minHeight);

        GP_CHECK_GE(minWidth, 0, "Window minimum width must be greater than or equal to 0");
        GP_CHECK_GE(minHeight, 0, "Window minimum height must be greater than or equal to 0");

        m_MinWidth = minWidth;
        m_MinHeight = minHeight;

        _updateSizeLimits();
    }

    void Window::setMaxSize(int maxWidth, int maxHeight) {
        GP_CORE_DEBUG("gp::Window::setMaxSize({1}, {2}) - '{0}'", m_Title, maxWidth, maxHeight);

        GP_CHECK_GE(maxWidth, m_MinWidth,
                    "Window maximum width must be greater than or equal to its minimum width");
        GP_CHECK_GE(maxHeight, m_MinHeight,
                    "Window maximum height must be greater than or equal to its minimum height");

        m_MaxWidth = maxWidth;
        m_MaxHeight = maxHeight;

        _updateSizeLimits();
    }

    // Position
    void Window::setPosition(int xPos, int yPos) {
        GP_CORE_DEBUG("gp::Window::setPosition({1}, {2}) - '{0}'", m_Title, xPos, yPos);

        m_xPos = xPos;
        m_yPos = yPos;

        _updatePosition();
    }

    // Aspect Ratio
    void Window::setAspectRatio(int numerator, int denominator) {
        GP_CORE_DEBUG("gp::Window::setAspectRatio({1}, {2}) - '{0}'", m_Title, numerator, denominator);

        if (numerator == -1 or denominator == -1) {
            _updateAspectRatio(-1, -1);
            return;
        }

        GP_CHECK_GT(numerator, 0, "Aspect ratio numerator must be greater than 0");
        GP_CHECK_GT(denominator, 0, "Aspect ratio denominator must be greater than 0");

        const int g = gcd(numerator, denominator);
        _updateAspectRatio(numerator / g, denominator / g);
    }

    AspectRatio Window::getAspectRatio() const {
        GP_CORE_TRACE("gp::Window::getAspectRatio() - '{0}'", m_Title);

        const int g = gcd(m_Width, m_Height);
        return AspectRatio{m_Width / g, m_Height / g};
    }
}

// Window state methods
namespace gp {
    void Window::restore() {
        GP_CORE_INFO("gp::Window::restore() - '{0}'", m_Title);

        if (isFullscreen()) {
            _unfullscreen(m_WindowedWidth, m_WindowedHeight, m_WindowedXPos, m_WindowedYPos);
        }
        else {
            _restore();
        }
    }

    void Window::fullscreen() {
        GP_CORE_DEBUG("gp::Window::fullscreen() - '{0}'", m_Title);

        m_WindowedWidth = m_Width;
        m_WindowedHeight = m_Height;
        m_WindowedXPos = m_xPos;
        m_WindowedYPos = m_yPos;

        if (!isFullscreen()) {
            _fullscreen();
        }
    }

    bool Window::isFullscreen() const {
        GP_CORE_TRACE("gp::Window::isFullscreen() - '{0}'", m_Title);
        return (bool) glfwGetWindowMonitor(m_Window);
    }

    void Window::minimize() {
        GP_CORE_INFO("gp::Window::minimize() - '{0}'", m_Title);
        glfwIconifyWindow(m_Window);
    }

    bool Window::isMinimized() const {
        GP_CORE_TRACE("gp::Window::isMinimized() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED);
    }

    void Window::maximize() {
        GP_CORE_INFO("gp::Window::maximize() - '{0}'", m_Title);
        glfwMaximizeWindow(m_Window);
    }

    bool Window::isMaximized() const {
        GP_CORE_TRACE("gp::Window::isMaximized() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED);
    }

    void Window::hide(bool hide) {
        GP_CORE_INFO("gp::Window::hide() - '{0}'", m_Title);
        if (hide) {
            glfwHideWindow(m_Window);
        }
        else {
            glfwShowWindow(m_Window);
        }
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

// Window events
namespace gp {
    bool Window::isMouseHovering() const {
        GP_CORE_TRACE("gp::Window::isMouseHovering() - '{0}'", m_Title);
        return (bool) glfwGetWindowAttrib(m_Window, GLFW_HOVERED);
    }

    Point Window::getMousePosition() const {
        GP_CORE_TRACE("gp::Window::getMousePosition() - '{0}'", m_Title);

        double xPos, yPos;
        glfwGetCursorPos(m_Window, &xPos, &yPos);
        return toWorld({(float) xPos, (float) yPos});
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

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onResize(width, height);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onClose();
        });
    }

    void Window::setPositionCallback(std::function<void(Window *, int, int)> callback) {
        GP_CORE_TRACE("gp::Window::setPositionCallback() - '{0}'", m_Title);

        m_PositionCallback = std::move(callback);

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow *window, int xPos, int yPos) {
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onMove(xPos, yPos);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onMinimize(iconified == GLFW_TRUE);
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

        // TODO fix issue with maximize callback not working. Tested on M1 macOS Monterey 12.4, 3.3.8 Cocoa NSGL EGL OSMesa dynamic, OpenGL 4.1
        glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow *window, int maximized) {
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onMaximize(maximized == GLFW_TRUE);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onFocus(focused == GLFW_TRUE);
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
            auto windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onRefreshRequired();
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onContentScale(xScale, yScale);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onFramebufferSize(width, height);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onMouseMotion((float) xPos, (float) yPos);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onMouseEnter((bool) entered);
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
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onScroll((float) xScroll, (float) yScroll);
        });
    }

    void Window::_setKeyCallback() const {
        GP_CORE_DEBUG("gp::Window::_setKeyCallback() - '{0}'", m_Title);

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onKeyPress(key, scancode, action, mods);
        });
    }

    void Window::_setMouseButtonCallback() const {
        GP_CORE_DEBUG("gp::Window::_setMouseButtonCallback() - '{0}'", m_Title);

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            auto *windowObject = (Window *) glfwGetWindowUserPointer(window);
            windowObject->_onMousePress(button, action, mods);
        });
    }
}

// Window callbacks
namespace gp {
    void Window::setDestroyCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("gp::Window::setDestroyCallback() - '{0}'", m_Title);

        m_DestroyCallback = std::move(callback);
    }

    void Window::_onResize(int width, int height) {
        GP_CORE_TRACE_ALL("gp::Window::on({1}, {2}) - '{0}'", m_Title, width, height);

        m_Width = width;
        m_Height = height;

        if (m_ResizeCallback) {
            m_ResizeCallback((Window *) this, width, height);
        }

        update();
    }

    void Window::_onClose() {
        GP_CORE_DEBUG("gp::Window::_onClose() - '{0}'", m_Title);
        m_CloseCallback((Window *) this);
    }

    void Window::_onDestroy() {
        GP_CORE_DEBUG("gp::Window::_onDestroy() - '{0}'", m_Title);
        if (m_DestroyCallback) {
            m_DestroyCallback((Window *) this);
        }
    }

    void Window::_onMove(int xPos, int yPos) {
        GP_CORE_TRACE_ALL("gp::Window::_onMove({1}, {2}) - '{0}'", m_Title, xPos, yPos);

        m_xPos = xPos;
        m_yPos = yPos;

        if (m_PositionCallback) {
            m_PositionCallback((Window *) this, xPos, yPos);
        }
    }

    void Window::_onMinimize(bool iconified) {
        GP_CORE_DEBUG("gp::Window::_onMinimize() - '{0}'", m_Title);
        m_MinimizeCallback((Window *) this, iconified);
    }

    void Window::_onMaximize(bool maximized) {
        GP_CORE_DEBUG("gp::Window::_onMaximize() - '{0}'", m_Title);
        m_MaximizeCallback((Window *) this, maximized);
    }

    void Window::_onFocus(bool focused) {
        GP_CORE_DEBUG("gp::Window::_onFocus() - '{0}'", m_Title);
        m_FocusedCallback((Window *) this, focused);
    }

    void Window::_onRefreshRequired() {
        GP_CORE_TRACE_ALL("gp::Window::_onRefreshRequired() - '{0}'", m_Title);
        m_RefreshCallback((Window *) this);
    }

    void Window::_onContentScale(float xScale, float yScale) {
        GP_CORE_TRACE_ALL("gp::Window::_onContentScale({1}, {2}) - '{0}'", m_Title, xScale, yScale);
        m_ContentScaleCallback((Window *) this, xScale, yScale);
    }

    void Window::_onFramebufferSize(int width, int height) {
        GP_CORE_TRACE_ALL("gp::Window::_onFramebufferSize({1}, {2}) - '{0}'", m_Title, width, height);
        m_FramebufferSizeCallback((Window *) this, width, height);
    }

    void Window::_onMouseMotion(float xPos, float yPos) {
        GP_CORE_TRACE_ALL("gp::Window::_onMouseMotion({1}, {2}) - '{0}'", m_Title, xPos, yPos);
        m_MouseMotionCallback((Window *) this, xPos, yPos);
    }

    void Window::_onMouseEnter(bool entered) {
        GP_CORE_TRACE_ALL("gp::Window::_onMouseEnter({1}) - '{0}'", m_Title, entered);
        m_MouseEnterCallback((Window *) this, entered);
    }

    void Window::_onScroll(float xScroll, float yScroll) {
        GP_CORE_TRACE_ALL("gp::Window::_onScroll({1}, {2}) - '{0}'", m_Title, xScroll, yScroll);
        m_ScrollCallback((Window *) this, xScroll, yScroll);
    }

    void Window::_onKeyPress(int key, [[maybe_unused]] int scancode, int action, int mods) {
        GP_CORE_TRACE_ALL("gp::Window::_onKeyPress({1}, {2}, {3}, {4}) - '{0}'", m_Title, key, scancode, action, mods);

        m_KeyModifiers = mods;
        if (m_KeyCallbacks.contains(key)) {
            m_KeyCallbacks[key](this, action);
        }
    }

    void Window::setKeyCallback(int key, std::function<void(Window *window, int action)> callback) {
        GP_CORE_DEBUG("gp::Window::setKeyCallback({1}) - '{0}'", m_Title, key);

        if (callback) {
            m_KeyCallbacks[key] = std::move(callback);
        }
        else if (m_KeyCallbacks.contains(key)) {
            m_KeyCallbacks.erase(key);
        }
        // _setKeyCallback(); // Not required as it is already set in super()
    }

    void Window::_onMousePress(int button, int action, int mods) {
        GP_CORE_TRACE_ALL("gp::Window::_onMousePress({1}, {2}, {3}) - '{0}'", m_Title, button, action, mods);

        m_KeyModifiers = mods;
        if (m_MouseCallbacks.contains(button)) {
            m_MouseCallbacks[button]((Window *) this, (bool) action);
        }
    }

    void Window::setMouseButtonCallback(int button, std::function<void(Window *window, bool pressed)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseButtonCallback({1}) - '{0}'", m_Title, button);

        if (callback) {
            m_MouseCallbacks[button] = std::move(callback);
        }
        else if (m_MouseCallbacks.contains(button)) {
            m_MouseCallbacks.erase(button);
        }
        // _setMouseButtonCallback(); // Not required as it is already set in super()
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

    void Window::_updateSizeLimits() const {
        GP_CORE_TRACE("gp::Window::_updateSizeLimits({1}, {2}, {3}, {4}) - '{0}'", m_Title,
                      m_MinWidth, m_MinHeight, m_MaxWidth, m_MaxHeight);
        glfwSetWindowSizeLimits(m_Window, m_MinWidth, m_MinHeight,
                                m_MaxWidth == INT_MAX ? GLFW_DONT_CARE : m_MaxWidth,
                                m_MaxHeight == INT_MAX ? GLFW_DONT_CARE : m_MaxHeight);
    }

    void Window::_updateAspectRatio(int numerator, int denominator) const {
        GP_CORE_TRACE("gp::Window::_updateAspectRatio() - '{0}'", m_Title);
        glfwSetWindowAspectRatio(m_Window, numerator, denominator);
    }

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
