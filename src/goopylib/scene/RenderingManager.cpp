#define GP_LOGGING_LEVEL 3

#include "RenderingManager.h"

#include "src/goopylib/core/Buffer.h"
#include "src/goopylib/texture/TextureAtlas.h"
#include "src/goopylib/shader/ShaderFiles.h"

#include "src/goopylib/objects/Triangle.h"
#include "src/goopylib/objects/Rectangle.h"
#include "src/goopylib/objects/Circle.h"
#include "src/goopylib/objects/Line.h"
#include "src/goopylib/objects/Image.h"

namespace gp {
    RenderingManager::RenderingManager(const Window &window, int width, int height) :
            m_Width(width),
            m_Height(height),
            m_Background(Color(255, 255, 255)),
            m_Camera(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f),
            m_Renderer(window) {

    }

    void RenderingManager::init() {
        Line::init();
        Texture2D::init();
        TextureAtlas::init();

        m_Renderer.init();

        GP_CORE_TRACE("Rendering::init() initializing Solid Shader");
        m_SolidShader = CreateScope<Shader>(solidVertexShader, solidFragmentShader);

        GP_CORE_TRACE("Rendering::init() initializing Ellipse Shader");
        m_EllipseShader = CreateScope<Shader>(ellipseVertexShader, ellipseFragmentShader);

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};

        GP_CORE_TRACE("Rendering::init() initializing texture Shader");
        m_TextureShader = CreateScope<Shader>(textureVertexShader, textureFragmentShader);
        m_TextureShader->set("Texture", Texture2D::getTextureSlots(), samplers);

        m_ShaderUniform = Scope<UniformBuffer>(new UniformBuffer({{ShaderDataType::Mat4, "PVMatrix"}}));
        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1);

        m_SolidShader->setUniformBlock(*m_ShaderUniform, "Projection", 0);
        m_EllipseShader->setUniformBlock(*m_ShaderUniform, "Projection", 0);
        m_TextureShader->setUniformBlock(*m_ShaderUniform, "Projection", 0);
    }

    void RenderingManager::render() {
        _updateBackground();

        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1, 0);
        m_Renderer.flush();
    }
}

namespace gp {
    // Width
    void RenderingManager::setWidth(int value) {
        GP_CORE_DEBUG("gp::RenderingManager::setWidth({1}) - '{0}'", m_Title, value);

        GP_CHECK_GT(value, 0, "Window width must be greater than 0");

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

        GP_CHECK_GT(value, 0, "Window height must be greater than 0");

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

    Point RenderingManager::toWorld(Point p) {
        GP_CORE_TRACE_ALL("gp::RenderingManager::toWorld({1}, {2}) - '{0}'", m_Title, p.x, p.y);

        p.x /= (float) (m_Width >> 1);
        p.y /= (float) (m_Height >> 1);

        p.x -= 1;
        p.y = 1 - p.y;

        auto pos = m_Camera.m_InverseProjectionViewMatrix * glm::vec4(p.x, p.y, 0, 1.0);

        return {pos.x, pos.y};
    }

    Point RenderingManager::toScreen(Point p) {
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
        if (object->isOpaque()) {

        }
        return m_Renderer.drawTexturedQuad(object);
    }

    void RenderingManager::destroyTexturedQuad(uint32_t ID) {
        return m_Renderer.destroyTexturedQuad(ID);
    }

    void RenderingManager::updateTexturedQuad(uint32_t ID, const TexturedQuad *object) {
        return m_Renderer.updateTexturedQuad(ID, object);
    }
}
