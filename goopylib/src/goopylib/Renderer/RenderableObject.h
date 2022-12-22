#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"

namespace gp {
    class RenderableObject {

    public:
        void draw(Window *window);

        void destroy();

        bool isDrawn() const;

        Point getPosition() const;

        void move(float dx, float dy);

        void setPosition(float dx, float dy);

        void rotate(float angle);

        void rotate(float angle, Point pivot);

        void scale(float factor);

        void scale(float xfactor, float yfactor);

        void scale(float factor, Point pivot);

        void scale(float xfactor, float yfactor, Point pivot);

    protected:
        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;

        Point m_Position;

        explicit RenderableObject(Point position);

        void update() const;

    private:
        float m_Angle = 0;
        float m_xScale = 1;
        float m_yScale = 1;

        bool m_Drawn = false;

        virtual void _calculateCenter() = 0;

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;

        virtual void _update() const = 0;

        virtual void _move(float dx, float dy) = 0;

        virtual void _rotate(float sin, float cos) = 0;

        virtual void _scale(float xfactor, float yfactor) = 0;
    };
}
