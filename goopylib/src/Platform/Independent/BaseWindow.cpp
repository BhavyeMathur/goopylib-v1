#include "pch.h"
#include "BaseWindow.h"

namespace gp {
    struct WindowConfig;

    struct AspectRatio;
    struct WindowFrame;
    struct ContentScale;

    std::vector<BaseWindow *> BaseWindow::s_Instances;

    BaseWindow::BaseWindow(const WindowConfig &config)
    : m_Data(config)
    {
        GP_WINDOW_TRACE("Initializing BaseWindow '{0}'", m_Data.title);

        m_WindowedWidth = m_Data.width;
        m_WindowedHeight = m_Data.height;
        m_WindowedXPos = m_Data.xPos;
        m_WindowedYPos = m_Data.yPos;

        m_KeyModifiers = 0;

        m_Projection = glm::scale(glm::mat4(1),
                                  glm::vec3(2.0f / (float) config.width, 2.0f / (float) config.height, 1));
        m_isDestroyed = false;

        s_Instances.push_back(this);
    }

    BaseWindow::~BaseWindow() {
        GP_WINDOW_TRACE("Deallocating BaseWindow '{0}'", m_Data.title);
        s_Instances.erase(std::remove(s_Instances.begin(), s_Instances.end(), this), s_Instances.end());
    }

    void BaseWindow::update() {
        // GP_WINDOW_TRACE("Updating window '{0}'", m_Data.title);

        _update();
        _updateBackground();
    }

    void BaseWindow::destroy() {
        GP_WINDOW_INFO("Destroying window '{0}'", m_Data.title);

        if (!m_isDestroyed) {
            _destroy();
            m_isDestroyed = true;
            onDestroy();
        }
    }
}

// BaseWindow getters & setters
namespace gp {
    // Width
    void BaseWindow::setWidth(int value) {
        GP_WINDOW_TRACE("Set '{0}' width -> {1}", m_Data.title, value);

        m_Data.width = value;
        _updateSize();
    }

    int BaseWindow::getWidth() const {
        return m_Data.width;
    }

    // Height
    void BaseWindow::setHeight(int value) {
        GP_WINDOW_TRACE("Set '{0}' height -> {1}", m_Data.title, value);

        m_Data.height = value;
        _updateSize();
    }

    int BaseWindow::getHeight() const {
        return m_Data.height;
    }

    // Title
    void BaseWindow::setTitle(const char *title) {
        GP_WINDOW_TRACE("Set '{0}' title -> '{1}'", m_Data.title, title);

        m_Data.title = title;
        _updateTitle();
    }

    const char *BaseWindow::getTitle() const {
        return m_Data.title;
    }

    // X Position
    void BaseWindow::setXPos(int value) {
        GP_WINDOW_TRACE("Set '{0}' x-position -> {1}", m_Data.title, value);

        m_Data.xPos = value;
        _updatePosition();
    }

    int BaseWindow::getXPos() const {
        return m_Data.xPos;
    }

    // Y Position
    void BaseWindow::setYPos(int value) {
        GP_WINDOW_TRACE("Set '{0}' y-position -> {1}", m_Data.title, value);

        m_Data.yPos = value;
        _updatePosition();
    }

    int BaseWindow::getYPos() const {
        return m_Data.yPos;
    }

    // Minimum Width
    void BaseWindow::setMinimumWidth(int value) {
        GP_WINDOW_TRACE("Set '{0}' minimum width -> {1}", m_Data.title, value);

        m_Data.minWidth = value;
        _updateSizeLimits();
    }

    int BaseWindow::getMinimumWidth() const {
        return m_Data.minWidth;
    }

    // Minimum Height
    void BaseWindow::setMinimumHeight(int value) {
        GP_WINDOW_TRACE("Set '{0}' minimum height -> {1}", m_Data.title, value);

        m_Data.minHeight = value;
        _updateSizeLimits();
    }

    int BaseWindow::getMinimumHeight() const {
        return m_Data.minHeight;
    }

    // Maximum Width
    void BaseWindow::setMaximumWidth(int value) {
        GP_WINDOW_TRACE("Set '{0}' maximum width -> {1}", m_Data.title, value);

        m_Data.maxWidth = value;
        _updateSizeLimits();
    }

    int BaseWindow::getMaximumWidth() const {
        return m_Data.maxWidth;
    }

    // Maximum Height
    void BaseWindow::setMaximumHeight(int value) {
        GP_WINDOW_TRACE("Set '{0}' maximum height -> {1}", m_Data.title, value);

        m_Data.maxHeight = value;
        _updateSizeLimits();
    }

    int BaseWindow::getMaximumHeight() const {
        return m_Data.maxHeight;
    }

    void BaseWindow::setBackground(const Color &background) {
        GP_WINDOW_TRACE("Set '{0}' background -> {1}", m_Data.title, background.toString());

        m_Data.background = background;
        _updateBackground();
    }

    Color& BaseWindow::getBackground() const {
        return const_cast<Color&>(m_Data.background);
    }
}

// BaseWindow get & set methods
namespace gp {

    // Size
    void BaseWindow::setSize(int width, int height) {
        GP_WINDOW_TRACE("Set '{0}' size -> ({1}, {2})", m_Data.title, width, height);

        m_Data.width = width;
        m_Data.height = height;

        _updateSize();
    }

    // Size Limits
    void BaseWindow::setSizeLimits(int minWidth, int minHeight, int maxWidth,
                                   int maxHeight) {
        GP_WINDOW_TRACE("Set '{0}' size limits -> ({1}, {2}), ({3}, {4})", m_Data.title, minWidth, minHeight, maxWidth,
                        maxHeight);

        m_Data.minWidth = minWidth;
        m_Data.minHeight = minHeight;
        m_Data.maxWidth = maxWidth;
        m_Data.maxHeight = maxHeight;

        _updateSizeLimits();
    }

    void BaseWindow::setMinimumSize(int minWidth, int minHeight) {
        GP_WINDOW_TRACE("Set '{0}' minimum size -> ({1}, {2})", m_Data.title, minWidth, minHeight);

        m_Data.minWidth = minWidth;
        m_Data.minHeight = minHeight;

        _updateSizeLimits();
    }

    void BaseWindow::setMaximumSize(int maxWidth, int maxHeight) {
        GP_WINDOW_TRACE("Set '{0}' maximum size -> ({1}, {2})", m_Data.title, maxWidth, maxHeight);

        m_Data.maxWidth = maxWidth;
        m_Data.maxHeight = maxHeight;

        _updateSizeLimits();
    }

    // Position
    void BaseWindow::setPosition(int xPos, int yPos) {
        GP_WINDOW_TRACE("Set '{0}' position -> ({1}, {2})", m_Data.title, xPos, yPos);

        m_Data.xPos = xPos;
        m_Data.yPos = yPos;

        _updatePosition();
    }

    void BaseWindow::setAspectRatio(int numerator, int denominator) {
        int g = gcd(numerator, denominator);
        _updateAspectRatio(numerator / g, denominator / g);

    }

    AspectRatio BaseWindow::getAspectRatio() const {
        int g = gcd(m_Data.width, m_Data.height);
        return AspectRatio{m_Data.width / g, m_Data.height / g};
    }
}

// BaseWindow state methods
namespace gp {
    bool BaseWindow::isDestroyed() const {
        return m_isDestroyed;
    }

    bool BaseWindow::isClosed() const {
        return _isClosed() or m_isDestroyed;
    }

    bool BaseWindow::isOpen() const {
        return !isClosed();
    }

    void BaseWindow::restore() {
        if (isFullscreen()) {
            _unfullscreen(m_WindowedWidth, m_WindowedHeight, m_WindowedXPos, m_WindowedYPos);
        }
        else {
            _restore();
        }
    }

    void BaseWindow::fullscreen() {
        m_WindowedWidth = m_Data.width;
        m_WindowedHeight = m_Data.height;
        m_WindowedXPos = m_Data.xPos;
        m_WindowedYPos = m_Data.yPos;

        _fullscreen();
    }

    void BaseWindow::maximize() {
        _maximize();
    }

    void BaseWindow::minimize() {
        _minimize();
    }

    void BaseWindow::show() {
        _show();
    }

    void BaseWindow::hide() {
        _hide();
    }

    void BaseWindow::focus() {
        _focus();
    }
}

// BaseWindow events
namespace gp {
    void BaseWindow::onKeyPress(int key, int UNUSED(scancode), int action, int mods) {
        m_KeyModifiers = mods;
        if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks[key]((Window *) this, action);
        }
    }

    void BaseWindow::setKeyCallback(int key, std::function<void(Window *window, int action)> callback) {
        GP_WINDOW_TRACE("Set '{0}' key ({1}) callback", m_Data.title, key);

        if (callback) {
            m_KeyCallbacks[key] = std::move(callback);
        }
        else if (m_KeyCallbacks.find(key) != m_KeyCallbacks.end()) {
            m_KeyCallbacks.erase(key);
        }
        // _setKeyCallback(); // Not required as it is already set in super()
    }
}

// BaseWindow callbacks
namespace gp {
    // Resize
    void BaseWindow::onResize(int width, int height) {
        m_Data.width = width;
        m_Data.height = height;

        if (m_ResizeCallback) {
            m_ResizeCallback((Window *) this, width, height);
        }

        m_Projection = glm::scale(glm::mat4(1), glm::vec3(2.0f / (float) width, 2.0f / (float) height, 1));
        update();
    }

    void BaseWindow::setResizeCallback(std::function<void(Window *, int width, int height)> callback) {
        GP_WINDOW_TRACE("Set '{0}' resize callback", m_Data.title);

        m_ResizeCallback = std::move(callback);
        // _setResizeCallback(); // Not required as it is already set in super()
    }

    // Close
    void BaseWindow::onClose() {
        GP_WINDOW_TRACE("OnClose()");
        m_CloseCallback((Window *) this);
    }

    void BaseWindow::setCloseCallback(std::function<void(Window *window)> callback) {
        GP_WINDOW_TRACE("Set '{0}' close callback", m_Data.title);

        m_CloseCallback = std::move(callback);
        _setCloseCallback();
    }

    // Destroy
    void BaseWindow::onDestroy() {
        GP_WINDOW_TRACE("OnDestroy()");
        if (m_DestroyCallback) {
            m_DestroyCallback((Window *) this);
        }
    }

    void BaseWindow::setDestroyCallback(std::function<void(Window *window)> callback) {
        GP_WINDOW_TRACE("Set '{0}' destroy callback", m_Data.title);

        m_DestroyCallback = std::move(callback);
    }

    // Move
    void BaseWindow::onMove(int xPos, int yPos) {
        m_Data.xPos = xPos;
        m_Data.yPos = yPos;

        if (m_PositionCallback) {
            m_PositionCallback((Window *) this, xPos, yPos);
        }
    }

    void BaseWindow::setPositionCallback(std::function<void(Window *window, int xPos, int yPos)> callback) {
        GP_WINDOW_TRACE("Set '{0}' position callback", m_Data.title);

        m_PositionCallback = std::move(callback);
        // _setPositionCallback(); // Not required as it is already set in super()
    }

    // Minimize
    void BaseWindow::onMinimize(bool iconified) {
        GP_WINDOW_TRACE("OnMinimize()");
        m_MinimizeCallback((Window *) this, iconified);
    }

    void BaseWindow::setMinimizeCallback(std::function<void(Window *window, bool minimized)> callback) {
        GP_WINDOW_TRACE("Set '{0}' minimize callback", m_Data.title);

        m_MinimizeCallback = std::move(callback);
        _setMinimizeCallback();
    }

    // Maximize
    void BaseWindow::onMaximize(bool maximized) {
        GP_WINDOW_TRACE("OnMaximize()");
        m_MaximizeCallback((Window *) this, maximized);
    }

    void BaseWindow::setMaximizeCallback(std::function<void(Window *window, bool maximized)> callback) {
        GP_WINDOW_TRACE("Set '{0}' maximize callback", m_Data.title);

        m_MaximizeCallback = std::move(callback);
        _setMaximizeCallback();
    }

    // Focus
    void BaseWindow::onFocus(bool focused) {
        GP_WINDOW_TRACE("OnFocus()");
        m_FocusedCallback((Window *) this, focused);
    }

    void BaseWindow::setFocusCallback(std::function<void(Window *window, bool focused)> callback) {
        GP_WINDOW_TRACE("Set '{0}' focus callback", m_Data.title);

        m_FocusedCallback = std::move(callback);
        _setFocusedCallback();
    }

    // Refresh
    void BaseWindow::onRefreshRequired() {
        m_RefreshCallback((Window *) this);
    }

    void BaseWindow::setRefreshCallback(std::function<void(Window *window)> callback) {
        GP_WINDOW_TRACE("Set '{0}' refresh required callback", m_Data.title);

        m_RefreshCallback = std::move(callback);
        _setRefreshCallback();
    }

    // Content Scale
    void BaseWindow::onContentScale(float xScale, float yScale) {
        m_ContentScaleCallback((Window *) this, xScale, yScale);
    }

    void BaseWindow::setContentScaleCallback(
            std::function<void(Window *window, float xScale, float yScale)> callback) {
        GP_WINDOW_TRACE("Set '{0}' content scale callback", m_Data.title);

        m_ContentScaleCallback = std::move(callback);
        _setContentScaleCallback();
    }

    // Framebuffer Size
    void BaseWindow::onFramebufferSize(int width, int height) {
        m_FramebufferSizeCallback((Window *) this, width, height);
    }

    void BaseWindow::setFramebufferSizeCallback(
            std::function<void(Window *window, int width, int height)> callback) {
        GP_WINDOW_TRACE("Set '{0}' framebuffer size callback", m_Data.title);

        m_FramebufferSizeCallback = std::move(callback);
        _setFramebufferSizeCallback();
    }
}

// BaseWindow static methods
namespace gp {
    void BaseWindow::updateAll() {
        // GP_WINDOW_TRACE("Updating all windows");

        for (BaseWindow *&instance: s_Instances) {
            instance->update();
        }
    }

    void BaseWindow::destroyAll() {
        GP_WINDOW_TRACE("Destroying all windows");
        for (BaseWindow *&instance: s_Instances) {
            instance->destroy();
        }
    }
}
