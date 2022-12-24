#include "Ellipse.h"

// Core Methods
namespace gp {
    Ellipse::Ellipse(Point position, float xRadius, float yRadius)
            : Polygon4(position,
                       {position.x - xRadius, position.y - yRadius}, {{-1, -1}, {0, 0.55, 0.9}},
                       {position.x + xRadius, position.y - yRadius}, {{1, -1}, {0, 0.55, 0.9}},
                       {position.x + xRadius, position.y + yRadius}, {{1, 1}, {0, 0.55, 0.9}},
                       {position.x - xRadius, position.y + yRadius}, {{-1, 1}, {0, 0.55, 0.9}}) {

        GP_CORE_DEBUG("Initializing Ellipse at ({0}, {1}), xRadius={3}, yRadius={4}",
                      position.x, position.y, xRadius, yRadius);
    }

    Ellipse::Ellipse(Point p1, Point p2)
            : Polygon4(p1, p2) {
        GP_CORE_DEBUG("Initializing Ellipse ({0}, {1}), ({2}, {3})", p1.x, p1.y, p2.x, p2.y);

        m_V1 = {{-1, -1}, {0, 0.55, 0.9}};
        m_V2 = {{1, -1}, {0, 0.55, 0.9}};
        m_V3 = {{1, 1}, {0, 0.55, 0.9}};
        m_V4 = {{-1, 1}, {0, 0.55, 0.9}};
    }

    uint32_t Ellipse::_draw(Window *window) const {
        return window->m_Renderer.drawEllipse(const_cast<Ellipse *>(this));
    }

    void Ellipse::_destroy() const {
        m_Window->m_Renderer.destroyEllipse(m_RendererID);
    }

    void Ellipse::_update() const {
        m_Window->m_Renderer.updateEllipse(m_RendererID, this);
    }
}

// Ellipse Methods
namespace gp {
    void Ellipse::setColor(const Color &color) {
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

    void Ellipse::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
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
