#include "RenderableObject.h"

namespace gp {
    RenderableObject::RenderableObject(Point position)
            : m_Position(position) {

    }

    void RenderableObject::draw(Window *window) {
        m_Window = window;
        m_Drawn = true;
        m_RendererID = _draw(window);
    }

    void RenderableObject::destroy() {
        _destroy();

        m_Window = nullptr;
        m_Drawn = false;
        m_RendererID = 0;
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
    }

    void RenderableObject::setPosition(float x, float y) {
        _move(x - m_Position.x, y - m_Position.y);

        m_Position.x = x;
        m_Position.y = y;
    }
}

// Getter Methods
namespace gp {
    bool RenderableObject::isDrawn() const {
        return m_Drawn;
    }

    Point RenderableObject::getPosition() const {
        return m_Position;
    }
}
