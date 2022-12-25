#pragma once

#include "src/goopylib/core/Window.h"
#include "src/goopylib/events/KeyboardCodes.h"


namespace gp {

    class CameraController {

    public:
        CameraController(Window& camera);

        void update();

        void enableMovement(bool value);

        void enableRotation(bool value);

        void enableZoom(bool value);

        void invertMovement(bool value);

        void invertRotation(bool value);

        void setHorizontalSpeed(float value);

        float getHorizontalSpeed() const;

        void setVerticalSpeed(float value);

        float getVerticalSpeed() const;

        void setRotateSpeed(float value);

        float getRotateSpeed() const;

        void setZoomSpeed(float value);

        float getZoomSpeed() const;

        void useWASD();

        void useArrows();

        void setMovementKeys(int up, int left, int down, int right);

        void setRotationKeys(int clockwise, int anticlockwise);

        void setZoomKeys(int in, int out);

    private:
        Camera* m_Camera;
        const Window* m_Window;

        bool m_EnableMovement = true;
        bool m_EnableRotation = true;
        bool m_EnableZoom = true;

        float m_InvertMovement = 1.0f;
        float m_InvertRotation = 1.0f;

        float m_VerticalSpeed = 5;
        float m_HorizontalSpeed = 5;
        float m_RotateSpeed = 3;
        float m_ZoomSpeed = 0.05;

        int m_UpKey = GP_KEY_W;
        int m_DownKey = GP_KEY_S;
        int m_LeftKey = GP_KEY_A;
        int m_RightKey = GP_KEY_D;
        int m_CWKey = GP_KEY_E;
        int m_CCWKey = GP_KEY_Q;
        int m_ZoomInKey = GP_KEY_EQUAL;
        int m_ZoomOutKey = GP_KEY_MINUS;
    };
}
