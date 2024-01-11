#pragma once

#include "Quad.h"

namespace gp {
    /**
     * An object representing a rectangle
     */
    class Rectangle : virtual public Quad {

    public:
        /**
         * An object representing a rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        GPAPI Rectangle(Point position, float width, float height);

        /**
         * An object representing a rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        GPAPI Rectangle(Point p1, Point p2);

        GPAPI ~Rectangle() override = default;

        [[nodiscard]] GPAPI std::string toString() const override;

        GPAPI void setP1(Point point) override;

        [[nodiscard]] GPAPI Point getP1() const override;

        GPAPI void setP2(Point point) override;

        [[nodiscard]] GPAPI Point getP2() const override;

        GPAPI void setP3(Point point) override;

        [[nodiscard]] GPAPI Point getP3() const override;

        GPAPI void setP4(Point point) override;

        [[nodiscard]] GPAPI Point getP4() const override;

    protected:
        GPAPI Rectangle() = default;
    };
}
