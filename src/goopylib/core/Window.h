#pragma once

#include "src/goopylib/scene/RenderingManager.h"

#include <GLFW/glfw3.h>

#ifdef APIENTRY
#undef APIENTRY
#endif

// TODO implement window icons (v2.0.x)

struct GLFWwindow;

namespace gp {
    enum class CursorMode {
        Normal = GLFW_CURSOR_NORMAL,
        Disabled = GLFW_CURSOR_DISABLED,
        Hidden = GLFW_CURSOR_HIDDEN
    };

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

namespace gp {
    /**
     * Creates a window that can be used to draw graphics and widgets.
     * 
     * @param width in screen coordinates
     * @param height in screen coordinates
     * @param title displayed in the title bar
     */
    class Window final : public RenderingManager {

        friend class Renderer;

    public:
        /**
         * Creates a window that can be used to draw graphics and widgets.
         * 
        * @param width in screen coordinates
         * @param height in screen coordinates
         * @param title displayed in the title bar
         * 
         * @throws std::invalid_argument width must be greater than 0
         * @throws std::invalid_argument height must be greater than 0
         */
        GPAPI Window(int width, int height, const char *title = "goopylib Window");

        GPAPI Window(const Window &) = delete;

        GPAPI Window(Window &&other) = delete;

        GPAPI ~Window();

        GPAPI std::string toString();

        #if GP_USING_GLFW

        /**
         * @return a pointer to the underlying GLFW context.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI GLFWwindow *getWindowGLFW();

        #endif

        /**
         * @return whether the window is closed.
         */
        [[nodiscard]] GPAPI bool isClosed() const;

        /**
         * @return whether the window is open.
         */
        [[nodiscard]] GPAPI bool isOpen() const;

        /**
         * @return whether the window has been destroyed.
         */
        [[nodiscard]] GPAPI bool isDestroyed() const;

        /**
         * Refreshes the window.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void update();

        /**
         * Destroys & closes the window.
         * 
         * @warning Once the window is destroyed, calling its methods is undefined.
         */
        GPAPI void destroy();

        /* Getters & Setters -----------------------------------------------------------------------------------------*/

        // Title
        /**
         * @param value the title string to show in the title menu
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setTitle(const char *value);

        /**
         * @return the title string showed in the title menu
         */
        [[nodiscard]] GPAPI const char *getTitle() const;

        // X Position
        /**
         * @param value in screen coordinates of the upper-left corner of the Window
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setXPos(int value);

        /**
         * @return in screen coordinates, the position of the upper-left corner of the Window
         */
        [[nodiscard]] GPAPI int getXPos() const;

        // Y Position
        /**
         * @param value in screen coordinates of the upper-left corner of the Window
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setYPos(int value);

        /**
         * @return in screen coordinates, the position of the lower-right corner of the Window
         */
        [[nodiscard]] GPAPI int getYPos() const;

        // Minimum Width
        /**
         * @param value in screen coordinates
         * 
         * @note this attribute applies only to resizable windows.
         * 
         * @throws std::invalid_argument value must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setMinWidth(int value);

        /**
         * @return the minimum resizable width in screen coordinates
         */
        [[nodiscard]] GPAPI int getMinWidth() const;

        // Minimum Height
        /**
         * @param value in screen coordinates
         *
         * @note this attribute applies only to resizable windows.
         *
         * @throws std::invalid_argument value must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setMinHeight(int value);

        /**
         * @return the minimum resizable height in screen coordinates
         */
        [[nodiscard]] GPAPI int getMinHeight() const;

        // Maximum Width
        /**
         * @param value in screen coordinates
         *
         * @note this attribute applies only to resizable windows.
         *
         * @throws std::invalid_argument value must be greater than the Window's minimum width
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setMaxWidth(int value);

        /**
         * @return the maximum resizable width in screen coordinates
         */
        [[nodiscard]] GPAPI int getMaxWidth() const;

        // Maximum Height
        /**
         * @param value in screen coordinates
         *
         * @note this attribute applies only to resizable windows.
         *
         * @throws std::invalid_argument value must be greater than the Window's minimum height
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setMaxHeight(int value);

        /**
         * @return the maximum resizable height in screen coordinates
         */
        [[nodiscard]] GPAPI int getMaxHeight() const;

        // Get & Set Methods
        /**
         * Sets the size of the window.
         *
         * @param width in screen coordinates
         * @param height in screen coordinates
         *
         * @throws std::invalid_argument width must be greater than 0
         * @throws std::invalid_argument height must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setSize(int width, int height);

        /**
         * Sets the minimum size of the window.
         *
         * @param minWidth in screen coordinates
         * @param minHeight in screen coordinates
         * @param maxWidth in screen coordinates
         * @param maxHeight in screen coordinates
         *
         * @note this attribute applies only to resizable windows.
         *
         * @throws std::invalid_argument minWidth must be greater than 0
         * @throws std::invalid_argument minHeight must be greater than 0
         * @throws std::invalid_argument maxWidth must be greater than minWidth
         * @throws std::invalid_argument height must be greater than minHeight
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);

        /**
         * Sets the minimum size of the window.
         *
         * @param minWidth in screen coordinates
         * @param minHeight in screen coordinates
         *
         * @note this attribute applies only to resizable windows.
         *
         * @throws std::invalid_argument minWidth must be greater than 0
         * @throws std::invalid_argument minHeight must be greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setMinSize(int minWidth, int minHeight);

        /**
         * Sets the maximum size of the window.
         *
         * @param maxWidth in screen coordinates
         * @param maxHeight in screen coordinates
         *
         * @note this attribute applies only to resizable windows.
         *
         * @throws std::invalid_argument maxWidth must be greater than the Window's minimum width
         * @throws std::invalid_argument height must be greater than the Window's minimum height
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setMaxSize(int maxWidth, int maxHeight);

        /**
         * Sets the position of the top-left of the window on the screen.
         *
         * @param xPos in screen coordinates
         * @param yPos in screen coordinates
         *
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setPosition(int xPos, int yPos);

        /**
         * Sets the aspect ratio of the window.
         * \n\n
         * The aspect ratio is specified as a numerator and denominator, corresponding to the width and height,
         * respectively. If you want a window to maintain its current aspect ratio, use its current size as the ratio.
         * \n\n
         *
         * Specify -1 to remove any aspect ratio settings.
         *
         * @throws std::invalid_argument numerator must be -1 or greater than 0
         * @throws std::invalid_argument denominator must be -1 or greater than 0
         * @throws std::runtime_error cannot set the attribute of a destroyed window
         */
        GPAPI void setAspectRatio(int numerator, int denominator);

        /**
         * Gets the current aspect ratio of the window.
         *
         * @return a struct representing the aspect ratio with (numerator, denominator)
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI AspectRatio getAspectRatio() const;

        /**
         * Gets the size, in screen coordinates, of the window frame.
         * \n\n
         * Decorated windows  have title bars and window frames around them. You can retrieve the sizes of these using this
         * method. The returned values are the distances, in screen coordinates, from the edges of the content area to the
         * corresponding edges of the full window. As they are distances and not coordinates, they are always zero or
         * positive.
         *
         * @return the size of the Window's frame as a struct with (left, top, right, bottom)
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI WindowFrame getFrameSize() const;

        /**
         * Gets the scale of the content on the window.
         * \n\n
         * The content scale is the ratio between the current DPI and the platform's default DPI.
         *
         * @return A struct representing the content scale with (xscale, yscale)
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI ContentScale getContentScale() const;

        /**
         * The size of the framebuffer for the window.
         *
         * @return a struct with (width, height) representing the dimensions, in pixels, of the framebuffer
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI FramebufferSize getFramebufferSize() const;

        /* Window Attributes -----------------------------------------------------------------------------------------*/

        /**
         * Gets whether the window is resizable by the user or not.
         * Defaults to False.
         *
         * @return whether the user can resize the window
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isResizable() const;

        /**
         * @param value whether the window is resizable by the user or not.
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setResizable(bool value);

        /**
         * Gets whether the window has window decorations.
         * Defaults to True.
         *
         * @return whether the window has decorations like a border, close widget, etc.
         *
         * @note an undecorated window will not be resizable by the user
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isDecorated() const;

        /**
         * @param value whether the window has window decorations like a border, close widget, etc.
         *
         * @note an undecorated window will not be resizable by the user
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setDecorated(bool value);

        /**
         * Gets whether the window is always on top.
         * Defaults to False.
         *
         * @return whether the window is always on top of other regular windows.
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isFloating() const;

        /**
         * @param value whether the window is always on top of other regular windows.
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setFloating(bool value);

        /**
         * Gets whether the window is automatically minimized when it loses focus.
         * Defaults to True.
         *
         * @return whether the window is automatically minimized when it loses focus.
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isAutoMinimized() const;

        /**
         * @param value whether the window is automatically minimized when it loses focus.
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setAutoMinimized(bool value);

        /**
         * Gets whether the window gains input focus when it is shown.
         * Defaults to True.
         *
         * @return whether calling Window::show() gives this window input focus
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isFocusedOnShow() const;

        /**
         * @param value whether calling Window::show() gives this window input focus
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setFocusedOnShow(bool value);

        /* Window State Methods --------------------------------------------------------------------------------------*/

        /**
         * Restores a minimized, maximized, or fullscreen window back to normal.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void restore();

        // Fullscreen
        /**
         * Makes the window enter fullscreen mode.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void fullscreen();

        /**
         * @return whether the window is in fullscreen mode.
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isFullscreen() const;

        // Minimize
        /**
         * Minimizes the window.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void minimize();

        /**
         * @return whether the window is in minimized mode.
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isMinimized() const;

        // Maximize
        /**
         * Maximizes the window.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void maximize();

        /**
         * @return whether the window is in maximized mode.
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isMaximized() const;

        // Visibility
        /**
         * Makes the window visible to the user.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void show();

        /**
         * Makes the window invisible to the user.
         *
         * @param hide: whether to hide/show the window
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void hide(bool hide = true);

        /**
         * @return whether the window is visible to the user.
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isVisible() const;

        // Input Focus
        /**
         * Gives the window input focus and brings it to the front.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void focus();

        /**
         * @return whether the window has input focus.
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool hasFocus() const;

        /**
         * Requests for the user's attention to the window.
         * \n\n
         * The system will highlight the Window, or on platforms where this is not supported, the application as a
         * whole. Once the user has given it attention, the system will automatically end the request.
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void requestAttention() const;

        /* Window Input Events ---------------------------------------------------------------------------------------*/

        /**
         * @return whether the mouse is hovering over the window.
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool isMouseHovering() const;

        /**
         * Gets the current position of the mouse
         *
         * @return a struct with the (x, y) position of the cursor in world coordinates
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI Point getMousePosition() const;

        /**
         * Normal makes the cursor visible and behave normally.\n
         * Hidden hides the cursor when it is over the window.\n
         * Disabled hides and grabs the cursor, providing virtual and unlimited cursor movement.
         *
         * @param mode one of "Normal", "Disabled", or "Hidden"
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setCursorMode(CursorMode mode) const;

        /**
         * @return whether the shift key is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkShiftKey() const;

        /**
         * @return whether the control key is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkControlKey() const;

        /**
         * @return whether the alt key is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkAltKey() const;

        /**
         * @return whether the super key is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkSuperKey() const;

        /**
         * @param key an int corresponding to the keycode
         *
         * @return whether the specified key is being pressed
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI int checkKey(int key) const;

        /**
         * @param button an int corresponding to the mouse button
         *
         * @return whether the specified mouse button is being pressed
         *
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkMouseButton(int button) const;

        /**
         * @return whether the left mouse button is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkLeftClick() const;

        /**
         * @return whether the middle mouse button is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkMiddleClick() const;

        /**
         * @return whether the right mouse button is being pressed
         * @throws std::runtime_error window has been destroyed
         */
        [[nodiscard]] GPAPI bool checkRightClick() const;

        /* Window Callback Functions ---------------------------------------------------------------------------------*/

        /**
         * Callback executed when the window is resized.
         * \n\n
         * It receives the new size, in screen coordinates, of the window when the window is resized.
         *
         * @code
         * void resizeCallback(Window *window, int width, int height) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setResizeCallback(std::function<void(Window *window, int width, int height)> callback);

        /**
         * Callback executed when the window is attempted to be closed.
         * \n\n
         *  It is called directly after the window's close flag has been set.
         *
         * @code
         * void closeCallback(Window *windowt) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setCloseCallback(std::function<void(Window *window)> callback);

        /**
         * Callback executed when the window is destroyed.
         * \n\n
         * It is called directly after Window::destroy().
         *
         * @code
         * void destroyCallback(Window *window) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setDestroyCallback(std::function<void(Window *window)> callback);

        /**
         * Callback executed when the window is moved.
         * \n\n
         * It receives the new position, in screen coordinates, of the upper-left corner of the window.
         *
         * @code
         * void positionCallback(Window *window, int xPos, int yPos) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setPositionCallback(std::function<void(Window *window, int xPos, int yPos)> callback);

        /**
         * Callback executed when the window is minimized.
         * \n\n
         * It receives a bool representing whether the window was minimized or restored to normal.
         *
         * @code
         * void minimizeCallback(Window *window, bool minimized) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setMinimizeCallback(std::function<void(Window *window, bool minimized)> callback);

        /**
         * Callback executed when the window is maximized.
         * \n\n
         * It receives a bool representing whether the window was maximized or restored to normal.
         *
         * @code
         * void maximizeCallback(Window *window, bool maximized) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setMaximizeCallback(std::function<void(Window *window, bool maximized)> callback);

        /**
         * Callback executed when the window gains input focus.
         * \n\n
         * It receives a bool representing whether the window gained or lost input focus.\n
         * On most platforms, this means that the callback is called when the user minimizes a window,
         * clicks on a window to make it active, or other similar actions.
         *
         * @code
         * void focusCallback(Window *window, bool focused) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setFocusCallback(std::function<void(Window *window, bool focused)> callback);

        /**
         * Callback executed when the window needs refreshing.
         * \n\n
         * On most platforms, this is called when the size of the window changes through resizing, minimizing,
         * maximizing, and entering fullscreen.
         *
         * @code
         * void refreshCallback(Window *window) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI  void setRefreshCallback(std::function<void(Window *window)> callback);

        /**
         * Callback executed when the Window's content scale changes.
         * \n\n
         * It receives the new content scale of the window.
         *
         * @code
         * void contentScaleCallback(Window *window, float xScale, float yScale) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setContentScaleCallback(std::function<void(Window *window, float xScale, float yScale)> callback);

        /**
         * Callback executed when the Window's framebuffer size changes.
         * \n\n
         * It receives the new size of the window's framebuffer.
         *
         * @code
         * void framebufferSizeCallback(Window *window, int width, int height) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setFramebufferSizeCallback(std::function<void(Window *window, int width, int height)> callback);

        /**
         * Callback executed when the mouse moves.
         * \n\n
         * The callback function receives the position of the mouse.
         *
         * @code
         * void mouseMotionCallback(Window *window, float xPos, float yPos) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setMouseMotionCallback(std::function<void(Window *window, float xPos, float yPos)> callback);

        /**
         * Callback executed when the mouse enters/exits the window.
         * \n\n
         * The callback function receives a bool representing whether the mouse entered or exited a window.
         *
         * @code
         * void mouseEnterCallback(Window *window, bool entered) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setMouseEnterCallback(std::function<void(Window *window, bool entered)> callback);

        /**
         * Callback executed when the mouse scrolls.
         * \n\n
         * The callback function receives floats representing the x and y components of the current scroll.
         *
         * @code
         * void scrollCallback(Window *window, float xScroll, float yScroll) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setScrollCallback(std::function<void(Window *window, float xScroll, float yScroll)> callback);

        /**
         * Callback executed when a key is pressed.
         * \n\n
         * It receives an int representing if the key was released (0), pressed (1), or repeated (2)
         *
         * @code
         * void keyCallback(Window *window, int action) {
         *      // code here
         * }
         * @endcode
         *
         * @param key an int corresponding to the key for which to set the callback
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setKeyCallback(int key, std::function<void(Window *window, int action)> callback);

        /**
         * Callback executed when a mouse button is pressed.
         * \n\n
         * It receives a bool representing if the mouse button was pressed.
         *
         * @code
         * void mouseButtonCallback(Window *window, bool pressed) {
         *      // code here
         * }
         * @endcode
         *
         * @param button an int corresponding to the mouse button for which to set the callback
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setMouseButtonCallback(int button, std::function<void(Window *window, bool pressed)> callback);

        /**
         * Callback executed when the left mouse button is clicked.
         * \n\n
         * The callback function receives a bool representing if the mouse button was pressed.
         *
         * @code
         * void leftClickCallback(Window *window, bool pressed) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setLeftClickCallback(std::function<void(Window *window, bool pressed)> callback);

        /**
         * Callback executed when the middle mouse button is clicked.
         * \n\n
         * The callback function receives a bool representing if the mouse button was pressed.
         *
         * @code
         * void middleClickCallback(Window *window, bool pressed) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setMiddleClickCallback(std::function<void(Window *window, bool pressed)> callback);

        /**
         * Callback executed when the right mouse button is clicked.
         * \n\n
         * The callback function receives a bool representing if the mouse button was pressed.
         *
         * @code
         * void rightClickCallback(Window *window, bool pressed) {
         *      // code here
         * }
         * @endcode
         *
         * @param callback the callback function
         *
         * @throws std::runtime_error window has been destroyed
         */
        GPAPI void setRightClickCallback(std::function<void(Window *window, bool pressed)> callback);


        /* Static Methods --------------------------------------------------------------------------------------------*/

        /**
         * Updates all the windows currently active.
         */
        GPAPI static void updateAll();

        /**
         * Destroys all active windows.
         */
        GPAPI static void destroyAll();

    private:
        int m_xPos;
        int m_yPos;

        int m_MinWidth = 0;
        int m_MinHeight = 0;
        int m_MaxWidth = INT_MAX;
        int m_MaxHeight = INT_MAX;

        int m_WindowedWidth;
        int m_WindowedHeight;
        int m_WindowedXPos;
        int m_WindowedYPos;

        bool m_IsDestroyed = false;
        int m_KeyModifiers = 0;  // check if the shift, control, alt, and super keys are pressed

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

        #if GP_USING_GLFW

        GLFWwindow *m_Window = nullptr;

        #endif

        static std::vector<Window *> s_Instances;

        GPAPI void super();

        // Callback Functions

        GPAPI void _onResize(int width, int height);

        GPAPI void _onClose();

        GPAPI void _onDestroy();

        GPAPI void _onMove(int xPos, int yPos);

        GPAPI void _onMinimize(bool iconified);

        GPAPI void _onMaximize(bool maximized);

        GPAPI void _onFocus(bool focused);

        GPAPI void _onRefreshRequired();

        GPAPI void _onContentScale(float xScale, float yScale);

        GPAPI void _onFramebufferSize(int width, int height);

        GPAPI void _onMouseMotion(float xPos, float yPos);

        GPAPI void _onMouseEnter(bool entered);

        GPAPI void _onScroll(float xScroll, float yScroll);

        GPAPI void _onKeyPress(int key, int scancode, int action, int mods);

        GPAPI void _onMousePress(int button, int action, int mods);

        GPAPI void _swapBuffers() const;

        GPAPI void _destroy() const;

        GPAPI void _updateSize() const override;

        GPAPI void _updatePosition() const;

        GPAPI void _updateSizeLimits() const;

        GPAPI void _updateAspectRatio(int numerator, int denominator) const;

        GPAPI void _fullscreen() const;

        GPAPI void _unfullscreen(int width, int height, int xPos, int yPos) const;

        GPAPI void _restore() const;

        GPAPI void _setKeyCallback() const;

        GPAPI void _setMouseButtonCallback() const;
    };
}
