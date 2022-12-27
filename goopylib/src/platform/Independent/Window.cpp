#include "src/goopylib/core/Window.h"
#include "src/goopylib/events/MouseCodes.h"

#if !GP_LOG_WINDOW
#undef GP_LOGGING
#endif

#include "src/goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_WINDOW
#undef GP_VALUE_CHECKING
#endif

#include "src/goopylib/debug/Error.h"


namespace gp {
    std::vector<Window *> Window::s_Instances;

    void Window::super() {
        m_Renderer.init();

        _updatePosition();
        _updateSizeLimits();

        _setResizeCallback();
        _setPositionCallback();
        _setKeyCallback();
        _setMouseButtonCallback();
    }

    void Window::update() {
        GP_CORE_TRACE_ALL("gp::Window::update() - '{0}'", m_Title);

        _updateBackground();

        m_Renderer.flush();

        _update();
    }

    void Window::destroy() {
        GP_CORE_INFO("Destroying window '{0}'", m_Title);

        if (!m_IsDestroyed) {
            _destroy();
            m_IsDestroyed = true;
            onDestroy();
        }
    }
}

// Window getters & setters
namespace gp {
    // Width
    void Window::setWidth(int value) {
        GP_CORE_DEBUG("Set '{0}' width -> {1}", m_Title, value);

        m_Width = value;
        _updateSize();
    }

    int Window::getWidth() const {
        return m_Width;
    }

    // Height
    void Window::setHeight(int value) {
        GP_CORE_DEBUG("Set '{0}' height -> {1}", m_Title, value);

        m_Height = value;
        _updateSize();
    }

    int Window::getHeight() const {
        return m_Height;
    }

    // Title
    void Window::setTitle(const char *title) {
        GP_CORE_DEBUG("Set '{0}' title -> '{1}'", m_Title, title);

        m_Title = title;
        _updateTitle();
    }

    const char *Window::getTitle() const {
        return m_Title;
    }

    // X Position
    void Window::setXPos(int value) {
        GP_CORE_DEBUG("Set '{0}' x-position -> {1}", m_Title, value);

        m_xPos = value;
        _updatePosition();
    }

    int Window::getXPos() const {
        return m_xPos;
    }

    // Y Position
    void Window::setYPos(int value) {
        GP_CORE_DEBUG("Set '{0}' y-position -> {1}", m_Title, value);

        m_yPos = value;
        _updatePosition();
    }

    int Window::getYPos() const {
        return m_yPos;
    }

    // Minimum Width
    void Window::setMinimumWidth(int value) {
        GP_CORE_DEBUG("Set '{0}' minimum width -> {1}", m_Title, value);

        m_MinWidth = value;
        _updateSizeLimits();
    }

    int Window::getMinimumWidth() const {
        return m_MinWidth;
    }

    // Minimum Height
    void Window::setMinimumHeight(int value) {
        GP_CORE_DEBUG("Set '{0}' minimum height -> {1}", m_Title, value);

        m_MinHeight = value;
        _updateSizeLimits();
    }

    int Window::getMinimumHeight() const {
        return m_MinHeight;
    }

    // Maximum Width
    void Window::setMaximumWidth(int value) {
        GP_CORE_DEBUG("Set '{0}' maximum width -> {1}", m_Title, value);

        m_MaxWidth = value;
        _updateSizeLimits();
    }

    int Window::getMaximumWidth() const {
        return m_MaxWidth;
    }

    // Maximum Height
    void Window::setMaximumHeight(int value) {
        GP_CORE_DEBUG("Set '{0}' maximum height -> {1}", m_Title, value);

        m_MaxHeight = value;
        _updateSizeLimits();
    }

    int Window::getMaximumHeight() const {
        return m_MaxHeight;
    }

    void Window::setBackground(const Color &background) {
        GP_CORE_DEBUG("Set '{0}' background -> {1}", m_Title, background.toString());

        m_Background = background;
        _updateBackground();
    }

    Color &Window::getBackground() const {
        return const_cast<Color &>(m_Background);
    }
}

// Window get & set methods
namespace gp {
    Camera &Window::getCamera() {
        return m_Renderer.m_Camera;
    }

    Point Window::toWorld(Point p) {
        p.x /= (float) (m_Width >> 1);
        p.y /= (float) (m_Height >> 1);

        p.x -= 1;
        p.y = 1 - p.y;

        auto pos = m_Renderer.m_Camera.m_InverseProjectionViewMatrix * glm::vec4(p.x, p.y, 0, 1.0);

        return {pos.x, pos.y};
    }

    Point Window::toScreen(Point p) {
        auto pos = m_Renderer.m_Camera.m_ProjectionViewMatrix * glm::vec4(p.x, p.y, 0, 1.0);

        float halfWidth = (float) (m_Width >> 1);
        float halfHeight = (float) (m_Height >> 1);

        pos.x *= halfWidth;
        pos.x += halfWidth;

        pos.y *= halfHeight;
        pos.y = halfHeight - pos.y;

        return {pos.x, pos.y};
    }

    // Size
    void Window::setSize(int width, int height) {
        GP_CORE_DEBUG("Set '{0}' size -> ({1}, {2})", m_Title, width, height);

        m_Width = width;
        m_Height = height;

        _updateSize();
    }

    // Size Limits
    void Window::setSizeLimits(int minWidth, int minHeight, int maxWidth,
                               int maxHeight) {
        GP_CORE_DEBUG("Set '{0}' size limits -> ({1}, {2}), ({3}, {4})", m_Title, minWidth, minHeight, maxWidth,
                      maxHeight);

        m_MinWidth = minWidth;
        m_MinHeight = minHeight;
        m_MaxWidth = maxWidth;
        m_MaxHeight = maxHeight;

        _updateSizeLimits();
    }

    void Window::setMinimumSize(int minWidth, int minHeight) {
        GP_CORE_DEBUG("Set '{0}' minimum size -> ({1}, {2})", m_Title, minWidth, minHeight);

        m_MinWidth = minWidth;
        m_MinHeight = minHeight;

        _updateSizeLimits();
    }

    void Window::setMaximumSize(int maxWidth, int maxHeight) {
        GP_CORE_DEBUG("Set '{0}' maximum size -> ({1}, {2})", m_Title, maxWidth, maxHeight);

        m_MaxWidth = maxWidth;
        m_MaxHeight = maxHeight;

        _updateSizeLimits();
    }

    // Position
    void Window::setPosition(int xPos, int yPos) {
        GP_CORE_DEBUG("Set '{0}' position -> ({1}, {2})", m_Title, xPos, yPos);

        m_xPos = xPos;
        m_yPos = yPos;

        _updatePosition();
    }

    void Window::setAspectRatio(int numerator, int denominator) {
        int g = gcd(numerator, denominator);
        _updateAspectRatio(numerator / g, denominator / g);

    }

    AspectRatio Window::getAspectRatio() const {
        int g = gcd(m_Width, m_Height);
        return AspectRatio{m_Width / g, m_Height / g};
    }
}

// Window state methods
namespace gp {
    bool Window::isDestroyed() const {
        return m_IsDestroyed;
    }

    bool Window::isClosed() const {
        return _isClosed() or m_IsDestroyed;
    }

    bool Window::isOpen() const {
        return !isClosed();
    }

    void Window::restore() {
        if (isFullscreen()) {
            _unfullscreen(m_WindowedWidth, m_WindowedHeight, m_WindowedXPos, m_WindowedYPos);
        }
        else {
            _restore();
        }
    }

    void Window::fullscreen() {
        m_WindowedWidth = m_Width;
        m_WindowedHeight = m_Height;
        m_WindowedXPos = m_xPos;
        m_WindowedYPos = m_yPos;

        _fullscreen();
    }

    void Window::maximize() {
        _maximize();
    }

    void Window::minimize() {
        _minimize();
    }

    void Window::show() {
        _show();
    }

    void Window::hide() {
        _hide();
    }

    void Window::focus() {
        _focus();
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

    void Window::onKeyPress(int key, int UNUSED(scancode), int action, int mods) {
        m_KeyModifiers = mods;
        if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks[key]((Window *) this, action);
        }
    }

    void Window::onMousePress(int button, int action, int mods) {
        m_KeyModifiers = mods;
        if (m_MouseCallbacks.find(button) != m_MouseCallbacks.end()) {
            m_MouseCallbacks[button]((Window *) this, (bool) action);
        }
    }

    void Window::setKeyCallback(int key, std::function<void(Window *window, int action)> callback) {
        GP_CORE_DEBUG("Set '{0}' key ({1}) callback", m_Title, key);

        if (callback) {
            m_KeyCallbacks[key] = std::move(callback);
        }
        else if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks.erase(key);
        }
        // _setKeyCallback(); // Not required as it is already set in super()
    }

    void Window::setMouseButtonCallback(int button, std::function<void(Window *window, bool pressed)> callback) {
        GP_CORE_DEBUG("Set '{0}' button ({1}) callback", m_Title, button);

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

// Window callbacks
namespace gp {
    // Resize
    void Window::onResize(int width, int height) {
        m_Width = width;
        m_Height = height;

        if (m_ResizeCallback) {
            m_ResizeCallback((Window *) this, width, height);
        }

        update();
    }

    void Window::setResizeCallback(std::function<void(Window *, int width, int height)> callback) {
        GP_CORE_DEBUG("Set '{0}' resize callback", m_Title);

        m_ResizeCallback = std::move(callback);
        // _setResizeCallback(); // Not required as it is already set in super()
    }

    // Close
    void Window::onClose() {
        GP_CORE_DEBUG("OnClose()");
        m_CloseCallback((Window *) this);
    }

    void Window::setCloseCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("Set '{0}' close callback", m_Title);

        m_CloseCallback = std::move(callback);
        _setCloseCallback();
    }

    // Destroy
    void Window::onDestroy() {
        GP_CORE_DEBUG("OnDestroy()");
        if (m_DestroyCallback) {
            m_DestroyCallback((Window *) this);
        }
    }

    void Window::setDestroyCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("Set '{0}' destroy callback", m_Title);

        m_DestroyCallback = std::move(callback);
    }

    // Move
    void Window::onMove(int xPos, int yPos) {
        m_xPos = xPos;
        m_yPos = yPos;

        if (m_PositionCallback) {
            m_PositionCallback((Window *) this, xPos, yPos);
        }
    }

    void Window::setPositionCallback(std::function<void(Window *window, int xPos, int yPos)> callback) {
        GP_CORE_DEBUG("Set '{0}' position callback", m_Title);

        m_PositionCallback = std::move(callback);
        // _setPositionCallback(); // Not required as it is already set in super()
    }

    // Minimize
    void Window::onMinimize(bool iconified) {
        GP_CORE_DEBUG("OnMinimize()");
        m_MinimizeCallback((Window *) this, iconified);
    }

    void Window::setMinimizeCallback(std::function<void(Window *window, bool minimized)> callback) {
        GP_CORE_DEBUG("Set '{0}' minimize callback", m_Title);

        m_MinimizeCallback = std::move(callback);
        _setMinimizeCallback();
    }

    // Maximize
    void Window::onMaximize(bool maximized) {
        GP_CORE_DEBUG("OnMaximize()");
        m_MaximizeCallback((Window *) this, maximized);
    }

    void Window::setMaximizeCallback(std::function<void(Window *window, bool maximized)> callback) {
        GP_CORE_DEBUG("Set '{0}' maximize callback", m_Title);

        m_MaximizeCallback = std::move(callback);
        _setMaximizeCallback();
    }

    // Focus
    void Window::onFocus(bool focused) {
        GP_CORE_DEBUG("OnFocus()");
        m_FocusedCallback((Window *) this, focused);
    }

    void Window::setFocusCallback(std::function<void(Window *window, bool focused)> callback) {
        GP_CORE_DEBUG("Set '{0}' focus callback", m_Title);

        m_FocusedCallback = std::move(callback);
        _setFocusedCallback();
    }

    // Refresh
    void Window::onRefreshRequired() {
        m_RefreshCallback((Window *) this);
    }

    void Window::setRefreshCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("Set '{0}' refresh required callback", m_Title);

        m_RefreshCallback = std::move(callback);
        _setRefreshCallback();
    }

    // Content Scale
    void Window::onContentScale(float xScale, float yScale) {
        m_ContentScaleCallback((Window *) this, xScale, yScale);
    }

    void Window::setContentScaleCallback(
            std::function<void(Window *window, float xScale, float yScale)> callback) {
        GP_CORE_DEBUG("Set '{0}' content scale callback", m_Title);

        m_ContentScaleCallback = std::move(callback);
        _setContentScaleCallback();
    }

    // Framebuffer Size
    void Window::onFramebufferSize(int width, int height) {
        m_FramebufferSizeCallback((Window *) this, width, height);
    }

    void Window::setFramebufferSizeCallback(
            std::function<void(Window *window, int width, int height)> callback) {
        GP_CORE_DEBUG("Set '{0}' framebuffer size callback", m_Title);

        m_FramebufferSizeCallback = std::move(callback);
        _setFramebufferSizeCallback();
    }

    void Window::onMouseMotion(float xPos, float yPos) {
        m_MouseMotionCallback((Window *) this, xPos, yPos);
    }

    void Window::setMouseMotionCallback(
            std::function<void(Window *window, float xPos, float yPos)> callback) {
        GP_CORE_DEBUG("Set '{0}' mouse motion callback", m_Title);

        m_MouseMotionCallback = std::move(callback);
        _setMouseMotionCallback();
    }

    void Window::onMouseEnter(bool entered) {
        m_MouseEnterCallback((Window *) this, entered);
    }

    void Window::setMouseEnterCallback(
            std::function<void(Window *window, bool entered)> callback) {
        GP_CORE_DEBUG("Set '{0}' mouse enter/exit callback", m_Title);

        m_MouseEnterCallback = std::move(callback);
        _setMouseEnterCallback();
    }

    void Window::onScroll(float xScroll, float yScroll) {
        m_ScrollCallback((Window *) this, xScroll, yScroll);
    }

    void Window::setScrollCallback(std::function<void(Window *window, float xScroll, float yScroll)> callback) {
        GP_CORE_DEBUG("Set '{0}' scroll callback", m_Title);

        m_ScrollCallback = std::move(callback);
        _setScrollCallback();
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
        GP_CORE_DEBUG("Destroying all windows");
        for (Window *&instance: s_Instances) {
            instance->destroy();
        }
    }
}
