#pragma once

#include "Quad.h"

namespace gp {
    /**
     * An object representing a rectangle
     */
    class GPAPI Rectangle : virtual public Quad {

    public:
        /**
         * An object representing a rectangle
         *
         * @param position center (x, y) of the rectangle in world space
         * @param width in world space
         * @param height in world space
         */
        Rectangle(Point position, float width, float height);

        /**
         * An object representing a rectangle
         *
         * @param p1 the 1st coordinate (x, y) of the rectangle
         * @param p2 the 2nd coordinate (x, y) of the rectangle
         */
        Rectangle(Point p1, Point p2);

        ~Rectangle() override = default;

        [[nodiscard]] std::string toString() const override;

        void setP1(Point point) override;

        [[nodiscard]] Point getP1() const override;

        void setP2(Point point) override;

        [[nodiscard]] Point getP2() const override;

        void setP3(Point point) override;

        [[nodiscard]] Point getP3() const override;

        void setP4(Point point) override;

        [[nodiscard]] Point getP4() const override;

    protected:
        Rectangle() = default;
    };
}
