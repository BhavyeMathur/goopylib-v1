#pragma once

#include "RenderableObject.h"


namespace gp {
    class Ellipse : public RenderableObject {

        friend class Renderer;

    public:
        Ellipse(Point position, float xRadius, float yRadius);

        Ellipse(Point p1, Point p2);

        void setColor(const Color& color);

        void setColor(const Color& color1, const Color& color2, const Color& color3, const Color& color4);

        void setTransparency(float value) override;

        void setTransparency(float v1, float v2, float v3, float v4);

    private:
        EllipseVertexAttrib m_V1 = {{-1, -1},  {0, 0.55, 0.9}};
        EllipseVertexAttrib m_V2 = {{1, -1},  {0, 0.55, 0.9}};
        EllipseVertexAttrib m_V3 = {{1, 1},  {0, 0.55, 0.9}};
        EllipseVertexAttrib m_V4 = {{-1, 1},  {0, 0.55, 0.9}};

        float m_Radius1;
        float m_Radius2;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        bool _contains(float x, float y) const override;

        void _onScale(float xfactor, float yfactor) override;
    };
}
