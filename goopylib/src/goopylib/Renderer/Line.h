#pragma once

#include "RenderableObject.h"

namespace gp {
    class Line : public RenderableObject {

    public:
        Line(Point p1, Point p2);

        void resetAnchor() override;

        void setColor(const Color &color);

        void setColor(const Color &color1, const Color &color2);

        void setTransparency(float value);

        void setTransparency(float value1, float value2);

        // Static Methods

        static void setWidth(float value);

        static float getWidth();

        static void init();

    private:
        LineVertex m_V1, m_V2;

        static float s_Width;
        static float s_MinWidth;
        static float s_MaxWidth;

        uint32_t _draw(Window *window) const override;

        void _destroy() const override;

        void _update() const override;

        void _move(float dx, float dy) override;

        void _rotate(float sin, float cos) override;

        void _scale(float xfactor, float yfactor) override;
    };
}
