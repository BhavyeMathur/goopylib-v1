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

        bool isDrawn() const;

        // Anchor
        void setAnchor(float x, float y);

        void resetAnchor();

        // Position
        void move(float dx, float dy);

        void setPosition(float x, float y);

        Point getPosition() const;

        // Rotation
        void rotate(float angle);

        void setRotation(float angle);

        float getRotation() const;

        // Scale
        void scale(float factor);

        void scale(float xfactor, float yfactor);

        void setScale(float xfactor, float yfactor);

        Scale getScale() const;

        // Dimensions
        void setWidth(float width);

        float getWidth() const;

        void setHeight(float height);

        float getHeight() const;

        void setSize(float width, float height);

        bool boxContains(Point point) const;

        bool contains(Point point) const;

        // Visibility
        virtual void setTransparency(float value) = 0;

        void hide(bool hidden = true);

        void show();

        bool isHidden() const;

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

        virtual bool _contains(float x, float y) const;

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;

        virtual void _update() const = 0;

        virtual void _onScale(float xfactor, float yfactor) {
        };
    };
}
