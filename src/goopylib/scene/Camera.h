#pragma once

#include "gp.h"
#include "src/goopylib/maths/gpmath.h"

#include <glm/detail/type_mat4x4.hpp>


namespace gp {
    struct CameraFrame {
        float left;
        float top;
        float right;
        float bottom;
    };

    struct CameraFrameSize {
        float width;
        float height;
    };

    /**
     * An orthographic camera associated with a Window.
     */
    class Camera {

        friend class Window;
        friend class Renderer;
        friend class RenderingManager;

    public:
        /**
         * An orthographic camera associated with a Window.
         *
         * @param left left clipping plane
         * @param right right clipping plane
         * @param bottom bottom clipping plane
         * @param top top clipping plane
         */
        GPAPI Camera(float left, float right, float bottom, float top);

        GPAPI Camera (const Camera&) = delete;

        GPAPI ~Camera() = default;

        /**
         * Sets an orthographic projection for the camera
         *
         * @param left left clipping plane
         * @param right right clipping plane
         * @param bottom bottom clipping plane
         * @param top top clipping plane
         */
        GPAPI void setProjection(float left, float right, float bottom, float top);

        /**
         * Gets the currently visible camera frame with left, right, bottom, and top values
         */
        [[nodiscard]] GPAPI CameraFrame getVisibleFrame() const;

        /**
         * Gets the camera projection frame (zoom=1) with left, right, bottom, and top values
         */
        [[nodiscard]] GPAPI CameraFrame getProjectionFrame() const;

        /**
         * Gets the currently visible camera frame width
         */
        [[nodiscard]] GPAPI float getVisibleWidth() const;

        /**
         * Gets the currently visible camera frame height
         */
        [[nodiscard]] GPAPI float getVisibleHeight() const;

        /**
         * Gets the camera projection (zoom=1) width
         */
        [[nodiscard]] GPAPI float getProjectionWidth() const;

        /**
         * Gets the camera projection (zoom=1) height
         */
        [[nodiscard]] GPAPI float getProjectionHeight() const;

        /**
         * Gets the currently visible camera frame size as width, height
         */
        [[nodiscard]] GPAPI CameraFrameSize getVisibleSize() const;

        /**
         * Gets the camera projection (zoom=1) size as width, height
         */
        [[nodiscard]] GPAPI CameraFrameSize getProjectionSize() const;

        /**
         * Moves (translate) the camera's position
         *
         * @param dx change in x position
         * @param dy change in y position
         */
        GPAPI void move(float dx, float dy);

        /**
         * Sets the x-position of the camera
         * @param x the new x-position
         */
        GPAPI void setX(float x);

        /**
         *
         * @return the x-position of the camera
         */
        [[nodiscard]] GPAPI float getX() const;

        /**
         * Sets the y-position of the camera
         * @param y the new y-position
         */
        GPAPI void setY(float y);

        /**
         *
         * @return the y-position of the camera
         */
        [[nodiscard]] GPAPI float getY() const;

        /**
         * Sets the position of the camera
         *
         * @param x the new x-position
         * @param y the new y-position
         */
        GPAPI void setPosition(float x, float y);

        /**
         *
         * @return the position of the camera as a struct with (x, y)
         */
        [[nodiscard]] GPAPI Point getPosition() const;

        /**
         * Rotates the camera
         * @param angle in degrees
         */
        GPAPI void rotate(float angle);

        /**
         * Sets the rotation of the camera
         * @param angle in degrees
         */
        GPAPI void setRotation(float angle);

        /**
         * Gets the rotation of the camera
         * @return angle in degrees
         */
        [[nodiscard]] GPAPI float getRotation() const;

        /**
         * Zooms the camera in. A value less than 1 zooms the camera out.
         * @param value zoom amount
         */
        GPAPI void zoom(float value);

        /**
         * Sets the zoom of the camera. Defaults to 1.
         * @param value zoom amount
         */
        GPAPI void setZoom(float value);

        /**
         *
         * @return the zoom level of the camera
         */
        [[nodiscard]] GPAPI float getZoom() const;

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

        GPAPI void _update();
    };
}
