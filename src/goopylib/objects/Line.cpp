#define GP_LOGGING_LEVEL 3
#include "Line.h"

namespace {
    gp::Quad getLineQuad(Point p1, Point p2, float thickness) {
        float theta = atan((p2.y - p1.y) / (p2.x - p1.x));
        float cos_theta = cos(theta);
        float sin_theta = sin(theta);

        thickness /= 2;
        float dx = sin_theta * thickness;
        float dy = cos_theta * thickness;

        return {{p1.x - dx, p1.y + dy},
                {p2.x - dx, p2.y + dy},
                {p2.x + dx, p2.y - dy},
                {p1.x + dx, p1.y - dy}};
    }
}

// Core Methods
namespace gp {
    Line::Line(Point p1, Point p2, float thickness)
            : Quad(getLineQuad(p1, p2, thickness)),
            m_Thickness(thickness) {

    }
}

// Getter & Setter methods
namespace gp {
    void Line::setColor(const Color &color1, const Color &color2) {
        setColor(color1, color1, color2, color2);
    }

    void Line::setColor(const char *hex1, const char *hex2) {
        setColor(hex1, hex1, hex2, hex2);
    }

    void Line::setTransparency(float value1, float value2) {
        setTransparency(value1, value1, value2, value2);
    }

    void Line::setThickness(float value) {
        m_Thickness = value;
    }

    float Line::getThickness() const {
        return m_Thickness;
    }
}
