#define GP_LOGGING_LEVEL 3

#include "Triangle.h"

// Core Methods
namespace gp {
    Triangle::Triangle(Point p1, Point p2, Point p3)
            : Renderable({p1, p2, p3}) {
        GP_CORE_DEBUG("Initializing Triangle ({0}, {1}), ({2}, {3}), ({4}, {5})", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    }

    bool Triangle::_contains(float x, float y) const {
        return checkTriangleContains({x, y}, m_Points[0], m_Points[1], m_Points[2]);
    }

    RenderableSubclass Triangle::_getRenderableSubclass() {
        return RenderableSubclass::Triangle;
    }

    std::string Triangle::toString() const {
        return strformat("Triangle((%g, %g), (%g, %g), (%g, %g))",
                         getP1().x, getP1().y, getP2().x, getP2().y, getP3().x, getP3().y);
    }
}

// Triangle Methods
namespace gp {
    void Triangle::setColor(const Color &color) {
        setColor(color, color, color);
    }

    void Triangle::setColor(const Color &color1, const Color &color2, const Color &color3) {
        m_V1.color = color1.getRGBAf();
        m_V2.color = color2.getRGBAf();
        m_V3.color = color3.getRGBAf();

        update();
    }

    void Triangle::setColor(const char *hexstring, float alpha) {
        m_V1.color = Color(hexstring, alpha).getRGBAf();
        m_V2.color = m_V1.color;
        m_V3.color = m_V1.color;

        update();
    }

    void Triangle::setColor(const char *hex1, const char *hex2, const char *hex3) {
        m_V1.color = Color(hex1).getRGBAf();
        m_V2.color = Color(hex2).getRGBAf();
        m_V3.color = Color(hex3).getRGBAf();

        update();
    }

    void Triangle::setColor(int red, int green, int blue, float alpha) {
        m_V1.color = Color(red, green, blue, alpha).getRGBAf();
        m_V2.color = m_V1.color;
        m_V3.color = m_V1.color;

        update();
    }

    void Triangle::setTransparency(float value) {
        setTransparency(value, value, value);
    }

    void Triangle::setTransparency(float v1, float v2, float v3) {
        m_V1.color.alpha = v1;
        m_V2.color.alpha = v2;
        m_V3.color.alpha = v3;

        update();
    }

    Float3 Triangle::getTransparency() {
        return {m_V1.color.alpha, m_V2.color.alpha, m_V3.color.alpha};
    }

    bool Triangle::isOpaque() const {
        return (m_V1.color.alpha == 1) && (m_V2.color.alpha == 1) && (m_V3.color.alpha == 1);
    }
}

// Triangle Getter & Setters
namespace gp {
    void Triangle::setP1(Point point) {
        m_Points[0] = point;

        _calculateAttributes();
        update();
    }

    Point Triangle::getP1() const {
        return m_Points[0];
    }

    void Triangle::setP2(Point point) {
        m_Points[1] = point;

        _calculateAttributes();
        update();
    }

    Point Triangle::getP2() const {
        return m_Points[1];
    }

    void Triangle::setP3(Point point) {
        m_Points[2] = point;

        _calculateAttributes();
        update();
    }

    Point Triangle::getP3() const {
        return m_Points[2];
    }
}
