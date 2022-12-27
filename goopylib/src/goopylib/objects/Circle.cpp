#include "Circle.h"

#if !GP_LOG_CIRCLE
#undef GP_LOGGING_LEVEL
#endif

#include "src/goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_CIRCLE
#undef GP_VALUE_CHECKING
#endif

#include "src/goopylib/debug/Error.h"


namespace gp {
    Circle::Circle(Point position, float radius)
    : Ellipse(position, radius, radius),
    m_RadiusSquared(radius * radius) {}

    bool Circle::_contains(float x, float y) const {
        x -= m_Position.x;
        y -= m_Position.y;

        Point p = {x * m_CosAngle - y * m_SinAngle,
                   x * m_SinAngle + y * m_CosAngle};

        p.x /= m_xScale;
        p.y /= m_yScale;

        return p.x * p.x + p.y * p.y < m_RadiusSquared;
    }
}
