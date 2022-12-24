#pragma once

#include "pch.h"

namespace gp {
    class Camera {

        friend class Renderer;

    public:
        Camera(float left, float right, float bottom, float top);

        ~Camera() = default;

        void setProjection(float left, float right, float bottom, float top);

        void move(float dx, float dy);

        void setPosition(float x, float y);

        Point getPosition() const;

        void rotate(float angle);

        void setRotation(float angle);

        float getRotation() const;

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionViewMatrix;

        glm::vec3 m_Position = { 0, 0, 0 };
        float m_RotationDegrees = 0;
        float m_RotationRadians = 0;

        void update();
    };
}
