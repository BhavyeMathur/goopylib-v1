#include "RenderableObject.h"

namespace gp {
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
}
