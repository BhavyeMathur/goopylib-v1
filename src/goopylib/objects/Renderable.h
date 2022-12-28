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
    class Renderable {

        friend class Renderer;

    public:
        void draw(Window *window);

        void destroy();

        [[nodiscard]] bool isDrawn() const;

        /* Getters & Setters */

        // Anchor
        void setAnchor(float x, float y);

        void resetAnchor();

        // Position
        void move(float dx, float dy);

        void setX(float x);

        [[nodiscard]] float getX() const;

        void setY(float y);

        [[nodiscard]] float getY() const;

        void setPosition(float x, float y);

        [[nodiscard]] Point getPosition() const;

        // Rotation
        void rotate(float angle);

        void setRotation(float angle);

        [[nodiscard]] float getRotation() const;

        // Scale
        void scale(float factor);

        void scale(float xfactor, float yfactor);

        void setScaleX(float factor);

        void setScaleY(float factor);

        void setScale(float factor);

        void setScale(float xfactor, float yfactor);

        [[nodiscard]] Scale getScale() const;

        // Dimensions
        void setWidth(float width);

        [[nodiscard]] float getWidth() const;

        void setHeight(float height);

        [[nodiscard]] float getHeight() const;

        void setSize(float width, float height);

        // Visibility
        virtual void setTransparency(float value) = 0;

        void hide(bool hide = true);

        void show();

        [[nodiscard]] bool isHidden() const;

        /* Methods */

        [[nodiscard]] bool boxContains(Point point) const;

        [[nodiscard]] bool contains(Point point) const;

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
