#define GP_LOGGING_LEVEL 3

#include "Renderer.h"

#include "core/VertexArray.h"
#include "texture/TextureBuffer.h"

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
                              }, 6, 4, m_Window.m_EllipseShader}) {
    }

    Renderer::~Renderer() = default;

    void Renderer::init() {
        GP_CORE_INFO("Rendering::init() initializing Renderer");

        m_TriangleBatch.init();
        m_QuadBatch.init();
        m_EllipseBatch.init();
    }

    void Renderer::_createTexturedBuffer() {
        GP_CORE_TRACE("Renderer::_createTexturedBuffer() creating TexturedQuad buffer");

        m_TexturedQuadBatches.emplace_back(BufferLayout{{
                                                                {ShaderDataType::Float2, "position"},
                                                                {ShaderDataType::Float, "z"},
                                                                {ShaderDataType::Float4, "color"},
                                                                {ShaderDataType::Float2, "texCoord"},
                                                                {ShaderDataType::Int, "texSlot"},
                                                        }}, 6, 4, m_Window.m_TextureShader);
        m_TexturedQuadBatches.back().init();
    }

    void Renderer::drawTriangle(uint32_t ID, const shared_ptr<Triangle> &object) {
        m_TriangleBatch.drawObject(ID, object);
    }

    void Renderer::destroyTriangle(uint32_t ID) {
        m_TriangleBatch.destroyObject(ID);
    }

    void Renderer::updateTriangle(uint32_t ID, const shared_ptr<Triangle> &object) {
        m_TriangleBatch.updateObject(ID, object);
    }

    void Renderer::drawQuad(uint32_t ID, const shared_ptr<Quad> &object) {
        m_QuadBatch.drawObject(ID, object);
    }

    void Renderer::destroyQuad(uint32_t ID) {
        m_QuadBatch.destroyObject(ID);
    }

    void Renderer::updateQuad(uint32_t ID, const shared_ptr<Quad> &object) {
        m_QuadBatch.updateObject(ID, object);
    }

    void Renderer::drawEllipse(uint32_t ID, const shared_ptr<Ellipse> &object) {
        m_EllipseBatch.drawObject(ID, object);
    }

    void Renderer::destroyEllipse(uint32_t ID) {
        m_EllipseBatch.destroyObject(ID);
    }

    void Renderer::updateEllipse(uint32_t ID, const shared_ptr<Ellipse> &object) {
        m_EllipseBatch.updateObject(ID, object);
    }

    void Renderer::drawTexturedQuad(uint32_t ID, const shared_ptr<TexturedQuad> &object) {
        GP_CORE_DEBUG("gp::Renderer::drawTexturedQuad({0})", ID);

        uint32_t texIndex, texSlot;

        if (m_TexturesCache.contains(object->getTextureName())) {
            GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - using cached texture '{0}'",
                          object->getTextureName());
            texIndex = m_TexturesCache[object->getTextureName()].index;
            texSlot = texIndex % 16;
        } else {
            GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - no cached texture '{0}'",
                          object->getTextureName());

            auto bitmap = object->getBitmap();
            texIndex = _cacheTexture(object->getTextureName(), *bitmap);
            texSlot = texIndex % 16;

            if (texSlot == 0) {
                _createTexturedBuffer();
            }
        }

        GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - texIndex={0}, texSlot={1}", texIndex, texSlot);

        object->m_VertexAttribs[0].texSlot = texSlot;
        object->m_VertexAttribs[1].texSlot = texSlot;
        object->m_VertexAttribs[2].texSlot = texSlot;
        object->m_VertexAttribs[3].texSlot = texSlot;

        const uint32_t batch = texIndex / TextureBuffer::getTextureSlots();
        m_TexturedQuadToBatch.insert({ID, batch});
        m_TexturedQuadBatches[batch].drawObject(ID, object);
    }

    void Renderer::destroyTexturedQuad(uint32_t ID) {
        const uint32_t batch = m_TexturedQuadToBatch.at(ID);
        m_TexturedQuadBatches[batch].destroyObject(ID);
        m_TexturedQuadToBatch.erase(ID);
    }

    void Renderer::updateTexturedQuad(uint32_t ID, const shared_ptr<TexturedQuad> &object) {
        const uint32_t batch = m_TexturedQuadToBatch[ID];
        m_TexturedQuadBatches[batch].updateObject(ID, object);
    }

    void Renderer::flush() {
        GP_CORE_TRACE_ALL("gp::Renderer::flush()");

        m_TriangleBatch.draw();
        m_QuadBatch.draw();
        m_EllipseBatch.draw();

        uint32_t textureSlotOffset = 0;
        for (auto &batch: m_TexturedQuadBatches) {
            _bindTextureBatch(textureSlotOffset);
            textureSlotOffset += TextureBuffer::getTextureSlots();
            batch.draw();
        }
    }

    uint32_t Renderer::_cacheTexture(const std::string &name, const Bitmap &bitmap) {
        GP_CORE_DEBUG("gp::Renderer::_cacheTexture('{0}')", name);

        auto texture = shared_ptr<TextureBuffer>(new TextureBuffer(bitmap));
        const uint32_t texIndex = m_Textures.size();

        m_TexturesCache.insert({name, {texture, texIndex}});
        m_Textures.push_back(texture);

        return texIndex;
    }

    void Renderer::_bindTextureBatch(uint32_t offset) const {
        const uint32_t textures = min(offset + TextureBuffer::getTextureSlots(),
                                      static_cast<uint32_t>(m_Textures.size()));

        for (uint32_t i = offset; i < textures; i++) {
            m_Textures[i]->bind(i % TextureBuffer::getTextureSlots());
        }
    }
}
