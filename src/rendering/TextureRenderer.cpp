#define GP_LOGGING_LEVEL 3

#include "TextureRenderer.h"

#include "objects/TexturedQuad.h"
#include "texture/TextureBuffer.h"

using std::make_shared;

namespace gp {
    TextureRenderer::TextureRenderer(const gp::Shader &shader)
            : m_Shader(shader) {
    }

    void TextureRenderer::setTextureAtlas(const shared_ptr<TextureAtlas> &textureAtlas) {
        m_TextureAtlas = textureAtlas;
    }

    void TextureRenderer::draw() {
        _processQueuedObjects();

        uint32_t textureSlotOffset = 0;
        for (auto &batch: m_TexturedQuadBatches) {
            _bindTextureBatch(textureSlotOffset);
            textureSlotOffset += TextureBuffer::getTextureSlots();
            batch.draw();
        }
    }

    void TextureRenderer::drawObject(uint32_t ID, const shared_ptr<gp::TexturedQuad> &object) {
        GP_CORE_DEBUG("gp::TextureRenderer::drawTexturedQuad({0})", ID);

        if (!m_TextureAtlas->contains(object->getTextureName())) {
            m_QueuedObjects.emplace(ID, object);
            return;
        }

        auto &texData = m_TextureAtlas->getTextureData(object->getTextureName());
        auto &texCoords = texData.texCoords;
        uint32_t texIndex = texData.index;
        uint32_t texSlot = texIndex % 16;

        if (texSlot == 0)
            _createTexturedBuffer();

        object->m_VertexAttribs[0].texCoord = texCoords.topleft();
        object->m_VertexAttribs[1].texCoord = texCoords.topright();
        object->m_VertexAttribs[2].texCoord = texCoords.bottomright();
        object->m_VertexAttribs[3].texCoord = texCoords.bottomleft();

        object->m_VertexAttribs[0].texSlot = texSlot;
        object->m_VertexAttribs[1].texSlot = texSlot;
        object->m_VertexAttribs[2].texSlot = texSlot;
        object->m_VertexAttribs[3].texSlot = texSlot;

        const uint32_t batch = texIndex / TextureBuffer::getTextureSlots();
        m_TexturedQuadToBatch.insert({ID, batch});
        m_TexturedQuadBatches[batch].drawObject(ID, object);
    }

    void TextureRenderer::destroyObject(uint32_t ID) {
        if (m_QueuedObjects.contains(ID)) {
            m_QueuedObjects.erase(ID);
            return;
        }

        const uint32_t batch = m_TexturedQuadToBatch[ID];
        m_TexturedQuadBatches[batch].destroyObject(ID);
        m_TexturedQuadToBatch.erase(ID);
    }

    void TextureRenderer::updateObject(uint32_t ID, const shared_ptr<TexturedQuad> &object) {
        if (m_QueuedObjects.contains(ID))
            return;

        const uint32_t batch = m_TexturedQuadToBatch[ID];
        m_TexturedQuadBatches[batch].updateObject(ID, object);
    }

    void TextureRenderer::_createTexturedBuffer() {
        GP_CORE_TRACE("gp::TextureRenderer::_createTexturedBuffer() creating TexturedQuad buffer");

        m_TexturedQuadBatches.emplace_back(BufferLayout{{
                                                                {ShaderDataType::Float2, "position"},
                                                                {ShaderDataType::Float, "z"},
                                                                {ShaderDataType::Float4, "color"},
                                                                {ShaderDataType::Float2, "texCoord"},
                                                                {ShaderDataType::Int, "texSlot"},
                                                        }}, 6, 4, m_Shader);
        m_TexturedQuadBatches.back().init();
    }

    void TextureRenderer::_cacheTexture(const shared_ptr<TexturedQuad> &object) {
        GP_CORE_INFO("gp::TextureRenderer::_cacheTexture('{0}')", name);

        auto name = object->getTextureName();

        if (m_TextureAtlas->contains(name))
            return;

        auto texCoords = m_TextureAtlas->add(object->getBitmap());
        m_TextureAtlas->m_TexturesCache.insert({name, {texCoords.page, texCoords.coords}});
    }

    void TextureRenderer::_bindTextureBatch(uint32_t offset) const {
        GP_CORE_DEBUG("gp::TextureRenderer::_bindTextureBatch(offset={0})", offset);

        const uint32_t textures = std::min(offset + TextureBuffer::getTextureSlots(),
                                           static_cast<uint32_t>(m_TextureAtlas->pages()));

        for (uint32_t i = offset; i < textures; i++)
            m_TextureAtlas->getTextureBuffer(i)->bind(i % TextureBuffer::getTextureSlots());
    }

    void TextureRenderer::_processQueuedObjects() {
        for (const auto &[ID, object]: m_QueuedObjects) {
            _cacheTexture(object);
            drawObject(ID, object);
        }
        m_QueuedObjects.clear();
        m_TextureAtlas->_updateTextureBufferData();
    }
}
