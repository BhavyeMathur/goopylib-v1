#define GP_LOGGING_LEVEL 3

#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

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

    CameraFrame Camera::getVisibleFrame() const {
        return {(m_Left + m_Position.x) / m_Zoom, (m_Right + m_Position.x) / m_Zoom,
                (m_Bottom + m_Position.y) / m_Zoom, (m_Top + m_Position.y) / m_Zoom};
    }

    CameraFrame Camera::getProjectionFrame() const {
        return {m_Left, m_Right, m_Bottom, m_Top};
    }

    float Camera::getVisibleWidth() const {
        return abs(m_Left - m_Right) / m_Zoom;
    }

    float Camera::getVisibleHeight() const {
        return abs(m_Top - m_Bottom) / m_Zoom;
    }

    float Camera::getProjectionWidth() const {
        return abs(m_Left - m_Right);
    }

    float Camera::getProjectionHeight() const {
        return abs(m_Top - m_Bottom);
    }

    CameraFrameSize Camera::getVisibleSize() const {
        return {getVisibleWidth(), getVisibleHeight()};
    }

    CameraFrameSize Camera::getProjectionSize() const {
        return {getProjectionWidth(), getProjectionHeight()};
    }

    void Camera::_update() {
        auto transform = glm::translate(glm::mat4(1.0f), m_Position);
        transform *= glm::rotate(glm::mat4(1.0f), m_RotationRadians, {0, 0, 1});

        m_ViewMatrix = glm::inverse(transform);
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
        m_InverseProjectionViewMatrix = glm::inverse(m_ProjectionViewMatrix);
    }

    void Camera::move(float dx, float dy) {
        m_Position.x += dx;
        m_Position.y += dy;

        _update();
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

        _update();
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
