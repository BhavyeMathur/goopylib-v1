#include "RenderableObject.h"

namespace gp {
    RenderableObject::RenderableObject(Point position, std::initializer_list<Point> points)
            : m_Position(position),
            m_Vertices(points.size()) {

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

    RenderableObject::RenderableObject(std::initializer_list<Point> points)
            : m_Vertices(points.size()) {

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

    void RenderableObject::draw(Window *window) {
        if (m_Drawn) {
            _destroy();
        }

        m_RendererID = _draw(window);
        m_Window = window;
        m_Drawn = true;
    }

    void RenderableObject::destroy() {
        if (m_Drawn) {
            _destroy();

            m_Window = nullptr;
            m_Drawn = false;
            m_RendererID = 0;
        }
    }

    void RenderableObject::update() const {
        if (m_Drawn) {
            _update();
        }
    }

    bool RenderableObject::boxContains(Point point) const {
        return point.x <= m_MaxX and point.x >= m_MinX and point.y <= m_MaxY and point.y >= m_MinY;
    }

    bool RenderableObject::contains(Point point) const {
        return boxContains(point) and _contains(point.x, point.y);  // early exit if box doesn't contain point
    }
}

// Getter & Setter Methods
namespace gp {
    bool RenderableObject::isDrawn() const {
        return m_Drawn;
    }

    // Anchor
    void RenderableObject::setAnchor(float x, float y) {
        m_Position.x = x;
        m_Position.y = y;
    }

    void RenderableObject::resetAnchor() {
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
    void RenderableObject::move(float dx, float dy) {
        _move(dx, dy);

        m_MinX += dx;
        m_MaxX += dx;
        m_MinY += dy;
        m_MaxY += dy;

        m_Position.x += dx;
        m_Position.y += dy;

        update();
    }

    void RenderableObject::setPosition(float x, float y) {
        move(x - m_Position.x, y - m_Position.y);
    }

    Point RenderableObject::getPosition() const {
        return m_Position;
    }

    // Rotation
    void RenderableObject::rotate(float angle) {
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

    void RenderableObject::setRotation(float angle) {
        rotate(angle - m_AngleDegrees);
    }

    float RenderableObject::getRotation() const {
        return m_AngleDegrees;
    }

    // Scale
    void RenderableObject::scale(float factor) {
        scale(factor, factor);
    }

    void RenderableObject::scale(float xfactor, float yfactor) {
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

    void RenderableObject::setScale(float xfactor, float yfactor) {
        scale(xfactor / m_xScale, yfactor / m_yScale);
    }

    Scale RenderableObject::getScale() const {
        return {m_xScale, m_yScale};
    }

    // Dimensions
    void RenderableObject::setWidth(float width) {
        scale(width / m_Width, 1);
    }

    float RenderableObject::getWidth() const {
        return m_Width;
    }

    void RenderableObject::setHeight(float height) {
        scale(1, height / m_Height);
    }

    float RenderableObject::getHeight() const {
        return m_Height;
    }

    void RenderableObject::setSize(float width, float height) {
        scale(width / m_Width, height / m_Height);
    }

    // Visibility
    void RenderableObject::hide(bool hidden) {
        if (m_Hidden == hidden) {
            return;
        }

        m_Hidden = hidden;
        update();
    }

    void RenderableObject::show() {
        hide(false);
    }

    bool RenderableObject::isHidden() const {
        return m_Hidden;
    }
}

// Internal Methods
namespace gp {
    void RenderableObject::_calculateAttributes() {
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

    void RenderableObject::_move(float x, float y) {
        for (int i = 0; i < m_Vertices; i++) {
            m_Points[i].x += x;
            m_Points[i].y += y;
        }
    }

    bool RenderableObject::_contains(float x, float y) const {
        return true;
    };
}
