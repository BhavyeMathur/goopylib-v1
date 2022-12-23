#pragma once

#include "RenderableObject.h"


namespace gp {
    class Ellipse : public RenderableObject {
    public:
        Ellipse(Point position, float xRadius, float yRadius);

        Ellipse(Point p1, Point p2);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        void resetCenter() final;

    private:
        EllipseVertex m_V1, m_V2, m_V3, m_V4;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        void _move(float dx, float dy) final;

        void _rotate(float sin, float cos) final;

        void _scale(float xfactor, float yfactor) final;
    };
}
