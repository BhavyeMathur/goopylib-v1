#pragma once

#include "RenderableObject.h"


namespace gp {
    class Quad : public RenderableObject {
    public:
        Quad(Point p1, Point p2, Point p3, Point p4);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        void resetCenter() override;

    private:
        QuadVertex m_V1, m_V2, m_V3, m_V4;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        void _move(float dx, float dy) override;

        void _rotate(float sin, float cos) override;

        void _scale(float xfactor, float yfactor) override;
    };
}
