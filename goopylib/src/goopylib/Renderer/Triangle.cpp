#include "Triangle.h"

namespace gp {

    Triangle::Triangle(Point p1, Point p2, Point p3)
            : m_Position{(p1.x + p2.x + p3.x) / 3.0f,
                         (p1.y + p2.y + p3.y) / 3.0f},
              m_P1(p1),
              m_P2(p2),
              m_P3(p3) {
        GP_CORE_DEBUG("Initializing Triangle ({0}, {1}), ({2}, {3}), ({4}, {5})", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    }

    Triangle::~Triangle() = default;

    void Triangle::draw(const Ref<Window> &window) {
        m_Window = window;
        m_Drawn = true;
        m_RendererID = window->drawTriangle(m_P1, m_P2, m_P3);
    }

    void Triangle::destroy() {
        m_Window->destroyTriangle(m_RendererID);

        m_Window = nullptr;
        m_Drawn = false;
        m_RendererID = 0;
    }

    Ref<Triangle> Triangle::create(Point p1, Point p2, Point p3) {
        return CreateRef<Triangle>(p1, p2, p3);
    }
}
