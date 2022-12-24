#include "Ellipse.h"

// Core Methods
namespace gp {
    Ellipse::Ellipse(Point position, float xRadius, float yRadius)
            : RenderableObject(position, {{position.x - xRadius, position.y - yRadius},
                                          {position.x + xRadius, position.y - yRadius},
                                          {position.x + xRadius, position.y + yRadius},
                                          {position.x - xRadius, position.y + yRadius}}) {
        GP_CORE_DEBUG("Initializing Ellipse at ({0}, {1}), xRadius={3}, yRadius={4}",
                      position.x, position.y, xRadius, yRadius);
    }

    Ellipse::Ellipse(Point p1, Point p2)
            : RenderableObject({{p1.x, p1.y}, {p2.x, p1.y}, {p2.x, p2.y}, {p1.x, p2.y}}) {
        GP_CORE_DEBUG("Initializing Ellipse ({0}, {1}), ({2}, {3})", p1.x, p1.y, p2.x, p2.y);
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
        setColor(color, color, color, color);
    }

    void Ellipse::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        m_V1.color = {color1.getRedf(), color1.getGreenf(), color1.getBluef(), color1.getAlpha()};
        m_V2.color = {color2.getRedf(), color2.getGreenf(), color2.getBluef(), color2.getAlpha()};
        m_V3.color = {color3.getRedf(), color3.getGreenf(), color3.getBluef(), color3.getAlpha()};
        m_V4.color = {color4.getRedf(), color4.getGreenf(), color4.getBluef(), color4.getAlpha()};

        update();
    }

    void Ellipse::setTransparency(float value) {
        setTransparency(value, value, value, value);
    }

    void Ellipse::setTransparency(float v1, float v2, float v3, float v4) {
        m_V1.color.alpha = v1;
        m_V2.color.alpha = v2;
        m_V3.color.alpha = v3;
        m_V4.color.alpha = v4;

        update();
    }
}
