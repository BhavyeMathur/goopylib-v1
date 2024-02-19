#pragma once

#include "Ellipse.h"

namespace gp {
    /**
     * An object representing a circle
     */
    class GPAPI Circle : public Ellipse {

    public:
        /**
         * An object representing a circle
         *
         * @param position the center (x, y) in world space
         * @param radius in world space
         */
        Circle(Point position, float radius);

        ~Circle() override = default;

        std::string toString() const override;

    private:
        float m_RadiusSquared;

        [[nodiscard]] bool _contains(float x, float y) const override;
    };
}
