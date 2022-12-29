#include "Circle.h"

#if (GP_LOG_CIRCLE != true) and (GP_LOG_CIRCLE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_CIRCLE
#endif

#if !GP_VALUE_CHECK_CIRCLE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


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
