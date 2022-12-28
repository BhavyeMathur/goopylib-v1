#pragma once

#include "Renderable.h"


namespace gp {
    class Triangle : public Renderable {

        friend class Renderer;

    public:
        Triangle(Point p1, Point p2, Point p3);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3);

        void setTransparency(float value) override;

        void setTransparency(float v1, float v2, float v3);

    private:
        TriangleVertexAttrib m_V1, m_V2, m_V3;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        [[nodiscard]] bool _contains(float x, float y) const override;
    };
}
