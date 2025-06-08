#define GP_LOGGING_LEVEL 3

#include "Circle.h"


namespace gp {
    Circle::Circle(Point position, float radius)
            : Ellipse(position, radius, radius),
              m_RadiusSquared(radius * radius) {
    }

    bool Circle::_contains(float x, float y) const {
        x -= m_Position.x;
        y -= m_Position.y;

        Point p = {x * m_CosAngle - y * m_SinAngle,
                   x * m_SinAngle + y * m_CosAngle};

        p.x /= m_xScale;
        p.y /= m_yScale;

        return p.x * p.x + p.y * p.y < m_RadiusSquared;
    }

    std::string Circle::toString() const {
        return strformat("Circle((%g, %g), radius=%g)", m_Position.x, m_Position.y, m_Radius1);
    }
}
