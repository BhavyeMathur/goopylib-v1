#pragma once

#include "Renderable.h"


namespace gp {
    class Quad : public Renderable {

        friend class Renderer;

    public:
        Quad(Point p1, Point p2, Point p3, Point p4);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        void setTransparency(float value) override;

        void setTransparency(float v1, float v2, float v3, float v4);

    private:
        QuadVertexAttrib m_V1 = {{0, 0.55, 0.9}};
        QuadVertexAttrib m_V2 = {{0, 0.55, 0.9}};
        QuadVertexAttrib m_V3 = {{0, 0.55, 0.9}};
        QuadVertexAttrib m_V4 = {{0, 0.55, 0.9}};

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        [[nodiscard]] bool _contains(float x, float y) const override;
    };
}
