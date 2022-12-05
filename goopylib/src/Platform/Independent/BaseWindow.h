#pragma once

#include "pch.h"

#define GP_WINDOW_TRACE(...) GP_CORE_TRACE("WINDOW: " __VA_ARGS__)
#define GP_WINDOW_INFO(...) GP_CORE_INFO("WINDOW: " __VA_ARGS__)

namespace gp {
    class Window;

    struct WindowConfig {
        unsigned int width;
        unsigned int height;
        unsigned int minWidth;
        unsigned int minHeight;
        unsigned int maxWidth;
        unsigned int maxHeight;

        int xPos;
        int yPos;

        const char *title;

        explicit WindowConfig(unsigned int width = 800,
                              unsigned int height = 450,
                              unsigned int minWidth = 0,
                              unsigned int minHeight = 0,
                              unsigned int maxWidth = MAX_WIDTH,
                              unsigned int maxHeight = MAX_HEIGHT,
                              int xPos = 0,
                              int yPos = 0,
                              const char *title = "goopylib Window") :

                width(width),
                height(height),
                minWidth(minWidth),
                minHeight(minHeight),
                maxWidth(maxWidth),
                maxHeight(maxHeight),
                xPos(xPos),
                yPos(yPos),
                title(title) {
        }
    };

    class BaseWindow {
    public:
        explicit BaseWindow(const WindowConfig &config);

        virtual ~BaseWindow();

        bool isClosed() const;

        bool isDestroyed() const;

        void update();

        void destroy();

        // Getters & Setters
        unsigned int getWidth() const;

        void setWidth(unsigned int value);

        unsigned int getHeight() const;

        void setHeight(unsigned int value);

        unsigned int getMinimumWidth() const;

        void setMinimumWidth(unsigned int value);

        unsigned int getMinimumHeight() const;

        void setMinimumHeight(unsigned int value);

        unsigned int getMaximumWidth() const;

        void setMaximumWidth(unsigned int value);

        unsigned int getMaximumHeight() const;

        void setMaximumHeight(unsigned int value);

        int getXPos() const;

        void setXPos(int value);

        int getYPos() const;

        void setYPos(int value);

        const char *getTitle() const;

        void setTitle(const char *title);

        // Get & Set Methods

        void setSize(unsigned int width, unsigned int height);

        void setSizeLimits(unsigned int minWidth, unsigned int minHeight,
                           unsigned int maxWidth, unsigned int maxHeight);

        void setMinimumSize(unsigned int minWidth, unsigned int minHeight);

        void setMaximumSize(unsigned int maxWidth, unsigned int maxHeight);

        void setPosition(int xPos, int yPos);

        // Attributes
        virtual bool isResizable() const = 0;

        virtual void setResizable(bool value) = 0;

        virtual bool isDecorated() const = 0;

        virtual void setDecorated(bool value) = 0;

        virtual bool isFloating() const = 0;

        virtual void setFloating(bool value) = 0;

        virtual bool isAutoMinimized() const = 0;

        virtual void setAutoMinimized(bool value) = 0;

        virtual bool isFocusedOnShow() const = 0;

        virtual void setFocusedOnShow(bool value) = 0;

        // State Methods
        virtual bool isFullscreen() const = 0;

        virtual bool isMaximized() const = 0;

        virtual bool isMinimized() const = 0;

        virtual bool isVisible() const = 0;

        // Callback Functions

        void setResizeCallback(std::function<void(Window *window, int width, int height)> callback);

        void setCloseCallback(std::function<void(Window *window)> callback);

        void setDestroyCallback(std::function<void(Window *window)> callback);

        void setPositionCallback(std::function<void(Window *window, int xPos, int yPos)> callback);

        void setMinimizeCallback(std::function<void(Window *window, bool minimized)> callback);

        void setMaximizeCallback(std::function<void(Window *window, bool maximized)> callback);

        void setFocusCallback(std::function<void(Window *window, bool focused)> callback);

        void setRefreshCallback(std::function<void(Window *window)> callback);

        void setContentScaleCallback(std::function<void(Window *window, float xScale, float yScale)> callback);

        void setFramebufferSizeCallback(std::function<void(Window *window, int width, int height)> callback);

        // Static Methods
        static void updateAll();

        static void destroyAll();

    protected:
        WindowConfig m_Data;
        glm::mat4 m_Projection{};

        bool m_isDestroyed;

        void super() {
            _updatePosition();
            _updateSizeLimits();
            _setResizeCallback();
        }

        // Callback Functions
        void onResize(int width, int height);

        void onClose();

        void onDestroy();

        void onMove(int xPos, int yPos);

        void onMinimize(bool iconified);

        void onMaximize(bool maximized);

        void onFocus(bool focused);

        void onRefreshRequired();

        void onContentScale(float xScale, float yScale);

        void onFramebufferSize(int width, int height);

    private:
        static std::vector<BaseWindow *> s_Instances;

        // Callback Functions
        std::function<void(Window *window, int width, int height)> m_ResizeCallback;
        std::function<void(Window *window)> m_CloseCallback;
        std::function<void(Window *window)> m_DestroyCallback;
        std::function<void(Window *window, int xPos, int yPos)> m_PositionCallback;
        std::function<void(Window *window, bool minimized)> m_MinimizeCallback;
        std::function<void(Window *window, bool maximized)> m_MaximizeCallback;
        std::function<void(Window *window, bool focused)> m_FocusedCallback;
        std::function<void(Window *window)> m_RefreshCallback;
        std::function<void(Window *window, float xScale, float yScale)> m_ContentScaleCallback;
        std::function<void(Window *window, int width, int height)> m_FramebufferSizeCallback;

        virtual bool _isClosed() const = 0;

        virtual void _update() const = 0;

        virtual void _destroy() const = 0;

        virtual void _updateSize() const = 0;

        virtual void _updatePosition() const = 0;

        virtual void _updateTitle() const = 0;

        virtual void _updateSizeLimits() const = 0;

        // Callback Functions

        virtual void _setResizeCallback() const = 0;

        virtual void _setCloseCallback() const = 0;

        virtual void _setPositionCallback() const = 0;

        virtual void _setMinimizeCallback() const = 0;

        virtual void _setMaximizeCallback() const = 0;

        virtual void _setFocusedCallback() const = 0;

        virtual void _setRefreshCallback() const = 0;

        virtual void _setContentScaleCallback() const = 0;

        virtual void _setFramebufferSizeCallback() const = 0;
    };
}
