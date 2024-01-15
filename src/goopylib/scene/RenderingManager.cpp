#define GP_LOGGING_LEVEL 3

#include "RenderingManager.h"

#include "src/goopylib/core/Buffer.h"
#include "src/goopylib/texture/Texture2D.h"

#include "src/goopylib/objects/Triangle.h"
#include "src/goopylib/objects/Rectangle.h"
#include "src/goopylib/objects/Circle.h"
#include "src/goopylib/objects/Line.h"
#include "src/goopylib/objects/Image.h"

namespace gp {
    RenderingManager::RenderingManager(const Window &window, int width, int height, const char *title) :
            m_Width(width),
            m_Height(height),
            m_Title(title),
            m_Background(Color(255, 255, 255)),
            m_Camera((float) -width / 2.0f, (float) width / 2.0f, (float) -height / 2.0f, (float) height / 2.0f),
            m_Renderer(window),
            m_AlphaRenderer(window) {

    }

    void RenderingManager::init() {
        Texture2D::init();
//        TextureAtlas::init();

        m_Renderer.init();
        m_AlphaRenderer.init();

        m_SolidShader.compile();
        m_EllipseShader.compile();

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};

        m_TextureShader.compile();
        m_TextureShader.set("Texture", Texture2D::getTextureSlots(), samplers);

        m_ShaderUniform = unique_ptr<UniformBuffer>(new UniformBuffer({{ShaderDataType::Mat4, "PVMatrix"}}));
        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1);

        m_SolidShader.setUniformBlock(*m_ShaderUniform, "Projection", 0);
        m_EllipseShader.setUniformBlock(*m_ShaderUniform, "Projection", 0);
        m_TextureShader.setUniformBlock(*m_ShaderUniform, "Projection", 0);
    }

    void RenderingManager::render() {
        _enableDepthWriting();
        _updateBackground();

        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1, 0);
        m_Renderer.flush();

        _disableDepthWriting();
        m_AlphaRenderer.flush();
    }
}

namespace gp {
    // Width
    void RenderingManager::setWidth(int value) {
        GP_CORE_DEBUG("gp::RenderingManager::setWidth({1}) - '{0}'", m_Title, value);

        GP_CHECK_GT(value, 0, "Window width must be greater than 0")

        m_Width = value;
        _updateSize();
    }

    int RenderingManager::getWidth() const {
        GP_CORE_TRACE("gp::RenderingManager::getWidth() - '{0}'", m_Title);
        return m_Width;
    }

    // Height
    void RenderingManager::setHeight(int value) {
        GP_CORE_DEBUG("gp::RenderingManager::setHeight({1}) - '{0}'", m_Title, value);

        GP_CHECK_GT(value, 0, "Window height must be greater than 0")

        m_Height = value;
        _updateSize();
    }

    int RenderingManager::getHeight() const {
        GP_CORE_TRACE("gp::RenderingManager::getHeight() - '{0}'", m_Title);
        return m_Height;
    }

    // Background
    void RenderingManager::setBackground(const Color &value) {
        GP_CORE_DEBUG("gp::RenderingManager::setBackground({1}) - '{0}'", m_Title, value.toString());

        m_Background = value;
    }

    Color &RenderingManager::getBackground() {
        GP_CORE_TRACE("gp::RenderingManager::getBackground() - '{0}'", m_Title);
        return m_Background;
    }

    Camera &RenderingManager::getCamera() {
        GP_CORE_TRACE("gp::RenderingManager::getCamera() - '{0}'", m_Title);
        return m_Camera;
    }

    Point RenderingManager::toWorld(Point p) const {
        GP_CORE_TRACE_ALL("gp::RenderingManager::toWorld({1}, {2}) - '{0}'", m_Title, p.x, p.y);

        p.x /= (float) (m_Width >> 1);
        p.y /= (float) (m_Height >> 1);

        p.x -= 1;
        p.y = 1 - p.y;

        auto pos = m_Camera.m_InverseProjectionViewMatrix * glm::vec4(p.x, p.y, 0, 1.0);

        return {pos.x, pos.y};
    }

    Point RenderingManager::toScreen(Point p) const {
        GP_CORE_TRACE_ALL("gp::RenderingManager::toScreen({1}, {2}) - '{0}'", m_Title, p.x, p.y);

        auto pos = m_Camera.m_ProjectionViewMatrix * glm::vec4(p.x, p.y, 0, 1.0);

        const auto halfWidth = (float) (m_Width >> 1);
        const auto halfHeight = (float) (m_Height >> 1);

        pos.x *= halfWidth;
        pos.x += halfWidth;

        pos.y *= halfHeight;
        pos.y = halfHeight - pos.y;

        return {pos.x, pos.y};
    }
}

namespace gp {
    uint32_t RenderingManager::_drawRenderable(Renderable *object) {
        GP_CORE_TRACE("gp::RenderingManager::_drawRenderable()");

        const uint32_t ID = m_NextObjectID;
        m_NextObjectID++;

        GP_CORE_TRACE("gp::RenderingManager::_drawRenderable() - 0");

        Renderer& renderer = (object->isVisibleAndOpaque() ? m_Renderer : m_AlphaRenderer);

        GP_CORE_TRACE("gp::RenderingManager::_drawRenderable() - 1");
        switch (object->_getRenderableSubclass()) {
            case RenderableSubclass::Line:
                renderer.drawLine(ID, dynamic_cast<const Line *>(object));
                break;
            case RenderableSubclass::Triangle:
                renderer.drawTriangle(ID, dynamic_cast<const Triangle *>(object));
                break;
            case RenderableSubclass::Quad:
                GP_CORE_TRACE("gp::RenderingManager::_drawRenderable() - 2");
                renderer.drawQuad(ID, dynamic_cast<const Quad *>(object));
                break;
            case RenderableSubclass::Ellipse:
                renderer.drawEllipse(ID, dynamic_cast<const Ellipse *>(object));
                break;
            case RenderableSubclass::TexturedQuad:
                GP_CORE_TRACE("gp::RenderingManager::_drawRenderable() - 3");
                renderer.drawTexturedQuad(ID, dynamic_cast<TexturedQuad *>(object));
                break;
        }

        m_ObjectToIsOpaque[ID] = object->isVisibleAndOpaque();
        return ID;
    }

    void RenderingManager::_undrawRenderable(Renderable *object) {
        uint32_t ID = object->m_RendererID;
        GP_CORE_TRACE("gp::RenderingManager::destroy({0})", ID);

        Renderer& renderer = (m_ObjectToIsOpaque[ID] ? m_Renderer : m_AlphaRenderer);

        switch (object->_getRenderableSubclass()) {
            case RenderableSubclass::Line:
                renderer.destroyLine(ID);
                break;
            case RenderableSubclass::Triangle:
                renderer.destroyTriangle(ID);
                break;
            case RenderableSubclass::Quad:
                renderer.destroyQuad(ID);
                break;
            case RenderableSubclass::Ellipse:
                renderer.destroyEllipse(ID);
                break;
            case RenderableSubclass::TexturedQuad:
                renderer.destroyTexturedQuad(ID);
                break;
        }
        
        m_ObjectToIsOpaque.erase(ID);
    }

    void RenderingManager::_updateRenderable(Renderable *object) {
        uint32_t ID = object->m_RendererID;
        GP_CORE_TRACE("gp::RenderingManager::_updateRenderable({0})", ID);

        Renderer& renderer = (m_ObjectToIsOpaque[ID] ? m_Renderer : m_AlphaRenderer);

        if (m_ObjectToIsOpaque[ID] != object->isVisibleAndOpaque()) {
            _undrawRenderable(object);

            ID = _drawRenderable(object);
            object->m_RendererID = ID;

            m_ObjectToIsOpaque[ID] = object->isVisibleAndOpaque();
            return;
        }

        switch (object->_getRenderableSubclass()) {
            case RenderableSubclass::Line:
                renderer.updateLine(ID, dynamic_cast<const Line *>(object));
                return;
            case RenderableSubclass::Triangle:
                renderer.updateTriangle(ID, dynamic_cast<const Triangle *>(object));
                return;
            case RenderableSubclass::Quad:
                renderer.updateQuad(ID, dynamic_cast<const Quad *>(object));
                return;
            case RenderableSubclass::Ellipse:
                renderer.updateEllipse(ID, dynamic_cast<const Ellipse *>(object));
                return;
            case RenderableSubclass::TexturedQuad:
                renderer.updateTexturedQuad(ID, dynamic_cast<TexturedQuad *>(object));
                return;
        }
    }
}
