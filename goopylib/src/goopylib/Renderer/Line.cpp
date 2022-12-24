#include "Line.h"

// Core Methods
namespace gp {
    Line::Line(Point p1, Point p2)
            : RenderableObject({(p1.x + p2.x) / 2, (p1.y + p2.y) / 2}),
            m_V1(p1, {0, 0, 0, 1}),
            m_V2(p2, {0, 0, 0, 1}) {

    }

    void Line::resetAnchor() {
        m_Position.x = (m_V1.point.x + m_V2.point.x) / 2.0f;
        m_Position.y = (m_V1.point.y + m_V2.point.y) / 2.0f;
    }

    uint32_t Line::_draw(Window *window) const {
        return window->m_Renderer.drawLine(m_V1, m_V2);
    }

    void Line::_destroy() const {
        m_Window->m_Renderer.destroyLine(m_RendererID);
    }

    void Line::_update() const {
        m_Window->m_Renderer.updateLine(m_RendererID, m_V1, m_V2);
    }

    void Line::_move(float dx, float dy) {
        m_V1.point.x += dx;
        m_V1.point.y += dy;

        m_V2.point.x += dx;
        m_V2.point.y += dy;
    }

    void Line::_rotate(float sin, float cos) {
        m_V1.point = {m_V1.point.x * cos + m_V1.point.y * sin,
                      m_V1.point.y * cos - m_V1.point.x * sin};

        m_V2.point = {m_V2.point.x * cos + m_V2.point.y * sin,
                      m_V2.point.y * cos - m_V2.point.x * sin};
    }

    void Line::_scale(float xfactor, float yfactor) {
        m_V1.point.x *= xfactor;
        m_V1.point.y *= yfactor;

        m_V2.point.x *= xfactor;
        m_V2.point.y *= yfactor;
    }
}

// Getter & Setter methods
namespace gp {
    void Line::setColor(const Color &color) {
        m_V1.color = {color.getRedf(), color.getGreenf(), color.getBluef(), color.getAlpha()};
        m_V2.color = {color.getRedf(), color.getGreenf(), color.getBluef(), color.getAlpha()};

        update();
    }

    void Line::setColor(const Color &color1, const Color &color2) {
        m_V1.color = {color1.getRedf(), color1.getGreenf(), color1.getBluef(), color1.getAlpha()};
        m_V2.color = {color2.getRedf(), color2.getGreenf(), color2.getBluef(), color2.getAlpha()};

        update();
    }

    void Line::setTransparency(float value) {
        m_V1.color.alpha = value;
        m_V2.color.alpha = value;

        update();
    }

    void Line::setTransparency(float value1, float value2) {
        m_V1.color.alpha = value1;
        m_V2.color.alpha = value2;

        update();
    }
}

// Static Methods
namespace gp {
    float Line::s_Width = 1;

    float Line::s_MinWidth = 0;
    float Line::s_MaxWidth = FLT_MAX;

    void Line::init() {
        #if GP_USING_OPENGL
        GLfloat lineWidthRange[2] = {0.0f, 0.0f};
        glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);

        s_MinWidth = lineWidthRange[0];
        s_MaxWidth = lineWidthRange[1];
        #endif
    }

    void Line::setWidth(float value) {
        #if GP_ERROR_CHECKING
        if (value > s_MaxWidth or value < s_MinWidth) {
            GP_CORE_WARN("Line width {0} not supported, must be between {1} and {2}", value, s_MinWidth, s_MaxWidth);
        }
        #endif

        #if GP_USING_OPENGL
        glLineWidth(value);
        #else
        GP_CORE_ERROR("Line width not supported on platform");
        #endif

        s_Width = value;
    }

    float Line::getWidth() {
        return s_Width;
    }
}
