#pragma once

#include "RenderableObject.h"

namespace gp {
    class Line : public RenderableObject {

        friend class Renderer;

    public:
        Line(Point p1, Point p2);

        void setColor(const Color &color);

        void setColor(const Color &color1, const Color &color2);

        void setTransparency(float value);

        void setTransparency(float value1, float value2);

        // Static Methods

        static void setThickness(float value);

        static float getThickness();

        static void init();

    private:
        LineVertexAttrib m_V1, m_V2;

        static float s_Width;
        static float s_MinWidth;
        static float s_MaxWidth;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;
    };
}
