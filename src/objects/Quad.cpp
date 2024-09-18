#define GP_LOGGING_LEVEL 3

#include "Quad.h"
#include "debug/Error.h"

// Core Methods
namespace gp {
    Quad::Quad(Point p1, Point p2, Point p3, Point p4)
            : Renderable({p1, p2, p3, p4}) {
        GP_CORE_DEBUG("gp::Quad::Quad(({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7}))",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
    }

    bool Quad::_contains(float x, float y) const {
        return checkQuadContains({x, y}, m_Points[0], m_Points[1], m_Points[2], m_Points[3]);
    }

    RenderableSubclass Quad::_getRenderableSubclass() {
        return RenderableSubclass::Quad;
    }

    std::string Quad::toString() const {
        return strformat("Quad((%g, %g), (%g, %g), (%g, %g), (%g, %g))",
                         getP1().x, getP1().y, getP2().x, getP2().y, getP3().x, getP3().y, getP4().x, getP4().y);
    }
}

// Quad Methods
namespace gp {
    void Quad::setColor(const Color &color) {
        setColor(color, color, color, color);
    }

    void Quad::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        setColor(color1.getRGBAf(), color2.getRGBAf(), color3.getRGBAf(), color4.getRGBAf());
    }

    void Quad::setColor(const char *hexstring, float alpha) {
        auto color = Color(hexstring, alpha).getRGBAf();
        setColor(color, color, color, color);
    }

    void Quad::setColor(const char *hex1, const char *hex2, const char *hex3, const char *hex4) {
        setColor(Color(hex1).getRGBAf(),
                 Color(hex2).getRGBAf(),
                 Color(hex3).getRGBAf(),
                 Color(hex4).getRGBAf());
    }

    void Quad::setColor(int red, int green, int blue, float alpha) {
        auto color = Color(red, green, blue, alpha).getRGBAf();
        setColor(color, color, color, color);
    }

    void Quad::setColor(const RGBAf rgbaf1, const RGBAf rgbaf2, const RGBAf rgbaf3, const RGBAf rgbaf4) {
        m_VertexAttribs[0].color = rgbaf1;
        m_VertexAttribs[1].color = rgbaf2;
        m_VertexAttribs[2].color = rgbaf3;
        m_VertexAttribs[3].color = rgbaf4;

        update();
    }

    void Quad::setTransparency(float value) {
        setTransparency(value, value, value, value);
    }

    void Quad::setTransparency(float v1, float v2, float v3, float v4) {
        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, "transparency must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, "transparency must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, "transparency must be between 0 and 1")
        GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, "transparency must be between 0 and 1")

        m_VertexAttribs[0].color.alpha = v1;
        m_VertexAttribs[1].color.alpha = v2;
        m_VertexAttribs[2].color.alpha = v3;
        m_VertexAttribs[3].color.alpha = v4;

        update();
    }

    Float4 Quad::getTransparency() const {
        return {m_VertexAttribs[0].color.alpha,
                m_VertexAttribs[1].color.alpha,
                m_VertexAttribs[2].color.alpha,
                m_VertexAttribs[3].color.alpha};
    }

    bool Quad::isOpaque() const {
        GP_CORE_TRACE("gp::Quad::isOpaque()");
        return (m_VertexAttribs[0].color.alpha == 1)
               && (m_VertexAttribs[1].color.alpha == 1)
               && (m_VertexAttribs[2].color.alpha == 1)
               && (m_VertexAttribs[3].color.alpha == 1);
    }
}

// Quad Getter & Setters
namespace gp {
    void Quad::setP1(Point point) {
        m_Points[0] = point;

        _calculateAttributes();
        update();
    }

    Point Quad::getP1() const {
        return m_Points[0];
    }

    void Quad::setP2(Point point) {
        m_Points[1] = point;

        _calculateAttributes();
        update();
    }

    Point Quad::getP2() const {
        return m_Points[1];
    }

    void Quad::setP3(Point point) {
        m_Points[2] = point;

        _calculateAttributes();
        update();
    }

    Point Quad::getP3() const {
        return m_Points[2];
    }

    void Quad::setP4(Point point) {
        m_Points[3] = point;

        _calculateAttributes();
        update();
    }

    Point Quad::getP4() const {
        return m_Points[3];
    }
}
