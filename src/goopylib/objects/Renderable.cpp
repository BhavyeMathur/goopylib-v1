#include "Renderable.h"

#if (GP_LOG_RENDERABLE != true) and (GP_LOG_RENDERABLE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_RENDERABLE
#endif

#if !GP_VALUE_CHECK_RENDERABLE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"

namespace gp {
    Renderable::Renderable(Point position, std::initializer_list<Point> points)
            : m_Position(position),
            m_Vertices(points.size()) {
        GP_CORE_DEBUG("gp::Renderable::Renderable(({0}, {1}), vertices={2})", position.x, position.y, points.size());

        m_Points = new Point[m_Vertices];
        int32_t i = 0;

        for (auto p: points) {
            m_Points[i] = p;
            i++;

            if (p.x > m_MaxX) {
                m_MaxX = p.x;
            }
            if (p.x < m_MinX) {
                m_MinX = p.x;
            }

            if (p.y > m_MaxY) {
                m_MaxY = p.y;
            }
            if (p.y < m_MinY) {
                m_MinY = p.y;
            }
        }

        m_Width = m_MaxX - m_MinX;
        m_Height = m_MaxY - m_MinY;
    }

    Renderable::Renderable(std::initializer_list<Point> points)
            : m_Vertices(points.size()) {
        GP_CORE_DEBUG("gp::Renderable::Renderable(vertices={0})", points.size());

        float sumX = 0;
        float sumY = 0;

        m_Points = new Point[m_Vertices];
        int32_t i = 0;

        for (auto p: points) {
            m_Points[i] = p;
            i++;

            if (p.x > m_MaxX) {
                m_MaxX = p.x;
            }
            if (p.x < m_MinX) {
                m_MinX = p.x;
            }

            if (p.y > m_MaxY) {
                m_MaxY = p.y;
            }
            if (p.y < m_MinY) {
                m_MinY = p.y;
            }

            sumX += p.x;
            sumY += p.y;
        }

        m_Position = {sumX / (float) m_Vertices, sumY / (float) m_Vertices};

        m_Width = m_MaxX - m_MinX;
        m_Height = m_MaxY - m_MinY;
    }

    void Renderable::draw(Window *window) {
        GP_CORE_DEBUG("gp::Renderable::draw({0})", window->getTitle());

        #if GP_ERROR_CHECKING
        if (window->m_IsDestroyed) {
            GP_RUNTIME_ERROR("window has been destroyed");
        }
        #endif

        if (m_Drawn) {
            _destroy();
        }

        m_RendererID = _draw(window);
        m_Window = window;
        m_Drawn = true;
    }

    void Renderable::destroy() {
        GP_CORE_INFO("gp::Renderable::destroy()");

        if (m_Drawn) {
            _destroy();

            m_Window = nullptr;
            m_Drawn = false;
            m_RendererID = 0;
        }
    }

    void Renderable::update() const {
        GP_CORE_TRACE("gp::Renderable::update()");

        if (m_Drawn) {
            _update();
        }
    }

    bool Renderable::boxContains(Point point) const {
        return boxContains(point.x, point.y);
    }

    bool Renderable::boxContains(float x, float y) const {
        GP_CORE_TRACE("gp::Renderable::boxContains({0}, {1})", x, y);
        return x <= m_MaxX and x >= m_MinX and y <= m_MaxY and y >= m_MinY;
    }

    bool Renderable::contains(Point point) const {
        return contains(point.x, point.y);
    }

    bool Renderable::contains(float x, float y) const {
        GP_CORE_TRACE("gp::Renderable::contains({0}, {1})", x, y);
        return boxContains(x, y) and _contains(x, y);  // early exit if box doesn't contain point
    }
}

// Getter & Setter Methods
namespace gp {
    bool Renderable::isDrawn() const {
        GP_CORE_TRACE("gp::Renderable::isDrawn()");
        return m_Drawn;
    }

    // Anchor
    void Renderable::setAnchor(float x, float y) {
        GP_CORE_DEBUG("gp::Renderable::setAnchor({0}, {1})", x, y);

        m_Position.x = x;
        m_Position.y = y;
    }

    void Renderable::resetAnchor() {
        GP_CORE_DEBUG("gp::Renderable::resetAnchor()");

        float sumX = 0;
        float sumY = 0;

        for (int i = 0; i < m_Vertices; i++) {
            Point p = m_Points[i];

            sumX += p.x;
            sumY += p.y;
        }

        m_Position = {sumX / (float) m_Vertices, sumY / (float) m_Vertices};
    }

    // Position
    void Renderable::move(float dx, float dy) {
        GP_CORE_DEBUG("gp::Renderable::move({0}, {1})", dx, dy);

        _move(dx, dy);

        m_MinX += dx;
        m_MaxX += dx;
        m_MinY += dy;
        m_MaxY += dy;

        m_Position.x += dx;
        m_Position.y += dy;

        update();
    }

    void Renderable::setX(float x) {
        GP_CORE_DEBUG("gp::Renderable::setX({0})", x);
        move(x - m_Position.x, 0);
    }

    float Renderable::getX() const {
        GP_CORE_TRACE("gp::Renderable::getX()");
        return m_Position.x;
    }

    void Renderable::setY(float y) {
        GP_CORE_DEBUG("gp::Renderable::setY({0})", y);
        move(0, y - m_Position.y);
    }

    float Renderable::getY() const {
        GP_CORE_TRACE("gp::Renderable::getY()");
        return m_Position.y;
    }

    void Renderable::setPosition(float x, float y) {
        GP_CORE_DEBUG("gp::Renderable::setPosition({0}, {1})", x, y);
        move(x - m_Position.x, y - m_Position.y);
    }

    Point Renderable::getPosition() const {
        GP_CORE_TRACE("gp::Renderable::getPosition()");
        return m_Position;
    }

    // Rotation
    void Renderable::rotate(float angle) {
        m_AngleDegrees += angle;
        angle /= 57.2957795131f;
        m_AngleRadians += angle;

        float sine = sin(angle);
        float cosine = cos(angle);

        _move(-m_Position.x, -m_Position.y);

        for (int i = 0; i < m_Vertices; i++) {
            Point p = m_Points[i];

            m_Points[i] = {p.x * cosine + p.y * sine,
                           p.y * cosine - p.x * sine};
        }

        _move(m_Position.x, m_Position.y);
        _calculateAttributes();

        m_SinAngle = sin(m_AngleRadians);
        m_CosAngle = cos(m_AngleRadians);

        update();
    }

    void Renderable::setRotation(float angle) {
        rotate(angle - m_AngleDegrees);
    }

    float Renderable::getRotation() const {
        GP_CORE_TRACE("gp::Renderable::getRotation()");
        return m_AngleDegrees;
    }

    // Scale
    void Renderable::scale(float factor) {
        scale(factor, factor);
    }

    void Renderable::scale(float xfactor, float yfactor) {
        _move(-m_Position.x, -m_Position.y);
        m_MinX -= m_Position.x;
        m_MaxX -= m_Position.x;
        m_MinY -= m_Position.y;
        m_MaxY -= m_Position.y;

        for (int i = 0; i < m_Vertices; i++) {
            m_Points[i].x *= xfactor;
            m_Points[i].y *= yfactor;
        }

        m_MinX *= xfactor;
        m_MaxX *= xfactor;
        m_MinY *= xfactor;
        m_MaxY *= xfactor;

        _move(m_Position.x, m_Position.y);
        m_MinX += m_Position.x;
        m_MaxX += m_Position.x;
        m_MinY += m_Position.y;
        m_MaxY += m_Position.y;

        m_Width = m_MaxX - m_MinX;
        m_Height = m_MaxY - m_MinY;

        m_xScale *= xfactor;
        m_yScale *= yfactor;

        _onScale(xfactor, yfactor);

        update();
    }

    void Renderable::setScaleX(float factor) {
        GP_CORE_DEBUG("gp::Renderable::setScaleX({0})", factor);
        scale(factor / m_xScale, 1);
    }

    void Renderable::setScaleY(float factor) {
        GP_CORE_DEBUG("gp::Renderable::setScaleY({0})", factor);
        scale(1, factor / m_xScale);
    }

    void Renderable::setScale(float factor) {
        GP_CORE_DEBUG("gp::Renderable::setScale({0})", factor);
        scale(factor / m_xScale, factor / m_yScale);
    }

    void Renderable::setScale(float xfactor, float yfactor) {
        GP_CORE_DEBUG("gp::Renderable::setScale({0}, {1})", xfactor, yfactor);
        scale(xfactor / m_xScale, yfactor / m_yScale);
    }

    Scale Renderable::getScale() const {
        GP_CORE_TRACE("gp::Renderable::getScale()");
        return {m_xScale, m_yScale};
    }

    // Dimensions
    void Renderable::setWidth(float width) {
        GP_CORE_DEBUG("gp::Renderable::setWidth({0})", width);
        scale(width / m_Width, 1);
    }

    float Renderable::getWidth() const {
        GP_CORE_TRACE("gp::Renderable::getWidth()");
        return m_Width;
    }

    void Renderable::setHeight(float height) {
        GP_CORE_DEBUG("gp::Renderable::setHeight({0})", height);
        scale(1, height / m_Height);
    }

    float Renderable::getHeight() const {
        GP_CORE_TRACE("gp::Renderable::getHeight()");
        return m_Height;
    }

    void Renderable::setSize(float width, float height) {
        scale(width / m_Width, height / m_Height);
    }

    // Visibility
    void Renderable::hide(bool hide) {
        GP_CORE_DEBUG("gp::Renderable::hide({0})", hide);

        if (m_Hidden == hide) {
            return;
        }

        m_Hidden = hide;
        update();
    }

    void Renderable::show() {
        GP_CORE_DEBUG("gp::Renderable::show()");
        hide(false);
    }

    bool Renderable::isHidden() const {
        GP_CORE_TRACE("gp::Renderable::isHidden()");
        return m_Hidden;
    }
}

// Internal Methods
namespace gp {
    void Renderable::_calculateAttributes() {
        GP_CORE_TRACE_ALL("gp::Renderable::_calculateAttributes()");

        m_MaxX = -FLT_MAX;
        m_MinX = FLT_MAX;
        m_MaxY = -FLT_MAX;
        m_MinY = FLT_MAX;

        for (int i = 0; i < m_Vertices; i++) {
            Point p = m_Points[i];

            if (p.x > m_MaxX) {
                m_MaxX = p.x;
            }
            if (p.x < m_MinX) {
                m_MinX = p.x;
            }

            if (p.y > m_MaxY) {
                m_MaxY = p.y;
            }
            if (p.y < m_MinY) {
                m_MinY = p.y;
            }
        }

        m_Width = m_MaxX - m_MinX;
        m_Height = m_MaxY - m_MinY;
    }

    void Renderable::_move(float x, float y) {
        GP_CORE_TRACE_ALL("gp::Renderable::_move({0}, {1})", x, y);

        for (int i = 0; i < m_Vertices; i++) {
            m_Points[i].x += x;
            m_Points[i].y += y;
        }
    }

    bool Renderable::_contains(float x, float y) const {
        GP_CORE_TRACE_ALL("gp::Renderable::_contains({0}, {1})", x, y);

        return true;
    }
}
