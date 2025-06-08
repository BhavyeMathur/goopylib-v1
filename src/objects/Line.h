#pragma once

#include "Quad.h"

namespace gp {
    /**
     * An object representing a line connecting 2 points together.
     */
    class GPAPI Line : public Quad {

        friend class Renderer;

    public:
        using Quad::setTransparency;
        using Quad::setColor;

        /**
         * An object representing a line connecting 2 points together.
         *
         * @param p1 1st coordinate (x, y) in world space
         * @param p2 2nd coordinate (x, y) in world space
         */
        Line(Point p1, Point p2, float thickness = 3);

        ~Line() override = default;

        [[nodiscard]] std::string toString() const override;

        /**
         * Sets the outline color of the line
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         */
        void setColor(const Color &color1, const Color &color2);

        /**
         * Sets the fill color of the object
         *
         * @param color1 the color of the 1st vertex
         * @param color2 the color of the 2nd vertex
         *
         * @throws std::invalid_argument invalid hexstring
         */
        void setColor(const char *hex1, const char *hex2);

        /**
         * Sets the transparency of the line
         *
         * @param value1 transparency of the 1st vertex between 0-1
         * @param value2 transparency of the 2nd vertex between 0-1
         *
         * @throws std::invalid_argument if values are not between 0 and 1
         */
        void setTransparency(float value1, float value2);

        /**
         * Sets the thickness of the line
         *
         * @param value thickness in world coordinates
         *
         * @throws std::invalid_argument if value is negative
         */
        void setThickness(float value);

        /**
         *
         * @return the thickness of the line in world coordinates
         */
        [[nodiscard]] float getThickness() const;

        void setP1(Point point) override;

        [[nodiscard]] Point getP1() const override;

        void setP2(Point point) override;

        [[nodiscard]] Point getP2() const override;

        void setP3(Point point) override;

        [[nodiscard]] Point getP3() const override;

        void setP4(Point point) override;

        [[nodiscard]] Point getP4() const override;

    private:
        float m_Thickness;
    };
}
