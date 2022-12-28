#pragma once

#include "Point.h"
#include "goopylib/core/Window.h"

#include <cfloat>


namespace gp {
    struct Scale {
        float xscale;
        float yscale;
    };
}

namespace gp {
    /**
     * Generic base class for renderables
     */
    class Renderable {

        friend class Renderer;

    public:
        /**
         * Draws the object to a window
         *
         * @param window the Window to draw to
         *
         * @throws std::runtime_error the window has been destroyed
         */
        void draw(Window *window);

        /**
         * Destroys and undraws the object
         */
        void destroy();

        /**
         *
         * @return whether the object has been drawn
         */
        [[nodiscard]] bool isDrawn() const;

        /* Getters & Setters */

        // Anchor
        /**
         * Sets the anchor (center) of the object to the specified coordinates
         *
         * @param x in world coordinates
         * @param y in world coordinates
         */
        void setAnchor(float x, float y);

        /**
         * Resets the anchor of the object to its center (average of its vertices)
         */
        void resetAnchor();

        // Position
        /**
         * Moves (translates) the object across the screen
         *
         * @param dx in world coordinates
         * @param dy in world coordinates
         */
        void move(float dx, float dy);

        /**
         * Sets the x position of the object
         * @param x in world coordinates
         */
        void setX(float x);

        /**
         *
         * @return the x position of the object's anchor in world coordinates
         */
        [[nodiscard]] float getX() const;

        /**
         * Sets the y position of the object
         * @param y in world coordinates
         */
        void setY(float y);

        /**
         *
         * @return the y position of the object's anchor in world coordinates
         */
        [[nodiscard]] float getY() const;

        /**
         * Sets the position of the object by moving its anchor
         * @param x in world coordinates
         * @param y in world coordinates
         */
        void setPosition(float x, float y);

        /**
         *
         * @return a struct with the (x, y) position of the object's anchor
         */
        [[nodiscard]] Point getPosition() const;

        // Rotation
        /**
         * Rotates the object
         * @param angle in degrees
         */
        void rotate(float angle);

        /**
         * Sets the rotation of the object
         * @param angle in degrees
         */
        void setRotation(float angle);

        /**
         *
         * @return the rotation of the object in degrees
         */
        [[nodiscard]] float getRotation() const;

        // Scale
        /**
         * Scales the object
         * @param factor the scale amount
         */
        void scale(float factor);

        /**
         * Scales the object
         * @param xfactor x-component scale amount
         * @param yfactor y-component scale amount
         */
        void scale(float xfactor, float yfactor);

        /**
         * Sets the x-component scale of the object
         * @param factor the scale amount
         */
        void setScaleX(float factor);

        /**
         * Sets the y-component scale of the object
         * @param factor the scale amount
         */
        void setScaleY(float factor);

        /**
         * Sets the x and y scale of the object
         * @param factor the scale amount
         */
        void setScale(float factor);

        /**
         * Sets the x and y scale of the object
         * @param xfactor the x-component scale amount
         * @param yfactor the y-component scale amount
         */
        void setScale(float xfactor, float yfactor);

        /**
         *
         * @return a struct with the (x, y) components of the object's scale
         */
        [[nodiscard]] Scale getScale() const;

        // Dimensions
        /**
         * Sets the width of the object by resizing it
         * @param width in screen coordinates
         */
        void setWidth(float width);

        /**
         *
         * @return in screen coordinates
         */
        [[nodiscard]] float getWidth() const;

        /**
         * Sets the height of the object by resizing it
         * @param height in screen coordinates
         */
        void setHeight(float height);

        /**
         *
         * @return in screen coordinates
         */
        [[nodiscard]] float getHeight() const;

        /**
         * Sets the dimensions of the object by resizing it
         * @param width in screen coordinates
         * @param height in screen coordinates
         */
        void setSize(float width, float height);

        // Visibility
        /**
         * Sets the transparency of the object
         *
         * @param value between 0 (transparent) and 1 (opaque)
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        virtual void setTransparency(float value) = 0;

        /**
         * Hides the object from the window
         * @param hide whether to hide or show
         */
        void hide(bool hide = true);

        /**
         * Unhides the object if it was hidden
         */
        void show();

        /**
         *
         * @return whether the object is hidden
         */
        [[nodiscard]] bool isHidden() const;

        /* Methods */

        /**
         * Checks if the object's rectangular bounding box contains a point
         *
         * @param point the coordinates in world space
         *
         * @return whether the rectangular bounding box contains the point
         */
        [[nodiscard]] bool boxContains(Point point) const;

        /**
         * Checks if the object's rectangular bounding box contains a point
         *
         * @param x in world coordinates
         * @param y in world coordinates
         *
         * @return whether the rectangular bounding box contains the point
         */
        [[nodiscard]] bool boxContains(float x, float y) const;

        /**
         * Checks if the object's bounding box contains a point
         *
         * @param point the coordinates in world space
         *
         * @return whether the object contains the point
         */
        [[nodiscard]] bool contains(Point point) const;

        /**
         * Checks if the object's bounding box contains a point
         *
         * @param x in world coordinates
         * @param y in world coordinates
         *
         * @return whether the object contains the point
         */
        [[nodiscard]] bool contains(float x, float y) const;

    protected:
        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;

        Point *m_Points = nullptr;
        uint32_t m_Vertices;

        Renderable(Point position, std::initializer_list<Point> points);

        Renderable(std::initializer_list<Point> points);

        void update() const;

    protected:
        void _move(float x, float y);

        Point m_Position = {0, 0};
        float m_Width;
        float m_Height;

        float m_AngleDegrees = 0;
        float m_AngleRadians = 0;
        float m_CosAngle = 1;
        float m_SinAngle = 0;

        float m_xScale = 1;
        float m_yScale = 1;

        float m_MaxX = -FLT_MAX;
        float m_MinX = FLT_MAX;
        float m_MaxY = -FLT_MAX;
        float m_MinY = FLT_MAX;

    private:
        bool m_Drawn = false;
        bool m_Hidden = false;

        void _calculateAttributes();

        [[nodiscard]] virtual bool _contains(float x, float y) const;

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;

        virtual void _update() const = 0;

        virtual void _onScale(float xfactor, float yfactor) {
        };
    };
}
