#pragma once

#include "Ellipse.h"

namespace gp {
    /**
     * An object representing a circle
     */
    class Circle : public Ellipse {

    public:
        /**
         * An object representing a circle
         *
         * @param position the center (x, y) in world space
         * @param radius in world space
         */
        GPAPI Circle(Point position, float radius);

        GPAPI ~Circle() override = default;

        GPAPI std::string toString() const override;

    private:
        float m_RadiusSquared;

        [[nodiscard]] GPAPI bool _contains(float x, float y) const override;
    };
}
