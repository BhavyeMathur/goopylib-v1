#include "Triangle.h"

#if (GP_LOG_TRIANGLE != true) and (GP_LOG_TRIANGLE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_TRIANGLE
#endif

#if !GP_VALUE_CHECK_TRIANGLE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"

// Core Methods
namespace gp {
    Triangle::Triangle(Point p1, Point p2, Point p3)
            : Renderable({p1, p2, p3}),
              m_V1({{0, 0.55, 0.9}}),
              m_V2({{0, 0.55, 0.9}}),
              m_V3({{0, 0.55, 0.9}}) {
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
