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
        GPAPI Line(Point p1, Point p2);

        GPAPI virtual ~Line() = default;

        /**
         * Sets the outline color of the line
         * @param color the color of the line
         */
        GPAPI void setColor(const Color &color);

        /**
         * Sets the outline color of the line
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         */
        GPAPI void setColor(const Color &color1, const Color &color2);

        /**
         * Sets the fill color of the object
         *
         * @param color the color of the object
         * @param alpha alpha component of the color between 0-1
         *
         * @throws std::invalid_argument invalid hexstring
         * @throws std::invalid_argument alpha must be between 0-1
         */
        GPAPI void setColor(const char *hexstring, float alpha = 1);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         *
         * @throws std::invalid_argument invalid hexstring
         */
        GPAPI void setColor(const char *hex1, const char *hex2);

        /**
         * Sets the fill color of the object
         *
         * @param red red component of the color between 0-255
         * @param green green component of the color between 0-255
         * @param blue blue component of the color between 0-255
         * @param alpha alpha component of the color between 0-1
         *
         * @throws std::invalid_argument RGB must be between 0-255
         * @throws std::invalid_argument alpha must be between 0-1
         */
        GPAPI void setColor(int red, int green, int blue, float alpha = 1);

        /**
         * Sets the transparency of the object
         *
         * @param value transparency of the object between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        GPAPI void setTransparency(float value) override;

        /**
         * Sets the transparency of the line
         *
         * @param value1 transparency of the 1st vertex between 0-1
         * @param value2 transparency of the 2nd vertex between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        GPAPI void setTransparency(float value1, float value2);

        /**
         *
         * @return the transparency at each vertex of the line
         *
         */
        [[nodiscard]] GPAPI Float2 getTransparency();

        // Static Methods

        /**
         * Sets the thickness of all lines
         * @param value thickness in world coordinates
         */
        GPAPI static void setThickness(float value);

        /**
         *
         * @return the thickness of all lines in world coordinates
         */
        GPAPI static float getThickness();

        GPAPI static void init();

    private:
        SolidVertexAttrib m_V1 = {{0.0f, 0.0f, 0.0f}};
        SolidVertexAttrib m_V2 = {{0.0f, 0.0f, 0.0f}};

        static float s_Width;
        static float s_MinWidth;
        static float s_MaxWidth;

        [[nodiscard]] GPAPI uint32_t _draw(Window &window) override;

        GPAPI void _destroy() const override;

        GPAPI void _update() override;
    };
}
