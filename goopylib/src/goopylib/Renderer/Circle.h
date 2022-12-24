#pragma once

#include "Ellipse.h"

namespace gp {
    class Circle : public Ellipse {

    public:
        Circle(Point position, float radius);

    private:
        float m_RadiusSquared;

        bool _contains(float x, float y) const override;
    };
}
