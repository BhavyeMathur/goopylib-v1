#include "RenderingManager.h"

#include "src/goopylib/texture/TextureAtlas.h"
#include "src/goopylib/shader/ShaderFiles.h"
#include "src/goopylib/objects/Line.h"

namespace gp {
    RenderingManager::RenderingManager(const Window& window, int width, int height) :
            m_Renderer(window),
            m_Camera(-width / 2, width / 2, -height / 2, height / 2) {

    }

    void RenderingManager::init() {
        Line::init();
        Texture2D::init();
        TextureAtlas::init();

        m_Renderer.init();

        GP_CORE_TRACE("Rendering::init() initializing Solid Shader");
        m_SolidShader = CreateRef<Shader>(solidVertexShader, solidFragmentShader);

        GP_CORE_TRACE("Rendering::init() initializing Ellipse Shader");
        m_EllipseShader = CreateRef<Shader>(ellipseVertexShader, ellipseFragmentShader);

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};

        GP_CORE_TRACE("Rendering::init() initializing texture Shader");
        m_TextureShader = CreateRef<Shader>(textureVertexShader, textureFragmentShader);
        m_TextureShader->set("Texture", Texture2D::getTextureSlots(), samplers);

        m_ShaderUniform = Ref<UniformBuffer>(new UniformBuffer({{ShaderDataType::Mat4, "PVMatrix"}}));
        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1);

        m_SolidShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        m_EllipseShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        m_TextureShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
    }

    void RenderingManager::render() {
         m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1, 0);
         m_Renderer.flush();
    }
}

namespace gp {
    uint32_t RenderingManager::drawLine(Line *object) {
        return m_Renderer.drawLine(object);
    }

    void RenderingManager::destroyLine(uint32_t ID) {
        return m_Renderer.destroyLine(ID);
    }

    void RenderingManager::updateLine(uint32_t ID, const Line *object) {
        return m_Renderer.updateLine(ID, object);
    }

    uint32_t RenderingManager::drawTriangle(Triangle *object) {
        return m_Renderer.drawTriangle(object);
    }

    void RenderingManager::destroyTriangle(uint32_t ID) {
        return m_Renderer.destroyTriangle(ID);
    }

    void RenderingManager::updateTriangle(uint32_t ID, const Triangle *object) {
        return m_Renderer.updateTriangle(ID, object);
    }

    uint32_t RenderingManager::drawQuad(Quad *object) {
        return m_Renderer.drawQuad(object);
    }

    void RenderingManager::destroyQuad(uint32_t ID) {
        return m_Renderer.destroyQuad(ID);
    }

    void RenderingManager::updateQuad(uint32_t ID, const Quad *object) {
        return m_Renderer.updateQuad(ID, object);
    }

    uint32_t RenderingManager::drawEllipse(Ellipse *object) {
        return m_Renderer.drawEllipse(object);
    }

    void RenderingManager::destroyEllipse(uint32_t ID) {
        return m_Renderer.destroyEllipse(ID);
    }

    void RenderingManager::updateEllipse(uint32_t ID, const Ellipse *object) {
        return m_Renderer.updateEllipse(ID, object);
    }

    uint32_t RenderingManager::drawTexturedQuad(TexturedQuad *object) {
        return m_Renderer.drawTexturedQuad(object);
    }

    void RenderingManager::destroyTexturedQuad(uint32_t ID) {
        return m_Renderer.destroyTexturedQuad(ID);
    }

    void RenderingManager::updateTexturedQuad(uint32_t ID, const TexturedQuad *object) {
        return m_Renderer.updateTexturedQuad(ID, object);
    }
}
