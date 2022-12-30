#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#if (GP_LOG_CAMERA != true) and (GP_LOG_CAMERA <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CAMERA
#endif

#if !GP_VALUE_CHECK_CAMERA
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"

namespace gp {
    Camera::Camera(float left, float right, float bottom, float top)
            : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
            m_ViewMatrix(1.0f),
            m_ProjectionViewMatrix(m_ProjectionMatrix * m_ViewMatrix),
            m_InverseProjectionViewMatrix(glm::inverse(m_ProjectionViewMatrix)),
            m_Left(left),
            m_Right(right),
            m_Bottom(bottom),
            m_Top(top) {
        GP_CORE_INFO("Initializing Orthographic Camera");
    }

    void Camera::setProjection(float left, float right, float bottom, float top) {
        m_Left = left;
        m_Right = right;
        m_Bottom = bottom;
        m_Top = top;

        m_ProjectionMatrix = glm::ortho(left / m_Zoom, right / m_Zoom,
                                        bottom / m_Zoom, top / m_Zoom, -1.0f, 1.0f);
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_InverseProjectionViewMatrix = glm::inverse(m_ProjectionViewMatrix);
    }

    void Camera::update() {
        auto transform = glm::translate(glm::mat4(1.0f), m_Position);
        transform *= glm::rotate(glm::mat4(1.0f), m_RotationRadians, {0, 0, 1});

        m_ViewMatrix = glm::inverse(transform);
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_InverseProjectionViewMatrix = glm::inverse(m_ProjectionViewMatrix);
    }

    void Camera::move(float dx, float dy) {
        m_Position.x += dx;
        m_Position.y += dy;

        update();
    }

    void Camera::setX(float x) {
        move(x - m_Position.x, 0);
    }

    float Camera::getX() const {
        return m_Position.x;
    }

    void Camera::setY(float y) {
        move(0, y - m_Position.y);
    }

    float Camera::getY() const {
        return m_Position.y;
    }

    void Camera::setPosition(float x, float y) {
        move(x - m_Position.x, y - m_Position.y);
    }

    Point Camera::getPosition() const {
        return {m_Position.x, m_Position.y};
    }

    void Camera::rotate(float angle) {
        m_RotationDegrees += angle;
        m_RotationRadians = m_RotationDegrees / 57.2957795131f;

        update();
    }

    void Camera::setRotation(float angle) {
        rotate(angle - m_RotationDegrees);
    }

    float Camera::getRotation() const {
        return m_RotationDegrees;
    }

    void Camera::zoom(float value) {
        m_Zoom *= value;

        setProjection(m_Left, m_Right, m_Bottom, m_Top);
    }

    void Camera::setZoom(float value) {
        zoom(value / m_Zoom);
    }

    float Camera::getZoom() const {
        return m_Zoom;
    }
}
