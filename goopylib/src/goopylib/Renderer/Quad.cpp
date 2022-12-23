#include "Quad.h"

// Core Methods
namespace gp {
    Quad::Quad(Point p1, Point p2, Point p3, Point p4)
            : Polygon4({(p1.x + p2.x + p3.x + p4.x) / 4.0f, (p1.y + p2.y + p3.y + p4.y) / 4.0f},
                       {p1, {0, 0.55, 0.9}},
                       {p2, {0, 0.55, 0.9}},
                       {p3, {0, 0.55, 0.9}},
                       {p4, {0, 0.55, 0.9}},
                       max(p1.x, p2.x, p3.x, p4.x) - min(p1.x, p2.x, p3.x, p4.x),
                       max(p1.y, p2.y, p3.y, p4.y) - min(p1.y, p2.y, p3.y, p4.y)) {
        GP_CORE_DEBUG("Initializing Quad ({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
    }

    uint32_t Quad::_draw(Window *window) const {
        return window->m_Renderer.drawQuad(m_V1, m_V2, m_V3, m_V4);
    }

    void Quad::_destroy() const {
        m_Window->m_Renderer.destroyQuad(m_RendererID);
    }

    void Quad::_update() const {
        m_Window->m_Renderer.updateQuad(m_RendererID, m_V1, m_V2, m_V3, m_V4);
    }
}

// Quad Methods
namespace gp {
    void Quad::setColor(const Color &color) {
        m_V1.color = {color.getRedf(), color.getGreenf(), color.getBluef()};
        m_V2.color = {color.getRedf(), color.getGreenf(), color.getBluef()};
        m_V3.color = {color.getRedf(), color.getGreenf(), color.getBluef()};
        m_V4.color = {color.getRedf(), color.getGreenf(), color.getBluef()};

        update();
    }

    void Quad::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        m_V1.color = {color1.getRedf(), color1.getGreenf(), color1.getBluef()};
        m_V2.color = {color2.getRedf(), color2.getGreenf(), color2.getBluef()};
        m_V3.color = {color3.getRedf(), color3.getGreenf(), color3.getBluef()};
        m_V4.color = {color4.getRedf(), color4.getGreenf(), color4.getBluef()};

        update();
    }
}
