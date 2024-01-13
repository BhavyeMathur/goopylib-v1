#define GP_LOGGING_LEVEL 3

#include "src/goopylib/core/Window.h"

#include "src/platform/events/MouseCodes.h"

// TODO check_key should return an int. 0 is released, 1 is pressed, 2 is repeat. (v2.0.x)
// This would involve maintaining an unordered map of key codes to the key state
// Inside GLFW's key callback, this map would be updated

namespace gp {
    std::vector<Window *> Window::s_Instances;

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
    const char *Window::getTitle() const {
        GP_CORE_TRACE("gp::Window::getTitle() - '{0}'", m_Title);
        return m_Title;
    }

    // X Position
    void Window::setXPos(int value) {
        GP_CORE_DEBUG("gp::Window::setXPos({1}) - '{0}'", m_Title, value);

        m_xPos = value;
        _updatePosition();
    }

    int Window::getXPos() const {
        GP_CORE_TRACE("gp::Window::getXPos() - '{0}'", m_Title);
        return m_xPos;
    }

    // Y Position
    void Window::setYPos(int value) {
        GP_CORE_DEBUG("gp::Window::setYPos({1}) - '{0}'", m_Title, value);

        m_yPos = value;
        _updatePosition();
    }

    int Window::getYPos() const {
        GP_CORE_TRACE("gp::Window::getYPos() - '{0}'", m_Title);
        return m_yPos;
    }

    // Minimum Width
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

    // Minimum Height
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

    // Maximum Width
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

    // Maximum Height
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
}

// Window events
namespace gp {
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

    // Move
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

    // Key Press
    void Window::_onKeyPress(int key, [[maybe_unused]] int scancode, int action, int mods) {
        GP_CORE_TRACE_ALL("gp::Window::_onKeyPress({1}, {2}, {3}, {4}) - '{0}'", m_Title, key, scancode, action, mods);

        m_KeyModifiers = mods;
        if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks[key]((Window *) this, action);
        }
    }

    void Window::setKeyCallback(int key, std::function<void(Window *window, int action)> callback) {
        GP_CORE_DEBUG("gp::Window::setKeyCallback({1}) - '{0}'", m_Title, key);

        if (callback) {
            m_KeyCallbacks[key] = std::move(callback);
        }
        else if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks.erase(key);
        }
        // _setKeyCallback(); // Not required as it is already set in super()
    }

    // Mouse Button
    void Window::_onMousePress(int button, int action, int mods) {
        GP_CORE_TRACE_ALL("gp::Window::_onMousePress({1}, {2}, {3}) - '{0}'", m_Title, button, action, mods);

        m_KeyModifiers = mods;
        if (m_MouseCallbacks.find(button) != m_MouseCallbacks.end()) {
            m_MouseCallbacks[button]((Window *) this, (bool) action);
        }
    }

    void Window::setMouseButtonCallback(int button, std::function<void(Window *window, bool pressed)> callback) {
        GP_CORE_DEBUG("gp::Window::setMouseButtonCallback({1}) - '{0}'", m_Title, button);

        if (callback) {
            m_MouseCallbacks[button] = std::move(callback);
        }
        else if (m_MouseCallbacks.find(button) != m_MouseCallbacks.end()) {
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
