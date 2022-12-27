#pragma once

#include "src/goopylib/scene/Renderer.h"
#include "src/goopylib/color/Color.h"

class GLFWwindow;

namespace gp {
    enum class CursorMode;

    class Color;

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
}

// TODO window autoflush
namespace gp {
    class Window {

        friend class Renderable;

        friend class Triangle;

        friend class Quad;

        friend class Ellipse;

        friend class Image;

        friend class Line;

    public:
        Window(int width, int height, const char *title = "goopylib Window");

        ~Window();

        #if GP_USING_GLFW

        GLFWwindow *getWindowGLFW();

        #endif

        bool isClosed() const;

        bool isOpen() const;

        bool isDestroyed() const;

        void update();

        void destroy();

        /* Getters & Setters -----------------------------------------------------------------------------------------*/

        // Width
        void setWidth(int value);

        int getWidth() const;

        // Height
        void setHeight(int value);

        int getHeight() const;

        // Title
        void setTitle(const char *value);

        const char *getTitle() const;

        // X Position
        void setXPos(int value);

        int getXPos() const;

        // Y Position
        void setYPos(int value);

        int getYPos() const;

        // Background
        void setBackground(const Color &value);

        Color &getBackground();

        // Minimum Width
        void setMinWidth(int value);

        int getMinWidth() const;

        // Minimum Height
        void setMinHeight(int value);

        int getMinHeight() const;

        // Maximum Width
        void setMaxWidth(int value);

        int getMaxWidth() const;

        // Maximum Height
        void setMaxHeight(int value);

        int getMaxHeight() const;

        // Get & Set Methods
        void setSize(int width, int height);

        void setSizeLimits(int minWidth, int minHeight,
                           int maxWidth, int maxHeight);

        void setMinSize(int minWidth, int minHeight);

        void setMaxSize(int maxWidth, int maxHeight);

        void setPosition(int xPos, int yPos);

        void setAspectRatio(int numerator, int denominator);

        AspectRatio getAspectRatio() const;

        WindowFrame getFrameSize() const;

        ContentScale getContentScale() const;

        FramebufferSize getFramebufferSize() const;

        /* Window Attributes -----------------------------------------------------------------------------------------*/

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

        /* Window State Methods --------------------------------------------------------------------------------------*/

        void restore();

        // Fullscreen
        void fullscreen();

        bool isFullscreen() const;

        // Maximize
        void maximize();

        bool isMaximized() const;

        // Minimize
        void minimize();

        bool isMinimized() const;

        // Visibility
        void show();

        void hide();

        bool isVisible() const;

        // Input Focus
        void focus();

        bool hasFocus() const;

        void requestAttention() const;

        /* Window Input Events ---------------------------------------------------------------------------------------*/

        bool isMouseHovering() const;

        Point getMousePosition() const;

        void setCursorMode(CursorMode mode) const;

        bool checkShiftKey() const;

        bool checkControlKey() const;

        bool checkAltKey() const;

        bool checkSuperKey() const;

        int checkKey(int key) const;

        bool checkMouseButton(int button) const;

        bool checkLeftClick() const;

        bool checkMiddleClick() const;

        bool checkRightClick() const;

        /* Window Callback Functions ---------------------------------------------------------------------------------*/

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

        void setMouseMotionCallback(std::function<void(Window *window, float xPos, float yPos)> callback);

        void setMouseEnterCallback(std::function<void(Window *window, bool entered)> callback);

        void setScrollCallback(std::function<void(Window *window, float xScroll, float yScroll)> callback);

        void setKeyCallback(int key, std::function<void(Window *window, int action)> callback);

        void setMouseButtonCallback(int button, std::function<void(Window *window, bool pressed)> callback);

        void setLeftClickCallback(std::function<void(Window *window, bool pressed)> callback);

        void setMiddleClickCallback(std::function<void(Window *window, bool pressed)> callback);

        void setRightClickCallback(std::function<void(Window *window, bool pressed)> callback);

        /* Other Window Methods --------------------------------------------------------------------------------------*/

        Camera &getCamera();

        Point toWorld(Point p);

        Point toScreen(Point p);

        /* Static Methods --------------------------------------------------------------------------------------------*/

        static void updateAll();

        static void destroyAll();

    private:
        int m_Width;
        int m_Height;
        const char *m_Title;

        int m_xPos;
        int m_yPos;

        Color m_Background;

        int m_MinWidth = 0;
        int m_MinHeight = 0;
        int m_MaxWidth = INT_MAX;
        int m_MaxHeight = INT_MAX;

        int m_WindowedWidth;
        int m_WindowedHeight;
        int m_WindowedXPos;
        int m_WindowedYPos;

        bool m_IsDestroyed = false;
        int m_KeyModifiers = 0;  // check if shift, control, alt, and super keys are pressed

        Renderer m_Renderer;

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
        std::function<void(Window *window, float xPos, float yPos)> m_MouseMotionCallback;
        std::function<void(Window *window, bool entered)> m_MouseEnterCallback;
        std::function<void(Window *window, float xScroll, float yScroll)> m_ScrollCallback;

        std::unordered_map<int, std::function<void(Window *window, int action)>> m_KeyCallbacks;
        std::unordered_map<int, std::function<void(Window *window, bool pressed)>> m_MouseCallbacks;

        static std::vector<Window *> s_Instances;

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

        void onMouseMotion(float xPos, float yPos);

        void onMouseEnter(bool entered);

        void onScroll(float xScroll, float yScroll);

        void onKeyPress(int key, int scancode, int action, int mods);

        void onMousePress(int button, int action, int mods);

        #if GP_USING_GLFW

        GLFWwindow *m_Window = nullptr;

        #endif

        void _swapBuffers() const;

        void _destroy() const;

        void _updateSize() const;

        void _updatePosition() const;

        void _updateBackground() const;

        void _updateSizeLimits() const;

        void _updateAspectRatio(int numerator, int denominator) const;

        void _fullscreen() const;

        void _unfullscreen(int width, int height, int xPos, int yPos) const;

        void _restore() const;

        void _setKeyCallback() const;

        void _setMouseButtonCallback() const;
    };
}
