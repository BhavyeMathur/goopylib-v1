#define GP_LOGGING_LEVEL 3

#include "Renderer.h"

#include "objects/Triangle.h"
#include "objects/Quad.h"
#include "objects/Ellipse.h"
#include "objects/TexturedQuad.h"

namespace gp {
    Renderer::Renderer(const RenderingManager &window)
            : m_Window(window),
              m_TriangleBatch({{{ShaderDataType::Float2, "position"},
                                {ShaderDataType::Float, "z"},
                                {ShaderDataType::Float4, "color"}},
                               6, 4, m_Window.m_SolidShader}),
              m_QuadBatch({{
                                   {ShaderDataType::Float2, "position"},
                                   {ShaderDataType::Float, "z"},
                                   {ShaderDataType::Float4, "color"}
                           }, 6, 4, m_Window.m_SolidShader}),
              m_EllipseBatch({{
                                      {ShaderDataType::Float2, "position"},
                                      {ShaderDataType::Float, "z"},
                                      {ShaderDataType::Float2, "localCoord"},
                                      {ShaderDataType::Float4, "color"}
                              }, 6, 4, m_Window.m_EllipseShader}),
              m_TextureRenderer(m_Window.m_TextureShader) {
    }

    void Renderer::init() {
        GP_CORE_INFO("Rendering::init() initializing Renderer");

        m_TriangleBatch.init();
        m_QuadBatch.init();
        m_EllipseBatch.init();
        m_TextureRenderer.init();
    }

    void Renderer::draw(uint32_t ID, const shared_ptr<gp::Renderable> &object) {
        switch (object->_getRenderableSubclass()) {
            case RenderableSubclass::Triangle:
                m_TriangleBatch.drawObject(ID, std::dynamic_pointer_cast<Triangle>(object));
                break;
            case RenderableSubclass::Quad:
                m_QuadBatch.drawObject(ID, std::dynamic_pointer_cast<Quad>(object));
                break;
            case RenderableSubclass::Ellipse:
                m_EllipseBatch.drawObject(ID, std::dynamic_pointer_cast<Ellipse>(object));
                break;
            case RenderableSubclass::TexturedQuad:
                m_TextureRenderer.drawObject(ID, std::dynamic_pointer_cast<TexturedQuad>(object));
                break;
        }
    }

    void Renderer::destroy(uint32_t ID, const shared_ptr<gp::Renderable> &object) {
        switch (object->_getRenderableSubclass()) {
            case RenderableSubclass::Triangle:
                m_TriangleBatch.destroyObject(ID);
                return;
            case RenderableSubclass::Quad:
                m_QuadBatch.destroyObject(ID);
                return;
            case RenderableSubclass::Ellipse:
                m_EllipseBatch.destroyObject(ID);
                return;
            case RenderableSubclass::TexturedQuad:
                m_TextureRenderer.destroyObject(ID);
                return;
        }
    }

    void Renderer::update(uint32_t ID, const shared_ptr<gp::Renderable> &object) {
        switch (object->_getRenderableSubclass()) {
            case RenderableSubclass::Triangle:
                m_TriangleBatch.updateObject(ID, std::dynamic_pointer_cast<Triangle>(object));
                break;
            case RenderableSubclass::Quad:
                m_QuadBatch.updateObject(ID, std::dynamic_pointer_cast<Quad>(object));
                break;
            case RenderableSubclass::Ellipse:
                m_EllipseBatch.updateObject(ID, std::dynamic_pointer_cast<Ellipse>(object));
                break;
            case RenderableSubclass::TexturedQuad:
                m_TextureRenderer.updateObject(ID, std::dynamic_pointer_cast<TexturedQuad>(object));
        }
    }

    void Renderer::flush() {
        GP_CORE_TRACE_ALL("gp::Renderer::flush()");

        m_TriangleBatch.draw();
        m_QuadBatch.draw();
        m_EllipseBatch.draw();
        m_TextureRenderer.draw();
    }
}
