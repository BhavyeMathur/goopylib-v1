#include "Quad.h"

// Core Methods
namespace gp {
    Quad::Quad(Point p1, Point p2, Point p3, Point p4)
            : Renderable({p1, p2, p3, p4}) {
        GP_CORE_DEBUG("Initializing Quad ({0}, {1}), ({2}, {3}), ({4}, {5}), ({6}, {7})",
                      p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
    }

    uint32_t Quad::_draw(Window *window) const {
        return window->m_Renderer.drawQuad(const_cast<Quad *>(this));
    }

    void Quad::_destroy() const {
        m_Window->m_Renderer.destroyQuad(m_RendererID);
    }

    void Quad::_update() const {
        m_Window->m_Renderer.updateQuad(m_RendererID, this);
    }

    bool Quad::_contains(float x, float y) const {
        return checkQuadContains({x, y}, m_Points[0], m_Points[1], m_Points[2], m_Points[3]);
    }
}

// Quad Methods
namespace gp {
    void Quad::setColor(const Color &color) {
        setColor(color, color, color, color);
    }

    void Quad::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        m_V1.color = {color1.getRedf(), color1.getGreenf(), color1.getBluef(), color1.getAlpha()};
        m_V2.color = {color2.getRedf(), color2.getGreenf(), color2.getBluef(), color2.getAlpha()};
        m_V3.color = {color3.getRedf(), color3.getGreenf(), color3.getBluef(), color3.getAlpha()};
        m_V4.color = {color4.getRedf(), color4.getGreenf(), color4.getBluef(), color4.getAlpha()};

        update();
    }

    void Quad::setTransparency(float value) {
        setTransparency(value, value, value, value);
    }

    void Quad::setTransparency(float v1, float v2, float v3, float v4) {
        m_V1.color.alpha = v1;
        m_V2.color.alpha = v2;
        m_V3.color.alpha = v3;
        m_V4.color.alpha = v4;

        update();
    }
}
