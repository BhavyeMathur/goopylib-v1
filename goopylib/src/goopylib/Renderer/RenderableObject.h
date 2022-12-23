#pragma once

#include "Point.h"
#include "src/goopylib/Core/Window.h"

namespace gp {
    struct Scale {
        float xscale;
        float yscale;
    };

    class RenderableObject {

    public:
        void draw(Window *window);

        void destroy();

        bool isDrawn() const;

        void move(float dx, float dy);

        void setAnchor(float x, float y);

        virtual void resetCenter() = 0;

        void setPosition(float x, float y);

        Point getPosition() const;

        void rotate(float angle);

        float getRotation() const;

        void scale(float factor);

        void scale(float xfactor, float yfactor);

        Scale getScale() const;

    protected:
        Window *m_Window = nullptr;
        uint32_t m_RendererID = 0;

        Point m_Position;
        float m_Angle = 0;
        float m_xScale = 1;
        float m_yScale = 1;

        explicit RenderableObject(Point position);

        void update() const;

    private:
        bool m_Drawn = false;

        virtual uint32_t _draw(Window *window) const = 0;

        virtual void _destroy() const = 0;

        virtual void _update() const = 0;

        virtual void _move(float dx, float dy) = 0;

        virtual void _rotate(float sin, float cos) = 0;

        virtual void _scale(float xfactor, float yfactor) = 0;
    };
}
