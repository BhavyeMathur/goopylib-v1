#include "src/goopylib/scene/RenderingManager.h"

namespace gp {
    void RenderingManager::_updateBackground() {
        glClearColor(m_Background.getRedf(),
                     m_Background.getGreenf(),
                     m_Background.getBluef(), 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderingManager::_enableDepthWriting() {
        glDepthMask(true);
    }

    void RenderingManager::_disableDepthWriting() {
        glDepthMask(false);
    }
}
