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
            else if (p.x < m_MinX) {
                m_MinX = p.x;
            }

            if (p.y > m_MaxY) {
                m_MaxY = p.y;
            }
            else if (p.y < m_MinY) {
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
            else if (p.x < m_MinX) {
                m_MinX = p.x;
            }

            if (p.y > m_MaxY) {
                m_MaxY = p.y;
            }
            else if (p.y < m_MinY) {
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

    void RenderableObject::move(float dx, float dy) {
        _move(dx, dy);

        m_Position.x += dx;
        m_Position.y += dy;

        m_MinX += dx;
        m_MaxX += dx;
        m_MinY += dy;
        m_MaxY += dy;

        update();
    }

    void RenderableObject::rotate(float angle) {
        angle /= 57.2957795131f;

        _move(-m_Position.x, -m_Position.y);
        _rotate(sin(angle), cos(angle));
        _move(m_Position.x, m_Position.y);

        m_Angle += angle;

        update();
    }

    void RenderableObject::scale(float factor) {
        scale(factor, factor);
    }

    void RenderableObject::scale(float xfactor, float yfactor) {
        _move(-m_Position.x, -m_Position.y);
        _scale(xfactor, yfactor);
        _move(m_Position.x, m_Position.y);

        m_xScale *= xfactor;
        m_yScale *= yfactor;

        m_Width *= xfactor;
        m_Height *= yfactor;

        update();
    }

    bool RenderableObject::contains(Point point) {
        return contains(point.x, point.y);
    }

    bool RenderableObject::contains(float x, float y) {
        return _contains(x, y);
    }
}

// Getter & Setter Methods
namespace gp {
    bool RenderableObject::isDrawn() const {
        return m_Drawn;
    }

    void RenderableObject::setAnchor(float x, float y) {
        m_Position.x = x;
        m_Position.y = y;
    }

    void RenderableObject::setPosition(float x, float y) {
        _move(x - m_Position.x, y - m_Position.y);

        m_Position.x = x;
        m_Position.y = y;

        update();
    }

    Point RenderableObject::getPosition() const {
        return m_Position;
    }

    float RenderableObject::getRotation() const {
        return m_Angle;
    }

    Scale RenderableObject::getScale() const {
        return {m_xScale, m_yScale};
    }
}
