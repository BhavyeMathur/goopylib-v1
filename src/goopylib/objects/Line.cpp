#define GP_LOGGING_LEVEL 3

#include "Line.h"

namespace {
    Point getLineQuadDeltas(Point p1, Point p2, float thickness) {
        thickness /= 2;
        float theta = atan((p2.y - p1.y) / (p2.x - p1.x));

        if (isnan(theta)) {
            return {thickness, thickness};
        }

        float cos_theta = cos(theta);
        float sin_theta = sin(theta);

        return {sin_theta * thickness, cos_theta * thickness};
    }

    gp::Quad getLineQuad(Point p1, Point p2, float thickness) {
        Point delta = getLineQuadDeltas(p1, p2, thickness);
        float dx = delta.x;
        float dy = delta.y;

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
        #if GP_ERROR_CHECKING
        if (thickness < 0) {
            GP_VALUE_ERROR("line thickness must be greater than or equal to 0");
        }
        #endif
    }

    std::string Line::toString() const {
        return strformat("Line((%g, %g), (%g, %g))", getP1().x, getP1().y, getP2().x, getP2().y);
    }
}

// Getter & Setter methods
namespace gp {
    void Line::setColor(const Color &color1, const Color &color2) {
        setColor(color1, color2, color2, color1);
    }

    void Line::setColor(const char *hex1, const char *hex2) {
        setColor(hex1, hex2, hex2, hex1);
    }

    void Line::setTransparency(float value1, float value2) {
        setTransparency(value1, value2, value2, value1);
    }

    void Line::setThickness(float value) {
        #if GP_ERROR_CHECKING
        if (value < 0) {
            GP_VALUE_ERROR("line thickness must be greater than or equal to 0");
        }
        #endif

        m_Thickness = value;

        Point p1 = getP1();
        Point p2 = getP2();

        Point delta = getLineQuadDeltas(p1, p2, m_Thickness);
        float dx = delta.x;
        float dy = delta.y;

        m_Points[0] = {p1.x - dx, p1.y + dy};
        m_Points[1] = {p2.x - dx, p2.y + dy};
        m_Points[2] = {p2.x + dx, p2.y - dy};
        m_Points[3] = {p1.x + dx, p1.y - dy};

        _calculateAttributes();
        update();
    }

    float Line::getThickness() const {
        return m_Thickness;
    }

    void Line::setP1(Point point) {
        Point p2 = getP2();

        Point delta = getLineQuadDeltas(point, p2, m_Thickness);
        float dx = delta.x;
        float dy = delta.y;

        m_Points[0] = {point.x - dx, point.y + dy};
        m_Points[1] = {p2.x - dx, p2.y + dy};
        m_Points[2] = {p2.x + dx, p2.y - dy};
        m_Points[3] = {point.x + dx, point.y - dy};

        _calculateAttributes();
        update();
    }

    Point Line::getP1() const {
        return {(m_Points[0].x + m_Points[3].x) / 2, (m_Points[0].y + m_Points[3].y) / 2};
    }

    void Line::setP2(Point point) {
        Point p1 = getP1();

        Point delta = getLineQuadDeltas(p1, point, m_Thickness);
        float dx = delta.x;
        float dy = delta.y;

        m_Points[0] = {p1.x - dx, p1.y + dy};
        m_Points[1] = {point.x - dx, point.y + dy};
        m_Points[2] = {point.x + dx, point.y - dy};
        m_Points[3] = {p1.x + dx, p1.y - dy};

        _calculateAttributes();
        update();
    }

    Point Line::getP2() const {
        return {(m_Points[1].x + m_Points[2].x) / 2, (m_Points[1].y + m_Points[2].y) / 2};
    }

    void Line::setP3(Point point) {
        GP_CORE_ERROR("gp::Line cannot set point 3");
    }

    Point Line::getP3() const {
        GP_CORE_ERROR("gp::Line cannot get point 3");
        return {NAN, NAN};
    }

    void Line::setP4(Point point) {
        GP_CORE_ERROR("gp::Line cannot set point 4");
    }

    Point Line::getP4() const {
        GP_CORE_ERROR("gp::Line cannot set point 4");
        return {NAN, NAN};
    }
}
