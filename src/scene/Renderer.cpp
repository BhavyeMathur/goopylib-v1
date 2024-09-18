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
            : m_Window(window) {
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

        m_TexturedQuadBatches.emplace_back(BufferLayout({
                                                                {ShaderDataType::Float2, "position"},
                                                                {ShaderDataType::Float,  "z"},
                                                                {ShaderDataType::Float4, "color"},
                                                                {ShaderDataType::Float2, "texCoord"},
                                                                {ShaderDataType::Int,    "texSlot"},
                                                        }), 6, 4);
        m_TexturedQuadBatches.back().init();

        m_TexturedQuadVertices.emplace_back();
        m_TexturedQuadToIndex.emplace_back();
    }

    void Renderer::drawTriangle(uint32_t ID, const shared_ptr<Triangle> object) {
        GP_CORE_DEBUG("gp::Renderer::drawTriangle({0})", ID);

        const uint32_t index = m_TriangleVertices.size();
        m_TriangleToIndex.insert({ID, index});

        for (int i = 0; i < 3; i++) {
            m_TriangleVertices.emplace_back(object->m_Points[i], object->m_ZPosition, object->m_VertexAttribs[i]);

            if (object->isHidden()) {
                m_TriangleVertices[index + i].attrib.color.alpha = 0;
            }
        }

        m_TriangleBatch.addObject();
        m_TriangleBatch.m_BufferData = &m_TriangleVertices[0];
    }

    void Renderer::destroyTriangle(uint32_t ID) {
        const uint32_t index = m_TriangleToIndex[ID];

        // TODO optimise destroying multiple contiguous objects
        m_TriangleVertices.erase(std::next(m_TriangleVertices.begin(), index),
                                 std::next(m_TriangleVertices.begin(), index + 3));

        m_TriangleToIndex.erase(ID);
        for (auto &i: m_TriangleToIndex) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_TriangleBatch.removeObject();
        m_TriangleBatch.m_BufferData = m_TriangleVertices.empty() ? nullptr : &m_TriangleVertices[0];
    }

    void Renderer::updateTriangle(uint32_t ID, const shared_ptr<Triangle> object) {
        const uint32_t index = m_TriangleToIndex[ID];

        for (int i = 0; i < 3; i++) {
            m_TriangleVertices[index + i] = {object->m_Points[i], object->m_ZPosition, object->m_VertexAttribs[i]};

            if (object->isHidden()) {
                m_TriangleVertices[index + i].attrib.color.alpha = 0;
            }
        }
        m_TriangleBatch.updateObjects();
    }

    void Renderer::drawQuad(uint32_t ID, const shared_ptr<Quad> object) {
        GP_CORE_DEBUG("gp::Renderer::drawQuad({0})", ID);

        const uint32_t index = m_QuadVertices.size();
        m_QuadToIndex.insert({ID, index});

        for (int i = 0; i < 4; i++) {
            m_QuadVertices.emplace_back(object->m_Points[i], object->m_ZPosition, object->m_VertexAttribs[i]);

            if (object->isHidden()) {
                m_QuadVertices[index + i].attrib.color.alpha = 0;
            }
        }

        m_QuadBatch.addObject();
        m_QuadBatch.m_BufferData = &m_QuadVertices[0];
    }

    void Renderer::destroyQuad(uint32_t ID) {
        const uint32_t index = m_QuadToIndex[ID];

        m_QuadVertices.erase(std::next(m_QuadVertices.begin(), index),
                             std::next(m_QuadVertices.begin(), index + 4));

        m_QuadToIndex.erase(ID);
        for (auto &i: m_QuadToIndex) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_QuadBatch.removeObject();
        m_QuadBatch.m_BufferData = m_QuadVertices.empty() ? nullptr : &m_QuadVertices[0];
    }

    void Renderer::updateQuad(uint32_t ID, const shared_ptr<Quad> object) {
        const uint32_t index = m_QuadToIndex[ID];

        for (int i = 0; i < 4; i++) {
            m_QuadVertices[index + i] = {object->m_Points[i], object->m_ZPosition, object->m_VertexAttribs[i]};

            if (object->isHidden()) {
                m_QuadVertices[index + i].attrib.color.alpha = 0;
            }
        }
        m_QuadBatch.updateObjects();
    }

    void Renderer::drawEllipse(uint32_t ID, const shared_ptr<Ellipse> object) {
        GP_CORE_DEBUG("gp::Renderer::drawEllipse({0})", ID);

        const uint32_t index = m_EllipseVertices.size();
        m_EllipseToIndex.insert({ID, index});

        for (int i = 0; i < 4; i++) {
            m_EllipseVertices.emplace_back(object->m_Points[i], object->m_ZPosition, object->m_VertexAttribs[i]);

            if (object->isHidden()) {
                m_EllipseVertices[index + i].attrib.color.alpha = 0;
            }
        }

        m_EllipseBatch.addObject();
        m_EllipseBatch.m_BufferData = &m_EllipseVertices[0];
    }

    void Renderer::destroyEllipse(uint32_t ID) {
        const uint32_t index = m_EllipseToIndex[ID];

        m_EllipseVertices.erase(std::next(m_EllipseVertices.begin(), index),
                                std::next(m_EllipseVertices.begin(), index + 4));

        m_EllipseToIndex.erase(ID);
        for (auto &i: m_EllipseToIndex) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_EllipseBatch.removeObject();
        m_EllipseBatch.m_BufferData = m_EllipseVertices.empty() ? nullptr : &m_EllipseVertices[0];
    }

    void Renderer::updateEllipse(uint32_t ID, const shared_ptr<Ellipse> object) {
        const uint32_t index = m_EllipseToIndex[ID];

        for (int i = 0; i < 4; i++) {
            m_EllipseVertices[index + i] = {object->m_Points[i], object->m_ZPosition, object->m_VertexAttribs[i]};

            if (object->isHidden()) {
                m_EllipseVertices[index + i].attrib.color.alpha = 0;
            }
        }
        m_EllipseBatch.updateObjects();
    }

    void Renderer::drawTexturedQuad(uint32_t ID, shared_ptr<TexturedQuad> object) {
        GP_CORE_DEBUG("gp::Renderer::drawTexturedQuad({0})", ID);

        uint32_t texIndex, texSlot;

        if (m_TexturesCache.contains(object->getTextureName())) {
            GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - using cached texture '{0}'", object->getTextureName());
            texIndex = m_TexturesCache[object->getTextureName()].index;
            texSlot = texIndex % 16;
        } else {
            GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - no cached texture '{0}'", object->getTextureName());

            auto bitmap = object->getBitmap();
            texIndex = _cacheTexture(object->getTextureName(), *bitmap);
            texSlot = texIndex % 16;

            if (texSlot == 0) {
                _createTexturedBuffer();
            }
        }

        GP_CORE_TRACE("gp::Renderer::drawTexturedQuad() - texIndex={0}, texSlot={1}", texIndex, texSlot);

        const uint32_t batch = texIndex / TextureBuffer::getTextureSlots();

        const uint32_t index = m_TexturedQuadVertices[batch].size();
        m_TexturedQuadToBatch.insert({ID, batch});
        m_TexturedQuadToIndex[batch].insert({ID, index});

        for (int i = 0; i < 4; i++) {
            object->m_TextureAttribs[i].texSlot = texSlot;
            m_TexturedQuadVertices[batch].emplace_back(object->m_Points[i], object->m_ZPosition,
                                                       object->m_VertexAttribs[i], object->m_TextureAttribs[i]);

            if (object->isHidden()) {
                m_TexturedQuadVertices[batch][index + i].attrib.color.alpha = 0;
            }
        }

        m_TexturedQuadBatches[batch].addObject();
        m_TexturedQuadBatches[batch].m_BufferData = &m_TexturedQuadVertices[batch][0];
    }

    void Renderer::destroyTexturedQuad(uint32_t ID) {
        const uint32_t batch = m_TexturedQuadToBatch[ID];
        auto &imageIDs = m_TexturedQuadToIndex[batch];
        const uint32_t index = imageIDs[ID];

        m_TexturedQuadVertices[batch].erase(std::next(m_TexturedQuadVertices[batch].begin(), index),
                                            std::next(m_TexturedQuadVertices[batch].begin(), index + 4));

        imageIDs.erase(ID);
        for (auto &i: imageIDs) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_TexturedQuadBatches[batch].removeObject();
        m_TexturedQuadBatches[batch].m_BufferData = m_TexturedQuadVertices[batch].empty()
                                                  ? nullptr
                                                  : &m_TexturedQuadVertices[batch][0];
    }

    void Renderer::updateTexturedQuad(uint32_t ID, const shared_ptr<TexturedQuad> object) {
        const uint32_t batch = m_TexturedQuadToBatch[ID];
        const uint32_t index = m_TexturedQuadToIndex[batch][ID];

        for (int i = 0; i < 4; i++) {
            m_TexturedQuadVertices[batch][index + i] = {object->m_Points[i], object->m_ZPosition,
                                                        object->m_VertexAttribs[i], object->m_TextureAttribs[i]};

            if (object->isHidden()) {
                m_TexturedQuadVertices[batch][index + i].attrib.color.alpha = 0;
            }
        }

        m_TexturedQuadBatches[batch].updateObjects();
    }

    void Renderer::flush() {
        GP_CORE_TRACE_ALL("gp::Renderer::flush()");

        if (!(m_TriangleBatch.empty() and m_QuadBatch.empty())) {
            m_Window.m_SolidShader.bind();
        }

        GP_CORE_TRACE_ALL("gp::Renderer::flush() drawing triangles");
        if (!m_TriangleBatch.empty()) {
            m_TriangleBatch.updateRenderingObjectVBO();
            m_TriangleBatch.draw();
        }

        GP_CORE_TRACE_ALL("gp::Renderer::flush() drawing quads");
        if (!m_QuadBatch.empty()) {
            m_QuadBatch.updateRenderingObjectEBO();
            m_QuadBatch.updateRenderingObjectVBO();
            m_QuadBatch.draw();
        }

        GP_CORE_TRACE_ALL("gp::Renderer::flush() drawing ellipses");
        if (!m_EllipseBatch.empty()) {
            m_EllipseBatch.updateRenderingObjectEBO();
            m_EllipseBatch.updateRenderingObjectVBO();

            m_Window.m_EllipseShader.bind();
            m_EllipseBatch.draw();
        }

        uint32_t textureSlotOffset = 0;
        for (auto &batch: m_TexturedQuadBatches) {
            _bindTextureBatch(textureSlotOffset);
            textureSlotOffset += TextureBuffer::getTextureSlots();

            if (!batch.empty()) {
                m_Window.m_TextureShader.bind();

                batch.updateRenderingObjectEBO();
                batch.updateRenderingObjectVBO();
                batch.draw();
            }
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
        const uint32_t textures = min(offset + TextureBuffer::getTextureSlots(), (uint32_t) m_Textures.size());

        for (uint32_t i = offset; i < textures; i++) {
            m_Textures[i]->bind(i % TextureBuffer::getTextureSlots());
        }
    }
}
