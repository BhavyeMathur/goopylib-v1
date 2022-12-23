#pragma once

#include "Polygon4.h"


namespace gp {
    class Quad : public Polygon4<QuadVertex> {
    public:
        Quad(Point p1, Point p2, Point p3, Point p4);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

    private:
        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;
    };
}
