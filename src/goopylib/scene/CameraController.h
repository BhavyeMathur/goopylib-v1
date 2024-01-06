#pragma once

#include "src/goopylib/core/Window.h"
#include "src/platform/events/KeyboardCodes.h"


namespace gp {

    /**
     * Controller class that automatically manages camera movement, rotation, and zoom.\n
     * This is a helper class that wraps around a Window's camera and provides basic but quick functionality.
     */
    class CameraController {

    public:
        /**
         * Controller class that automatically manages camera movement, rotation, and zoom.\n
         * This is a helper class that wraps around a Window's camera and provides basic but quick functionality.
         *
         * @param window the window to use
         */
        GPAPI CameraController(Window* window);

        GPAPI CameraController (const CameraController&) = delete;

        /**
         * Updates the controller. Call this method in the mainloop.
         */
        GPAPI void update();

        /**
         * Enables automatic camera movement when the control keys are pressed.
         * @param value whether to enable or disable movement
         */
        GPAPI void enableMovement(bool value);

        /**
         * Enables automatic camera rotation when the control keys are pressed.
         * @param value whether to enable or disable rotation
         */
        GPAPI void enableRotation(bool value);

        /**
         * Enables automatic camera zooming when the control keys are pressed.
         * @param value whether to enable or disable zooming
         */
        GPAPI void enableZoom(bool value);

        /**
         * Inverts camera movement.
         * @param value whether to invert the movement
         */
        GPAPI void invertMovement(bool value);

        /**
         * Inverts camera rotation.
         * @param value whether to invert the rotation
         */
        GPAPI void invertRotation(bool value);

        /**
         * Sets the horizontal movement speed of the camera.
         * @param value the horizontal speed
         */
        GPAPI void setHorizontalSpeed(float value);

        /**
         *
         * @return the horizontal movement speed of the camera
         */
        [[nodiscard]] GPAPI float getHorizontalSpeed() const;

        /**
         * Sets the vertical movement speed of the camera.
         * @param value the vertical speed
         */
        GPAPI void setVerticalSpeed(float value);

        /**
         *
         * @return the vertical movement speed of the camera
         */
        [[nodiscard]] GPAPI float getVerticalSpeed() const;

        /**
         * Sets the rotational speed of the camera.
         * @param value the rotate speed
         */
        GPAPI void setRotateSpeed(float value);

        /**
         *
         * @return the rotational speed of the camera
         */
        [[nodiscard]] GPAPI float getRotateSpeed() const;

        /**
         * Sets the zoom speed of the camera.
         * @param value the zoom speed
         */
        GPAPI void setZoomSpeed(float value);

        /**
         *
         * @return the zoom speed of the camera
         */
        [[nodiscard]] GPAPI float getZoomSpeed() const;

        /**
         * Binds the WASD keys for camera movement.
         */
        GPAPI void useWASD();

        /**
         * Binds the arrow keys for camera movement.
         */
        GPAPI void useArrows();

        /**
         * Sets the keys used for camera movement.
         *
         * @param up key to use for moving up
         * @param left key to use for moving left
         * @param down key to use for moving down
         * @param right key to use for moving right
         */
        GPAPI void setMovementKeys(int up, int left, int down, int right);

        /**
         * Sets the keys used for camera rotation.
         *
         * @param clockwise key to use for clockwise rotation
         * @param anticlockwise key to use for anticlockwise rotation
         */
        GPAPI void setRotationKeys(int clockwise, int anticlockwise);

        /**
         * Sets the keys used for camera zooming.
         *
         * @param in key to use for zooming in
         * @param out key to use for zooming out
         */
        GPAPI void setZoomKeys(int in, int out);

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
