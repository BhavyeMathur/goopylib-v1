#define GP_LOGGING_LEVEL 3

#include "TextureRenderer.h"

#include "objects/TexturedQuad.h"
#include "texture/TextureBuffer.h"

using std::make_shared;

namespace gp {
    TextureRenderer::TextureRenderer(const gp::Shader &shader)
            : m_Shader(shader) {
    }

    void TextureRenderer::draw() {
        uint32_t textureSlotOffset = 0;

        for (auto &batch: m_TexturedQuadBatches) {
            _bindTextureBatch(textureSlotOffset);
            textureSlotOffset += TextureBuffer::getTextureSlots();
            batch.draw();
        }
    }

    void TextureRenderer::drawObject(uint32_t ID, const shared_ptr<gp::TexturedQuad> &object) {
        GP_CORE_DEBUG("gp::TextureRenderer::drawTexturedQuad({0})", ID);

        uint32_t texIndex, texSlot;

        if (m_TexturesCache.contains(object->getTextureName())) {
            GP_CORE_TRACE("gp::TextureRenderer::drawObject() - using cached texture '{0}'", object->getTextureName());
            texIndex = m_TexturesCache[object->getTextureName()].index;
            texSlot = texIndex % 16;
        } else {
            GP_CORE_TRACE("gp::TextureRenderer::drawObject() - no cached texture '{0}'", object->getTextureName());

            auto bitmap = object->getBitmap();
            texIndex = _cacheTexture(object->getTextureName(), *bitmap);
            texSlot = texIndex % 16;

            if (texSlot == 0) {
                _createTexturedBuffer();
            }
        }

        GP_CORE_TRACE("gp::TextureRenderer::drawObject() - texIndex={0}, texSlot={1}", texIndex, texSlot);

        object->m_VertexAttribs[0].texSlot = texSlot;
        object->m_VertexAttribs[1].texSlot = texSlot;
        object->m_VertexAttribs[2].texSlot = texSlot;
        object->m_VertexAttribs[3].texSlot = texSlot;

        const uint32_t batch = texIndex / TextureBuffer::getTextureSlots();
        m_TexturedQuadToBatch.insert({ID, batch});
        m_TexturedQuadBatches[batch].drawObject(ID, object);
    }

    void TextureRenderer::destroyObject(uint32_t ID) {
        const uint32_t batch = m_TexturedQuadToBatch.at(ID);
        m_TexturedQuadBatches[batch].destroyObject(ID);
        m_TexturedQuadToBatch.erase(ID);
    }

    void TextureRenderer::updateObject(uint32_t ID, const shared_ptr<TexturedQuad> &object) {
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

    uint32_t TextureRenderer::_cacheTexture(const std::string &name, const Bitmap &bitmap) {
        GP_CORE_INFO("gp::TextureRenderer::_cacheTexture('{0}')", name);

        auto texture = make_shared<TextureBuffer>(bitmap);
        const uint32_t texIndex = m_Textures.size();

        m_TexturesCache.insert({name, {texture, texIndex}});
        m_Textures.push_back(texture);

        return texIndex;
    }

    void TextureRenderer::_bindTextureBatch(uint32_t offset) const {
        GP_CORE_DEBUG("gp::TextureRenderer::_bindTextureBatch(offset={0})", offset);

        const uint32_t textures = std::min(offset + TextureBuffer::getTextureSlots(),
                                           static_cast<uint32_t>(m_Textures.size()));

        for (uint32_t i = offset; i < textures; i++) {
            m_Textures[i]->bind(i % TextureBuffer::getTextureSlots());
        }
    }
}
