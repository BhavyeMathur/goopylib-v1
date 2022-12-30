#include "Ellipse.h"

#if (GP_LOG_ELLIPSE != true) and (GP_LOG_ELLIPSE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_ELLIPSE
#endif

#if !GP_VALUE_CHECK_ELLIPSE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


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
            : Renderable({{p1.x, p1.y}, {p2.x, p1.y}, {p2.x, p2.y}, {p1.x, p2.y}}),
            m_Radius1(abs(p2.x - p1.x) / 2),
            m_Radius2(abs(p2.y - p1.y) / 2){
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
}

// Ellipse Methods
namespace gp {
    void Ellipse::setColor(const Color &color) {
        setColor(color, color, color, color);
    }

    void Ellipse::setColor(const Color &color1, const Color &color2, const Color &color3, const Color &color4) {
        m_V1.color = color1.getRGBAf();
        m_V2.color = color2.getRGBAf();
        m_V3.color = color3.getRGBAf();
        m_V4.color = color4.getRGBAf();

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

        m_V1.color.alpha = v1;
        m_V2.color.alpha = v2;
        m_V3.color.alpha = v3;
        m_V4.color.alpha = v4;

        update();
    }
}
