#pragma once

#include "Renderable.h"

namespace gp {
    /**
     * An object representing a line connecting 2 points together.
     */
    class Line : public Renderable {

        friend class Renderer;

    public:
        /**
         * An object representing a line connecting 2 points together.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         */
        Line(Point p1, Point p2);

        /**
         * Sets the outline color of the line
         * @param color the color of the line
         */
        void setColor(const Color &color);

        /**
         * Sets the outline color of the line
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         */
        void setColor(const Color &color1, const Color &color2);

        void setTransparency(float value) override;

        /**
         * Sets the transparency of the line
         *
         * @param value1 transparency of the 1st vertex between 0-1
         * @param value2 transparency of the 2nd vertex between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void setTransparency(float value1, float value2);

        // Static Methods

        /**
         * Sets the thickness of all lines
         * @param value thickness in world coordinates
         */
        static void setThickness(float value);

        /**
         *
         * @return the thickness of all lines in world coordinates
         */
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
