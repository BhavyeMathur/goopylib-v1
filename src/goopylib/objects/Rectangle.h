#pragma once

#include "Quad.h"

namespace gp {
    /**
     * An object representing a rectangle
     */
    class Rectangle : public Quad {

    public:
        /**
         * An object representing a rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        GPAPI Rectangle(Point position, float width, float height)
                : Quad({position.x - width / 2.0f, position.y - height / 2.0f},
                       {position.x + width / 2.0f, position.y - height / 2.0f},
                       {position.x + width / 2.0f, position.y + height / 2.0f},
                       {position.x - width / 2.0f, position.y + height / 2.0f}) {
        };

        /**
         * An object representing a rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI Rectangle(Point p1, Point p2)
                : Quad({p1.x, p1.y},
                       {p2.x, p1.y},
                       {p2.x, p2.y},
                       {p1.x, p2.y}) {
        };

        GPAPI void setP1(Point point) override;

        [[nodiscard]] GPAPI Point getP1() const override;

        GPAPI void setP2(Point point) override;

        [[nodiscard]] GPAPI Point getP2() const  override;

        GPAPI void setP3(Point point) override;

        [[nodiscard]] GPAPI Point getP3() const override;

        GPAPI void setP4(Point point) override;

        [[nodiscard]] GPAPI Point getP4() const  override;
    };
}
