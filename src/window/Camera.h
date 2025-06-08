#pragma once

#include "gp.h"
#include "maths/gpmath.h"

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
    class GPAPI Camera {

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
        Camera(float left, float right, float bottom, float top);

        Camera (const Camera&) = delete;

        ~Camera() = default;

        /**
         * Sets an orthographic projection for the camera
         *
         * @param left left clipping plane
         * @param right right clipping plane
         * @param bottom bottom clipping plane
         * @param top top clipping plane
         */
        void setProjection(float left, float right, float bottom, float top);

        /**
         * Gets the currently visible camera frame with left, right, bottom, and top values
         */
        [[nodiscard]] CameraFrame getVisibleFrame() const;

        /**
         * Gets the camera projection frame (zoom=1) with left, right, bottom, and top values
         */
        [[nodiscard]] CameraFrame getProjectionFrame() const;

        /**
         * Gets the currently visible camera frame width
         */
        [[nodiscard]] float getVisibleWidth() const;

        /**
         * Gets the currently visible camera frame height
         */
        [[nodiscard]] float getVisibleHeight() const;

        /**
         * Gets the camera projection (zoom=1) width
         */
        [[nodiscard]] float getProjectionWidth() const;

        /**
         * Gets the camera projection (zoom=1) height
         */
        [[nodiscard]] float getProjectionHeight() const;

        /**
         * Gets the currently visible camera frame size as width, height
         */
        [[nodiscard]] CameraFrameSize getVisibleSize() const;

        /**
         * Gets the camera projection (zoom=1) size as width, height
         */
        [[nodiscard]] CameraFrameSize getProjectionSize() const;

        /**
         * Moves (translate) the camera's position
         *
         * @param dx change in x position
         * @param dy change in y position
         */
        void move(float dx, float dy);

        /**
         * Sets the x-position of the camera
         * @param x the new x-position
         */
        void setX(float x);

        /**
         *
         * @return the x-position of the camera
         */
        [[nodiscard]] float getX() const;

        /**
         * Sets the y-position of the camera
         * @param y the new y-position
         */
        void setY(float y);

        /**
         *
         * @return the y-position of the camera
         */
        [[nodiscard]] float getY() const;

        /**
         * Sets the position of the camera
         *
         * @param x the new x-position
         * @param y the new y-position
         */
        void setPosition(float x, float y);

        /**
         *
         * @return the position of the camera as a struct with (x, y)
         */
        [[nodiscard]] Point getPosition() const;

        /**
         * Rotates the camera
         * @param angle in degrees
         */
        void rotate(float angle);

        /**
         * Sets the rotation of the camera
         * @param angle in degrees
         */
        void setRotation(float angle);

        /**
         * Gets the rotation of the camera
         * @return angle in degrees
         */
        [[nodiscard]] float getRotation() const;

        /**
         * Zooms the camera in. A value less than 1 zooms the camera out.
         * @param value zoom amount
         */
        void zoom(float value);

        /**
         * Sets the zoom of the camera. Defaults to 1.
         * @param value zoom amount
         */
        void setZoom(float value);

        /**
         *
         * @return the zoom level of the camera
         */
        [[nodiscard]] float getZoom() const;

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

        void _update();
    };
}
