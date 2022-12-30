#include "Line.h"

#if (GP_LOG_LINE != true) and (GP_LOG_LINE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_LINE
#endif

#if !GP_VALUE_CHECK_LINE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"

// Core Methods
namespace gp {
    Line::Line(Point p1, Point p2)
            : Renderable({p1, p2}),
            m_V1({{0, 0, 0}}),
            m_V2({{0, 0, 0}}) {

    }

    uint32_t Line::_draw(Window *window) const {
        return window->m_Renderer.drawLine(const_cast<Line *>(this));
    }

    void Line::_destroy() const {
        m_Window->m_Renderer.destroyLine(m_RendererID);
    }

    void Line::_update() const {
        m_Window->m_Renderer.updateLine(m_RendererID, this);
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
