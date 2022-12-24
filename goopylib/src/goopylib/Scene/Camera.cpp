#include "Camera.h"

namespace gp {
    Camera::Camera(float left, float right, float bottom, float top)
            : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
            m_ViewMatrix(1.0f),
            m_ProjectionViewMatrix(m_ProjectionMatrix * m_ViewMatrix),
            m_InverseProjectionViewMatrix(glm::inverse(m_ProjectionViewMatrix)) {
    }

    void Camera::setProjection(float left, float right, float bottom, float top) {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
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
}
