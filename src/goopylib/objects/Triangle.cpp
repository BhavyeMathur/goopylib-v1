#define GP_LOGGING_LEVEL 3

#include "Triangle.h"

#include "src/goopylib/debug/LogMacros.h"

// Core Methods
namespace gp {
    Triangle::Triangle(Point p1, Point p2, Point p3)
            : Renderable({p1, p2, p3}),
              m_V1({0.0f, 0.55f, 0.9f}),
              m_V2({0.0f, 0.55f, 0.9f}),
              m_V3({0.0f, 0.55f, 0.9f}) {
        GP_CORE_DEBUG("Initializing Triangle ({0}, {1}), ({2}, {3}), ({4}, {5})", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    }

    uint32_t Triangle::_draw(Window &window) {
        return window.m_Renderer.drawTriangle(this);
    }

    void Triangle::_destroy() const {
        m_Window->m_Renderer.destroyTriangle(m_RendererID);
    }

    void Triangle::_update() {
        m_Window->m_Renderer.updateTriangle(m_RendererID, this);
    }

    bool Triangle::_contains(float x, float y) const {
        return checkTriangleContains({x, y}, m_Points[0], m_Points[1], m_Points[2]);
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
}
