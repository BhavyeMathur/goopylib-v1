#pragma once

#include "RenderableObject.h"


namespace gp {
    class Triangle : public RenderableObject {
    public:
        Triangle(Point p1, Point p2, Point p3);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3);

        void resetAnchor() override;

    private:
        TriangleVertex m_V1, m_V2, m_V3;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        void _move(float dx, float dy) override;

        void _rotate(float sin, float cos) override;

        void _scale(float xfactor, float yfactor) override;
    };
}
