#pragma once

#include "Platform/Independent/BaseWindow.h"

namespace gp {
    class GPAPI Window final : public BaseWindow {

    public:
        explicit Window(const WindowConfig &config);

        ~Window() override;

        #if GP_USING_GLFW

        GLFWwindow *getWindowGLFW();

        #endif

        // Window Attributes
        bool isResizable() const override;

        void setResizable(bool value) override;

        bool isDecorated() const override;

        void setDecorated(bool value) override;

        bool isFloating() const override;

        void setFloating(bool value) override;

        bool isAutoMinimized() const override;

        void setAutoMinimized(bool value) override;

        bool isFocusedOnShow() const override;

        void setFocusedOnShow(bool value) override;

        // Window Get & Set Methods

        WindowFrame getFrameSize() const override;

        ContentScale getContentScale() const override;

        FramebufferSize getFramebufferSize() const override;

        // Window Input Events

        bool isMouseHovering() const override;

        bool checkShiftKey() const override;

        bool checkControlKey() const override;

        bool checkAltKey() const override;

        bool checkSuperKey() const override;

        int checkKey(int key) const override;

        // Window States

        bool isFullscreen() const override;

        bool isMaximized() const override;

        bool isMinimized() const override;

        bool isVisible() const override;

        bool hasFocus() const override;

        void requestAttention() const override;


    private:
        #if GP_USING_GLFW
        GLFWwindow *m_Window = nullptr;
        #endif

        bool _isClosed() const override;

        void _update() const override;

        void _destroy() const override;

        void _updateSize() const override;

        void _updateTitle() const override;

        void _updatePosition() const override;

        void _updateBackground() const override;

        void _updateSizeLimits() const override;

        void _updateAspectRatio(int numerator, int denominator) const override;

        // Window State Methods

        void _fullscreen() const override;

        void _unfullscreen(int width, int height, int xPos, int yPos) const override;

        void _maximize() const override;

        void _minimize() const override;

        void _restore() const override;

        void _hide() const override;

        void _show() const override;

        void _focus() const override;

        // Callback Functions

        void _setResizeCallback() const override;

        void _setCloseCallback() const override;

        void _setPositionCallback() const override;

        void _setMinimizeCallback() const override;

        void _setMaximizeCallback() const override;

        void _setFocusedCallback() const override;

        void _setRefreshCallback() const override;

        void _setContentScaleCallback() const override;

        void _setFramebufferSizeCallback() const override;

        void _setKeyCallback() const override;
    };
}
