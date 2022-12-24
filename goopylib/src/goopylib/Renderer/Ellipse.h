#pragma once

#include "Polygon4.h"


namespace gp {
    class Ellipse : public Polygon4<EllipseVertexAttrib> {

        friend class Renderer;

    public:
        Ellipse(Point position, float xRadius, float yRadius);

        Ellipse(Point p1, Point p2);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

    private:
        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;
    };
}
