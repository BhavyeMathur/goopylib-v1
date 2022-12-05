#pragma once

#include "Platform/Independent/BaseWindow.h"

namespace gp {
    class Window final : public BaseWindow {

    public:
        explicit Window(const WindowConfig &config);

        ~Window() override;

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

        // Window States
        bool isFullscreen() const override;

        bool isMaximized() const override;

        bool isMinimized() const override;

        bool isVisible() const override;

    private:
        #if GP_USING_GLFW
        GLFWwindow *m_Window;
        #endif

        bool _isClosed() const override;

        void _update() const override;

        void _destroy() const override;

        void _updateSize() const override;

        void _updatePosition() const override;

        void _updateTitle() const override;

        void _updateSizeLimits() const override;

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
    };
}
