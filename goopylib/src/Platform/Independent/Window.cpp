#include "src/goopylib/Core/Window.h"

namespace gp {
    std::vector<Window *> Window::s_Instances;

    void Window::update() {
        GP_CORE_TRACE_ALL("Updating window '{0}'", m_Data.title);

        _updateBackground();

        m_Renderer.flush();

        _update();
    }

    void Window::destroy() {
        GP_CORE_INFO("Destroying window '{0}'", m_Data.title);

        if (!m_isDestroyed) {
            _destroy();
            m_isDestroyed = true;
            onDestroy();
        }
    }
}

// Window getters & setters
namespace gp {
    // Width
    void Window::setWidth(int value) {
        GP_CORE_DEBUG("Set '{0}' width -> {1}", m_Data.title, value);

        m_Data.width = value;
        _updateSize();
    }

    int Window::getWidth() const {
        return m_Data.width;
    }

    // Height
    void Window::setHeight(int value) {
        GP_CORE_DEBUG("Set '{0}' height -> {1}", m_Data.title, value);

        m_Data.height = value;
        _updateSize();
    }

    int Window::getHeight() const {
        return m_Data.height;
    }

    // Title
    void Window::setTitle(const char *title) {
        GP_CORE_DEBUG("Set '{0}' title -> '{1}'", m_Data.title, title);

        m_Data.title = title;
        _updateTitle();
    }

    const char *Window::getTitle() const {
        return m_Data.title;
    }

    // X Position
    void Window::setXPos(int value) {
        GP_CORE_DEBUG("Set '{0}' x-position -> {1}", m_Data.title, value);

        m_Data.xPos = value;
        _updatePosition();
    }

    int Window::getXPos() const {
        return m_Data.xPos;
    }

    // Y Position
    void Window::setYPos(int value) {
        GP_CORE_DEBUG("Set '{0}' y-position -> {1}", m_Data.title, value);

        m_Data.yPos = value;
        _updatePosition();
    }

    int Window::getYPos() const {
        return m_Data.yPos;
    }

    // Minimum Width
    void Window::setMinimumWidth(int value) {
        GP_CORE_DEBUG("Set '{0}' minimum width -> {1}", m_Data.title, value);

        m_Data.minWidth = value;
        _updateSizeLimits();
    }

    int Window::getMinimumWidth() const {
        return m_Data.minWidth;
    }

    // Minimum Height
    void Window::setMinimumHeight(int value) {
        GP_CORE_DEBUG("Set '{0}' minimum height -> {1}", m_Data.title, value);

        m_Data.minHeight = value;
        _updateSizeLimits();
    }

    int Window::getMinimumHeight() const {
        return m_Data.minHeight;
    }

    // Maximum Width
    void Window::setMaximumWidth(int value) {
        GP_CORE_DEBUG("Set '{0}' maximum width -> {1}", m_Data.title, value);

        m_Data.maxWidth = value;
        _updateSizeLimits();
    }

    int Window::getMaximumWidth() const {
        return m_Data.maxWidth;
    }

    // Maximum Height
    void Window::setMaximumHeight(int value) {
        GP_CORE_DEBUG("Set '{0}' maximum height -> {1}", m_Data.title, value);

        m_Data.maxHeight = value;
        _updateSizeLimits();
    }

    int Window::getMaximumHeight() const {
        return m_Data.maxHeight;
    }

    void Window::setBackground(const Color &background) {
        GP_CORE_DEBUG("Set '{0}' background -> {1}", m_Data.title, background.toString());

        m_Data.background = background;
        _updateBackground();
    }

    Color &Window::getBackground() const {
        return const_cast<Color &>(m_Data.background);
    }
}

// Window get & set methods
namespace gp {

    // Size
    void Window::setSize(int width, int height) {
        GP_CORE_DEBUG("Set '{0}' size -> ({1}, {2})", m_Data.title, width, height);

        m_Data.width = width;
        m_Data.height = height;

        _updateSize();
    }

    // Size Limits
    void Window::setSizeLimits(int minWidth, int minHeight, int maxWidth,
                               int maxHeight) {
        GP_CORE_DEBUG("Set '{0}' size limits -> ({1}, {2}), ({3}, {4})", m_Data.title, minWidth, minHeight, maxWidth,
                      maxHeight);

        m_Data.minWidth = minWidth;
        m_Data.minHeight = minHeight;
        m_Data.maxWidth = maxWidth;
        m_Data.maxHeight = maxHeight;

        _updateSizeLimits();
    }

    void Window::setMinimumSize(int minWidth, int minHeight) {
        GP_CORE_DEBUG("Set '{0}' minimum size -> ({1}, {2})", m_Data.title, minWidth, minHeight);

        m_Data.minWidth = minWidth;
        m_Data.minHeight = minHeight;

        _updateSizeLimits();
    }

    void Window::setMaximumSize(int maxWidth, int maxHeight) {
        GP_CORE_DEBUG("Set '{0}' maximum size -> ({1}, {2})", m_Data.title, maxWidth, maxHeight);

        m_Data.maxWidth = maxWidth;
        m_Data.maxHeight = maxHeight;

        _updateSizeLimits();
    }

    // Position
    void Window::setPosition(int xPos, int yPos) {
        GP_CORE_DEBUG("Set '{0}' position -> ({1}, {2})", m_Data.title, xPos, yPos);

        m_Data.xPos = xPos;
        m_Data.yPos = yPos;

        _updatePosition();
    }

    void Window::setAspectRatio(int numerator, int denominator) {
        int g = gcd(numerator, denominator);
        _updateAspectRatio(numerator / g, denominator / g);

    }

    AspectRatio Window::getAspectRatio() const {
        int g = gcd(m_Data.width, m_Data.height);
        return AspectRatio{m_Data.width / g, m_Data.height / g};
    }
}

// Window state methods
namespace gp {
    bool Window::isDestroyed() const {
        return m_isDestroyed;
    }

    bool Window::isClosed() const {
        return _isClosed() or m_isDestroyed;
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
        m_WindowedWidth = m_Data.width;
        m_WindowedHeight = m_Data.height;
        m_WindowedXPos = m_Data.xPos;
        m_WindowedYPos = m_Data.yPos;

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
    void Window::onKeyPress(int key, int UNUSED(scancode), int action, int mods) {
        m_KeyModifiers = mods;
        if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks[key]((Window *) this, action);
        }
    }

    void Window::setKeyCallback(int key, std::function<void(Window *window, int action)> callback) {
        GP_CORE_DEBUG("Set '{0}' key ({1}) callback", m_Data.title, key);

        if (callback) {
            m_KeyCallbacks[key] = std::move(callback);
        }
        else if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks.erase(key);
        }
        // _setKeyCallback(); // Not required as it is already set in super()
    }
}

// Window callbacks
namespace gp {
    // Resize
    void Window::onResize(int width, int height) {
        m_Data.width = width;
        m_Data.height = height;

        if (m_ResizeCallback) {
            m_ResizeCallback((Window *) this, width, height);
        }

        update();
    }

    void Window::setResizeCallback(std::function<void(Window *, int width, int height)> callback) {
        GP_CORE_DEBUG("Set '{0}' resize callback", m_Data.title);

        m_ResizeCallback = std::move(callback);
        // _setResizeCallback(); // Not required as it is already set in super()
    }

    // Close
    void Window::onClose() {
        GP_CORE_DEBUG("OnClose()");
        m_CloseCallback((Window *) this);
    }

    void Window::setCloseCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("Set '{0}' close callback", m_Data.title);

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
        GP_CORE_DEBUG("Set '{0}' destroy callback", m_Data.title);

        m_DestroyCallback = std::move(callback);
    }

    // Move
    void Window::onMove(int xPos, int yPos) {
        m_Data.xPos = xPos;
        m_Data.yPos = yPos;

        if (m_PositionCallback) {
            m_PositionCallback((Window *) this, xPos, yPos);
        }
    }

    void Window::setPositionCallback(std::function<void(Window *window, int xPos, int yPos)> callback) {
        GP_CORE_DEBUG("Set '{0}' position callback", m_Data.title);

        m_PositionCallback = std::move(callback);
        // _setPositionCallback(); // Not required as it is already set in super()
    }

    // Minimize
    void Window::onMinimize(bool iconified) {
        GP_CORE_DEBUG("OnMinimize()");
        m_MinimizeCallback((Window *) this, iconified);
    }

    void Window::setMinimizeCallback(std::function<void(Window *window, bool minimized)> callback) {
        GP_CORE_DEBUG("Set '{0}' minimize callback", m_Data.title);

        m_MinimizeCallback = std::move(callback);
        _setMinimizeCallback();
    }

    // Maximize
    void Window::onMaximize(bool maximized) {
        GP_CORE_DEBUG("OnMaximize()");
        m_MaximizeCallback((Window *) this, maximized);
    }

    void Window::setMaximizeCallback(std::function<void(Window *window, bool maximized)> callback) {
        GP_CORE_DEBUG("Set '{0}' maximize callback", m_Data.title);

        m_MaximizeCallback = std::move(callback);
        _setMaximizeCallback();
    }

    // Focus
    void Window::onFocus(bool focused) {
        GP_CORE_DEBUG("OnFocus()");
        m_FocusedCallback((Window *) this, focused);
    }

    void Window::setFocusCallback(std::function<void(Window *window, bool focused)> callback) {
        GP_CORE_DEBUG("Set '{0}' focus callback", m_Data.title);

        m_FocusedCallback = std::move(callback);
        _setFocusedCallback();
    }

    // Refresh
    void Window::onRefreshRequired() {
        m_RefreshCallback((Window *) this);
    }

    void Window::setRefreshCallback(std::function<void(Window *window)> callback) {
        GP_CORE_DEBUG("Set '{0}' refresh required callback", m_Data.title);

        m_RefreshCallback = std::move(callback);
        _setRefreshCallback();
    }

    // Content Scale
    void Window::onContentScale(float xScale, float yScale) {
        m_ContentScaleCallback((Window *) this, xScale, yScale);
    }

    void Window::setContentScaleCallback(
            std::function<void(Window *window, float xScale, float yScale)> callback) {
        GP_CORE_DEBUG("Set '{0}' content scale callback", m_Data.title);

        m_ContentScaleCallback = std::move(callback);
        _setContentScaleCallback();
    }

    // Framebuffer Size
    void Window::onFramebufferSize(int width, int height) {
        m_FramebufferSizeCallback((Window *) this, width, height);
    }

    void Window::setFramebufferSizeCallback(
            std::function<void(Window *window, int width, int height)> callback) {
        GP_CORE_DEBUG("Set '{0}' framebuffer size callback", m_Data.title);

        m_FramebufferSizeCallback = std::move(callback);
        _setFramebufferSizeCallback();
    }
}

// Window static methods
namespace gp {
    void Window::updateAll() {
        // GP_CORE_DEBUG("Updating all windows");

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
