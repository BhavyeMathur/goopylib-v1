#define GP_LOGGING_LEVEL 3

#include "Ellipse.h"
#include "debug/Error.h"

// Core Methods
namespace gp {
    Ellipse::Ellipse(Point position, float xRadius, float yRadius)
            : Renderable(position, {{position.x - xRadius, position.y - yRadius},
                                    {position.x + xRadius, position.y - yRadius},
                                    {position.x + xRadius, position.y + yRadius},
                                    {position.x - xRadius, position.y + yRadius}}),
              m_Radius1(xRadius),
              m_Radius2(yRadius) {
        GP_CORE_DEBUG("Initializing Ellipse at ({0}, {1}), xRadius={3}, yRadius={4}",
                      position.x, position.y, xRadius, yRadius);
    }

    Ellipse::Ellipse(Point p1, Point p2)
            : Renderable({{p1.x, p1.y},
                          {p2.x, p1.y},
                          {p2.x, p2.y},
                          {p1.x, p2.y}}),
              m_Radius1(abs(p2.x - p1.x) / 2),
              m_Radius2(abs(p2.y - p1.y) / 2) {
        GP_CORE_DEBUG("Initializing Ellipse ({0}, {1}), ({2}, {3})", p1.x, p1.y, p2.x, p2.y);
    }

    bool Ellipse::_contains(float x, float y) const {
        x -= m_Position.x;
        y -= m_Position.y;

        Point p = {x * m_CosAngle - y * m_SinAngle,
                   x * m_SinAngle + y * m_CosAngle};

        p.x /= m_Radius1;
        p.y /= m_Radius2;

        return p.x * p.x + p.y * p.y < 1;
    }

    void Ellipse::_onScale(float xfactor, float yfactor) {
        m_Radius1 *= xfactor;  // Since these variables are used only by _contains(),
        m_Radius2 *= yfactor;  // we do not need to care about the rotation
    }

    RenderableSubclass Ellipse::_getRenderableSubclass() {
        return RenderableSubclass::Ellipse;
    }

    std::string Ellipse::toString() const {
        return strformat("Ellipse((%g, %g), radii=(%g, %g))", m_Position.x, m_Position.y, m_Radius1, m_Radius2);
    }

    const void *Ellipse::vertexAttribData() const {
        return static_cast<const void *>(m_VertexAttribs);
    }
}

// Ellipse Methods
namespace gp {
    void Ellipse::setColor(const Color &color) {
        setColor(color, color, color, color);
    }

    void Ellipse::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        setColor(color1.getRGBAf(), color2.getRGBAf(), color3.getRGBAf(), color4.getRGBAf());
    }

    void Ellipse::setColor(const char *hexstring, float alpha) {
        auto color = Color(hexstring, alpha).getRGBAf();
        setColor(color, color, color, color);
    }

    void Ellipse::setColor(const char *hex1, const char *hex2, const char *hex3, const char *hex4) {
        setColor(Color(hex1).getRGBAf(),
                 Color(hex2).getRGBAf(),
                 Color(hex3).getRGBAf(),
                 Color(hex4).getRGBAf());
    }

    void Ellipse::setColor(int red, int green, int blue, float alpha) {
        auto color = Color(red, green, blue, alpha).getRGBAf();
        setColor(color, color, color, color);;
    }

    void Ellipse::setColor(const gp::RGBAf rgbaf1, const gp::RGBAf rgbaf2, const gp::RGBAf rgbaf3,
                           const gp::RGBAf rgbaf4) {
        m_VertexAttribs[0].color = rgbaf1;
        m_VertexAttribs[1].color = rgbaf2;
        m_VertexAttribs[2].color = rgbaf3;
        m_VertexAttribs[3].color = rgbaf4;

        update();
    }

    void Ellipse::setTransparency(float value) {
        setTransparency(value, value, value, value);
    }

    void Ellipse::setTransparency(float v1, float v2, float v3, float v4) {
        GP_CHECK_INCLUSIVE_RANGE(v1, 0, 1, "transparency must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(v2, 0, 1, "transparency must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(v3, 0, 1, "transparency must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(v4, 0, 1, "transparency must be between 0 and 1");

        m_VertexAttribs[0].color.alpha = v1;
        m_VertexAttribs[1].color.alpha = v2;
        m_VertexAttribs[2].color.alpha = v3;
        m_VertexAttribs[3].color.alpha = v4;

        update();
    }

    Float4 Ellipse::getTransparency() const {
        return {m_VertexAttribs[0].color.alpha,
                m_VertexAttribs[1].color.alpha,
                m_VertexAttribs[2].color.alpha,
                m_VertexAttribs[3].color.alpha};
    }

    bool Ellipse::isOpaque() const {
        return (m_VertexAttribs[0].color.alpha == 1)
               && (m_VertexAttribs[1].color.alpha == 1)
               && (m_VertexAttribs[2].color.alpha == 1)
               && (m_VertexAttribs[3].color.alpha == 1);
    }
}
