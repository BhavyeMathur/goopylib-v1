#pragma once

#include "src/goopylib/Color/Color.h"
#include "src/goopylib/Scene/Renderer.h"

// TODO cursor callback
// TODO cursor enter/leave
// TODO check mouse button
// TODO mouse button callbacks
// TODO scroll callback
// TODO mouse input mode

class GLFWwindow;

namespace gp {
    enum class CursorMode;

    struct WindowConfig {
        int width;
        int height;
        const char *title;

        int xPos;
        int yPos;

        Color background;

        int minWidth;
        int minHeight;
        int maxWidth;
        int maxHeight;

        WindowConfig(int width,
                     int height,
                     const char *title = "goopylib Window",

                     int xPos = 0,
                     int yPos = 0,

                     const Color &background = Color(),

                     int minWidth = 0,
                     int minHeight = 0,
                     int maxWidth = MAX_WIDTH,
                     int maxHeight = MAX_HEIGHT) :

                width(width),
                height(height),
                title(title),

                xPos(xPos),
                yPos(yPos),

                background(background),

                minWidth(minWidth),
                minHeight(minHeight),
                maxWidth(maxWidth),
                maxHeight(maxHeight) {
        }
    };

    struct AspectRatio {
        int numerator;
        int denominator;
    };

    struct WindowFrame {
        int left;
        int top;
        int right;
        int bottom;
    };

    struct ContentScale {
        float xScale;
        float yScale;
    };

    struct FramebufferSize {
        int width;
        int height;
    };

    class Window {

        friend class Renderable;

        friend class Triangle;

        friend class Quad;

        friend class Ellipse;

        friend class Image;

        friend class Line;

    public:
        Window(const WindowConfig &config);

        ~Window();

        bool isClosed() const;

        bool isOpen() const;

        bool isDestroyed() const;

        void update();

        void destroy();

        // Getters & Setters

        // Width
        int getWidth() const;

        void setWidth(int value);

        // Height
        int getHeight() const;

        void setHeight(int value);

        // Title
        const char *getTitle() const;

        void setTitle(const char *title);

        // X Position
        int getXPos() const;

        void setXPos(int value);

        // Y Position
        int getYPos() const;

        void setYPos(int value);

        // Background
        Color &getBackground() const;

        void setBackground(const Color &background);

        // Minimum Width
        int getMinimumWidth() const;

        void setMinimumWidth(int value);

        // Minimum Height
        int getMinimumHeight() const;

        void setMinimumHeight(int value);

        // Maximum Width
        int getMaximumWidth() const;

        void setMaximumWidth(int value);

        // Maximum Height
        int getMaximumHeight() const;

        void setMaximumHeight(int value);

        // Get & Set Methods
        void setSize(int width, int height);

        void setSizeLimits(int minWidth, int minHeight,
                           int maxWidth, int maxHeight);

        void setMinimumSize(int minWidth, int minHeight);

        void setMaximumSize(int maxWidth, int maxHeight);

        void setPosition(int xPos, int yPos);

        // Camera & Projection
        Camera &getCamera();

        Point toWorld(Point p);

        Point toScreen(Point p);

        // Aspect Ratio
        void setAspectRatio(int numerator, int denominator);

        AspectRatio getAspectRatio() const;

        WindowFrame getFrameSize() const;

        ContentScale getContentScale() const;

        FramebufferSize getFramebufferSize() const;

        // Attributes

        bool isResizable() const;

        void setResizable(bool value);

        bool isDecorated() const;

        void setDecorated(bool value);

        bool isFloating() const;

        void setFloating(bool value);

        bool isAutoMinimized() const;

        void setAutoMinimized(bool value);

        bool isFocusedOnShow() const;

        void setFocusedOnShow(bool value);

        // State Methods

        void restore();

        void fullscreen();

        bool isFullscreen() const;

        void maximize();

        bool isMaximized() const;

        void minimize();

        bool isMinimized() const;

        void show();

        void hide();

        bool isVisible() const;

        void focus();

        bool hasFocus() const;

        void requestAttention() const;

        // Input Events

        bool isMouseHovering() const;

        Point getMousePosition() const;

        void setCursorMode(CursorMode mode) const;

        bool checkShiftKey() const;

        bool checkControlKey() const;

        bool checkAltKey() const;

        bool checkSuperKey() const;

        int checkKey(int key) const;

        void setKeyCallback(int key, std::function<void(Window *window, int action)> callback);

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

    private:
        WindowConfig m_Data;

        bool m_isDestroyed = false;
        int m_KeyModifiers = 0;  // check if shift, control, alt, and super keys are pressed

        void super();

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

        void onKeyPress(int key, int scancode, int action, int mods);

        #if GP_USING_GLFW

        GLFWwindow *getWindowGLFW();

        #endif

        static std::vector<Window *> s_Instances;

        #if GP_USING_GLFW

        GLFWwindow *m_Window = nullptr;

        #endif

        Renderer m_Renderer;

        int m_WindowedWidth;
        int m_WindowedHeight;
        int m_WindowedXPos;
        int m_WindowedYPos;

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

        std::unordered_map<int, std::function<void(Window *window, int action)>> m_KeyCallbacks;

        bool _isClosed() const;

        void _update() const;

        void _destroy() const;

        void _updateSize() const;

        void _updateTitle() const;

        void _updatePosition() const;

        void _updateBackground() const;

        void _updateSizeLimits() const;

        void _updateAspectRatio(int numerator, int denominator) const;

        // Window State Methods

        void _fullscreen() const;

        void _unfullscreen(int width, int height, int xPos, int yPos) const;

        void _maximize() const;

        void _minimize() const;

        void _restore() const;

        void _hide() const;

        void _show() const;

        void _focus() const;

        // Callback Functions

        void _setResizeCallback() const;

        void _setCloseCallback() const;

        void _setPositionCallback() const;

        void _setMinimizeCallback() const;

        void _setMaximizeCallback() const;

        void _setFocusedCallback() const;

        void _setRefreshCallback() const;

        void _setContentScaleCallback() const;

        void _setFramebufferSizeCallback() const;

        void _setKeyCallback() const;
    };
}
