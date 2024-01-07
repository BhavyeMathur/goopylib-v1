#define GP_LOGGING_LEVEL 3
#include "Line.h"

// Core Methods
namespace gp {
    Line::Line(Point p1, Point p2)
            : Renderable({p1, p2}) {

    }

    uint32_t Line::_draw(Window &window) {
        return window.drawLine(this);
    }

    void Line::_destroy() const {
        m_Window->destroyLine(m_RendererID, this);
    }

    void Line::_update() {
        m_Window->updateLine(m_RendererID, this);
    }
}

// Getter & Setter methods
namespace gp {
    void Line::setColor(const Color &color) {
        m_V1.color = color.getRGBAf();
        m_V2.color = color.getRGBAf();

        update();
    }

    void Line::setColor(const Color &color1, const Color &color2) {
        m_V1.color = color1.getRGBAf();
        m_V2.color = color2.getRGBAf();

        update();
    }

    void Line::setColor(const char *hexstring, float alpha) {
        m_V1.color = Color(hexstring, alpha).getRGBAf();
        m_V2.color = m_V1.color;

        update();
    }

    void Line::setColor(const char *hex1, const char *hex2) {
        m_V1.color = Color(hex1).getRGBAf();
        m_V2.color = Color(hex2).getRGBAf();

        update();
    }

    void Line::setColor(int red, int green, int blue, float alpha) {
        m_V1.color = Color(red, green, blue, alpha).getRGBAf();
        m_V2.color = m_V1.color;

        update();
    }

    void Line::setTransparency(float value) {
        m_V1.color.alpha = value;
        m_V2.color.alpha = value;

        update();
    }

    void Line::setTransparency(float value1, float value2) {
        GP_CHECK_INCLUSIVE_RANGE(value1, 0, 1, "transparency must be between 0 and 1");
        GP_CHECK_INCLUSIVE_RANGE(value2, 0, 1, "transparency must be between 0 and 1");

        m_V1.color.alpha = value1;
        m_V2.color.alpha = value2;

        update();
    }

    Float2 Line::getTransparency() {
        return {m_V1.color.alpha, m_V2.color.alpha};
    }

    bool Line::isOpaque() const {
        return (m_V1.color.alpha == 1) && (m_V2.color.alpha == 1);
    }
}

// Static Methods
namespace gp {
    float Line::s_Width = 1;

    float Line::s_MinWidth = 0;
    float Line::s_MaxWidth = FLT_MAX;

    void Line::setThickness(float value) {
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

    float Line::getThickness() {
        return s_Width;
    }
}
