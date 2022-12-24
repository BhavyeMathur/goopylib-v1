#include "Quad.h"

// Core Methods
namespace gp {
    Quad::Quad(Point p1, Point p2, Point p3, Point p4)
            : Polygon4(p1, QuadVertexAttrib({0, 0.55, 0.9}),
                       p2, QuadVertexAttrib({0, 0.55, 0.9}),
                       p3, QuadVertexAttrib({0, 0.55, 0.9}),
                       p4, QuadVertexAttrib({0, 0.55, 0.9})) {
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
}

// Quad Methods
namespace gp {
    void Quad::setColor(const Color &color) {
        m_V1.color = {color.getRedf(), color.getGreenf(), color.getBluef()};
        m_V2.color = {color.getRedf(), color.getGreenf(), color.getBluef()};
        m_V3.color = {color.getRedf(), color.getGreenf(), color.getBluef()};
        m_V4.color = {color.getRedf(), color.getGreenf(), color.getBluef()};

        m_V1.transparency = color.getAlpha();
        m_V2.transparency = color.getAlpha();
        m_V3.transparency = color.getAlpha();
        m_V4.transparency = color.getAlpha();

        update();
    }

    void Quad::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        m_V1.color = {color1.getRedf(), color1.getGreenf(), color1.getBluef()};
        m_V2.color = {color2.getRedf(), color2.getGreenf(), color2.getBluef()};
        m_V3.color = {color3.getRedf(), color3.getGreenf(), color3.getBluef()};
        m_V4.color = {color4.getRedf(), color4.getGreenf(), color4.getBluef()};

        m_V1.transparency = color1.getAlpha();
        m_V2.transparency = color2.getAlpha();
        m_V3.transparency = color3.getAlpha();
        m_V4.transparency = color4.getAlpha();

        update();
    }
}
