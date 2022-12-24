#include "Triangle.h"

// Core Methods
namespace gp {
    Triangle::Triangle(Point p1, Point p2, Point p3)
            : RenderableObject({p1, p2, p3}),
              m_V1({0, 0.55, 0.9}),
              m_V2({0, 0.55, 0.9}),
              m_V3({0, 0.55, 0.9}) {
        GP_CORE_DEBUG("Initializing Triangle ({0}, {1}), ({2}, {3}), ({4}, {5})", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    }

    uint32_t Triangle::_draw(Window *window) const {
        return window->m_Renderer.drawTriangle(const_cast<Triangle *>(this));
    }

    void Triangle::_destroy() const {
        m_Window->m_Renderer.destroyTriangle(m_RendererID);
    }

    void Triangle::_update() const {
        m_Window->m_Renderer.updateTriangle(m_RendererID, this);
    }

    bool Triangle::_contains(float x, float y) {
        return false;
    }
}

// Triangle Methods
namespace gp {
    void Triangle::setColor(const Color &color) {
        setColor(color, color, color);
    }

    void Triangle::setColor(const Color &color1, const Color &color2, const Color &color3) {
        m_V1.color = {color1.getRedf(), color1.getGreenf(), color1.getBluef(), color1.getAlpha()};
        m_V2.color = {color2.getRedf(), color2.getGreenf(), color2.getBluef(), color2.getAlpha()};
        m_V3.color = {color3.getRedf(), color3.getGreenf(), color3.getBluef(), color3.getAlpha()};

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
