#include "CameraController.h"

#if (GP_LOG_CAMERA_CONTROLLER != true) and (GP_LOG_CAMERA_CONTROLLER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CAMERA_CONTROLLER
#endif

#if !GP_VALUE_CHECK_CAMERA_CONTROLLER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


namespace gp {
    CameraController::CameraController(Window* window)
            : m_Window(window),
            m_Camera(&window->getCamera()) {

    }

    void CameraController::enableMovement(bool value) {
        m_EnableMovement = value;
    }

    void CameraController::enableRotation(bool value) {
        m_EnableRotation = value;
    }

    void CameraController::enableZoom(bool value) {
        m_EnableZoom = value;
    }

    void CameraController::invertMovement(bool value) {
        m_InvertMovement = value ? -1.0f : 1.0f;
    }

    void CameraController::invertRotation(bool value) {
        m_InvertRotation = value ? -1.0f : 1.0f;
    }

    void CameraController::setHorizontalSpeed(float value) {
        m_HorizontalSpeed = value;
    }

    float CameraController::getHorizontalSpeed() const {
        return m_HorizontalSpeed;
    }

    void CameraController::setVerticalSpeed(float value) {
        m_VerticalSpeed = value;
    }

    float CameraController::getVerticalSpeed() const {
        return m_VerticalSpeed;
    }

    void CameraController::setRotateSpeed(float value) {
        m_RotateSpeed = value;
    }

    float CameraController::getRotateSpeed() const {
        return m_RotateSpeed;
    }

    void CameraController::setZoomSpeed(float value) {
        m_ZoomSpeed = value;
    }

    float CameraController::getZoomSpeed() const {
        return m_ZoomSpeed;
    }

    void CameraController::useWASD() {
        m_UpKey = GP_KEY_W;
        m_DownKey = GP_KEY_S;
        m_LeftKey = GP_KEY_A;
        m_RightKey = GP_KEY_D;
    }

    void CameraController::useArrows() {
        m_UpKey = GP_KEY_UP;
        m_DownKey = GP_KEY_DOWN;
        m_LeftKey = GP_KEY_LEFT;
        m_RightKey = GP_KEY_RIGHT;
    }

    void CameraController::setMovementKeys(int up, int left, int down, int right) {
        m_UpKey = up;
        m_LeftKey = left;
        m_DownKey = down;
        m_RightKey = right;
    }

    void CameraController::setRotationKeys(int clockwise, int anticlockwise) {
        m_CWKey = clockwise;
        m_CCWKey = anticlockwise;
    }

    void CameraController::setZoomKeys(int in, int out) {
        m_ZoomInKey = in;
        m_ZoomOutKey = out;
    }

    void CameraController::update() {
        if (m_EnableMovement) {
            if (m_Window->checkKey(m_UpKey)) {
                m_Camera->move(0, m_VerticalSpeed * m_InvertMovement);
            }
            else if (m_Window->checkKey(m_LeftKey)) {
                m_Camera->move(-m_HorizontalSpeed * m_InvertMovement, 0);
            }
            else if (m_Window->checkKey(m_DownKey)) {
                m_Camera->move(0, -m_VerticalSpeed * m_InvertMovement);
            }
            else if (m_Window->checkKey(m_RightKey)) {
                m_Camera->move(m_HorizontalSpeed * m_InvertMovement, 0);
            }
        }

        if (m_EnableRotation) {
            if (m_Window->checkKey(m_CWKey)) {
                m_Camera->rotate(-m_RotateSpeed * m_InvertRotation);
            }
            else if (m_Window->checkKey(m_CCWKey)) {
                m_Camera->rotate(m_RotateSpeed * m_InvertRotation);
            }
        }

        if (m_EnableZoom) {
            if (m_Window->checkKey(m_ZoomInKey)) {
                m_Camera->zoom(1 + m_ZoomSpeed);
            }
            else if (m_Window->checkKey(m_ZoomOutKey)) {
                m_Camera->zoom(1 - m_ZoomSpeed);
            }
        }
    }
}
