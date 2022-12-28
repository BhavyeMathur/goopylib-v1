#pragma once

#include "gp.h"
#include "goopylib/maths/gpmath.h"

#include <glm/detail/type_mat4x4.hpp>


namespace gp {
    class Camera {

        friend class Renderer;
        friend class Window;

    public:
        Camera(float left, float right, float bottom, float top);

        ~Camera() = default;

        void setProjection(float left, float right, float bottom, float top);

        void move(float dx, float dy);

        void setPosition(float x, float y);

        [[nodiscard]] [[nodiscard]] Point getPosition() const;

        void rotate(float angle);

        void setRotation(float angle);

        [[nodiscard]] [[nodiscard]] float getRotation() const;

        void zoom(float value);

        void setZoom(float value);

        [[nodiscard]] [[nodiscard]] float getZoom() const;

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionViewMatrix;
        glm::mat4 m_InverseProjectionViewMatrix;

        float m_Left;
        float m_Right;
        float m_Bottom;
        float m_Top;

        glm::vec3 m_Position = {0, 0, 0};
        float m_RotationDegrees = 0;
        float m_RotationRadians = 0;
        float m_Zoom = 1;

        void update();
    };
}
