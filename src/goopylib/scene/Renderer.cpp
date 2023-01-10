#include "Renderer.h"

#include "src/goopylib/texture/TextureAtlas.h"

#include "src/goopylib/objects/Line.h"
#include "src/goopylib/objects/Triangle.h"
#include "src/goopylib/objects/Quad.h"
#include "src/goopylib/objects/Ellipse.h"
#include "src/goopylib/objects/Image.h"
#include "src/goopylib/shader/Shader.h"

#include "config.h"

#if (GP_LOG_RENDERER != true) and (GP_LOG_RENDERER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_RENDERER
#endif

#if !GP_VALUE_CHECK_RENDERER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"

const char *solidVertexShader =

        #include "src/goopylib/shader/solid.vert"

const char *solidFragmentShader =

        #include "src/goopylib/shader/solid.frag"

const char *ellipseVertexShader =

        #include "src/goopylib/shader/ellipse.vert"

const char *ellipseFragmentShader =

        #include "src/goopylib/shader/ellipse.frag"

const char *textureVertexShader =

        #include "src/goopylib/shader/texture.vert"

const char *textureFragmentShader =

        #include "src/goopylib/shader/texture.frag"

namespace gp {
    Renderer::Renderer(float width, float height)
            : m_Camera(-width / 2, width / 2, -height / 2, height / 2) {

    }

    Renderer::~Renderer() = default;

    void Renderer::init() {
        GP_CORE_INFO("Rendering::init() initializing Renderer");

        GP_CORE_DEBUG("Rendering::init() initializing Line");
        Line::init();

        GP_CORE_DEBUG("Rendering::init() initializing Texture Atlas");
        TextureAtlas::init();

        GP_CORE_TRACE("Rendering::init() initializing Solid Shader");
        m_SolidShader = CreateRef<Shader>(solidVertexShader, solidFragmentShader);

        GP_CORE_TRACE("Rendering::init() initializing Ellipse Shader");
        m_EllipseShader = CreateRef<Shader>(ellipseVertexShader, ellipseFragmentShader);

        _createLineBuffer();
        _createTriangleBuffer();
        _createQuadBuffer();
        _createEllipseBuffer();

        GP_CORE_TRACE("Rendering::init() initializing texture Shader");
        m_TextureShader = CreateRef<Shader>(textureVertexShader, textureFragmentShader);

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};
        m_TextureShader->set("Texture", s_TextureSlots, samplers);


        m_ShaderUniform = Ref<UniformBuffer>(new UniformBuffer({{ShaderDataType::Mat4, "PVMatrix"}}));
        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1);

        m_SolidShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        m_EllipseShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
        m_TextureShader->setUniformBlock(m_ShaderUniform, "Projection", 0);
    }

    void Renderer::_createLineBuffer() {
        GP_CORE_TRACE("Renderer::_createLineBuffer()");

        auto lineVAO = Ref<VertexArray>(new VertexArray());
        auto lineVBO = Ref<VertexBuffer>(new VertexBuffer());

        lineVBO->setLayout({{ShaderDataType::Float2, "position"},
                            {ShaderDataType::Float4, "color"}});
        lineVAO->setVertexBuffer(lineVBO);

        m_LineBatch = {lineVAO, nullptr, GP_DRAW_MODE_LINES};
    }

    void Renderer::_createTriangleBuffer() {
        GP_CORE_TRACE("Renderer::_createTriangleBuffer()");

        auto triangleVAO = Ref<VertexArray>(new VertexArray());
        auto triangleVBO = Ref<VertexBuffer>(new VertexBuffer());

        triangleVBO->setLayout({{ShaderDataType::Float2, "position"},
                                {ShaderDataType::Float4, "color"}});
        triangleVAO->setVertexBuffer(triangleVBO);

        m_TriangleBatch = {triangleVAO, nullptr};
    }

    void Renderer::_createQuadBuffer() {
        GP_CORE_TRACE("Renderer::_createQuadBuffer()");

        auto quadVAO = Ref<VertexArray>(new VertexArray());
        auto quadVBO = Ref<VertexBuffer>(new VertexBuffer());

        quadVBO->setLayout({{ShaderDataType::Float2, "position"},
                            {ShaderDataType::Float4, "color"}});
        quadVAO->setVertexBuffer(quadVBO);

        m_QuadBatch = {quadVAO, nullptr};
    }

    void Renderer::_createEllipseBuffer() {
        GP_CORE_TRACE("Renderer::_createEllipseBuffer()");

        auto ellipseVAO = Ref<VertexArray>(new VertexArray());
        auto ellipseVBO = Ref<VertexBuffer>(new VertexBuffer());

        ellipseVBO->setLayout({{ShaderDataType::Float2, "position"},
                               {ShaderDataType::Float2, "localCoord"},
                               {ShaderDataType::Float4, "color"}});
        ellipseVAO->setVertexBuffer(ellipseVBO);

        m_EllipseBatch = {ellipseVAO, nullptr};
    }

    void Renderer::_createTexturedQuadBuffer() {
        GP_CORE_TRACE("Renderer::_createTexturedQuadBuffer()");

        auto imageVAO = Ref<VertexArray>(new VertexArray());
        auto imageVBO = Ref<VertexBuffer>(new VertexBuffer());

        imageVBO->setLayout({{ShaderDataType::Float2, "position"},
                             {ShaderDataType::Float2, "texCoord"},
                             {ShaderDataType::Int,    "texSlot"},
                             {ShaderDataType::Float4, "color"}});
        imageVAO->setVertexBuffer(imageVBO);

        m_TexturedQuadBatches.emplace_back(imageVAO, nullptr);
        m_TexturedQuadVertices.emplace_back();
        m_TexturedQuadToIndex.emplace_back();
    }

    uint32_t Renderer::drawLine(Line *object) {
        uint32_t ID = m_NextLineID;
        m_NextLineID++;
        GP_CORE_DEBUG("Drawing Line {0}", ID);

        uint32_t index = m_LineVertices.size();
        m_LineToIndex.insert({ID, index});

        m_LineVertices.push_back({object->m_Points[0], object->m_V1});
        m_LineVertices.push_back({object->m_Points[1], object->m_V2});

        if (object->isHidden()) {
            m_LineVertices[index + 0].attrib.color.alpha = 0;
            m_LineVertices[index + 1].attrib.color.alpha = 0;
        }

        m_LineBatch.indices += 2;
        m_LineBatch.vertices += 2;
        m_LineBatch.bufferData = &m_LineVertices[0];
        m_LineBatch.reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyLine(uint32_t ID) {
        uint32_t index = m_LineToIndex[ID];

        m_LineVertices.erase(std::next(m_LineVertices.begin(), index),
                             std::next(m_LineVertices.begin(), index + 2));

        m_LineToIndex.erase(ID);
        for (auto &i: m_LineToIndex) {
            if (i.second > index) {
                i.second -= 2;
            }
        }

        m_LineBatch.indices -= 2;
        m_LineBatch.vertices -= 2;
        m_LineBatch.bufferData = m_LineVertices.empty() ? nullptr : &m_LineVertices[0];
        m_LineBatch.reallocateBufferData = true;
    }

    void Renderer::updateLine(uint32_t ID, const Line *object) {
        uint32_t index = m_LineToIndex[ID];

        m_LineVertices[index + 0] = {object->m_Points[0], object->m_V1};
        m_LineVertices[index + 1] = {object->m_Points[1], object->m_V2};

        if (object->isHidden()) {
            m_LineVertices[index + 0].attrib.color.alpha = 0;
            m_LineVertices[index + 1].attrib.color.alpha = 0;
        }

        m_LineBatch.updateBufferData = true;
    }

    uint32_t Renderer::drawTriangle(Triangle *object) {
        uint32_t ID = m_NextTriangleID;
        m_NextTriangleID++;
        GP_CORE_DEBUG("Drawing Triangle {0}", ID);

        uint32_t index = m_TriangleVertices.size();
        m_TriangleToIndex.insert({ID, index});

        m_TriangleVertices.push_back({object->m_Points[0], object->m_V1});
        m_TriangleVertices.push_back({object->m_Points[1], object->m_V2});
        m_TriangleVertices.push_back({object->m_Points[2], object->m_V3});

        if (object->isHidden()) {
            m_TriangleVertices[index + 0].attrib.color.alpha = 0;
            m_TriangleVertices[index + 1].attrib.color.alpha = 0;
            m_TriangleVertices[index + 2].attrib.color.alpha = 0;
        }

        m_TriangleBatch.indices += 3;
        m_TriangleBatch.vertices += 3;
        m_TriangleBatch.bufferData = &m_TriangleVertices[0];
        m_TriangleBatch.reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyTriangle(uint32_t ID) {
        uint32_t index = m_TriangleToIndex[ID];

        m_TriangleVertices.erase(std::next(m_TriangleVertices.begin(), index),
                                 std::next(m_TriangleVertices.begin(), index + 3));

        m_TriangleToIndex.erase(ID);
        for (auto &i: m_TriangleToIndex) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_TriangleBatch.indices -= 3;
        m_TriangleBatch.vertices -= 3;
        m_TriangleBatch.bufferData = m_TriangleVertices.empty() ? nullptr : &m_TriangleVertices[0];
        m_TriangleBatch.reallocateBufferData = true;
    }

    void Renderer::updateTriangle(uint32_t ID, const Triangle *object) {
        uint32_t index = m_TriangleToIndex[ID];

        m_TriangleVertices[index + 0] = {object->m_Points[0], object->m_V1};
        m_TriangleVertices[index + 1] = {object->m_Points[1], object->m_V2};
        m_TriangleVertices[index + 2] = {object->m_Points[2], object->m_V3};

        if (object->isHidden()) {
            m_TriangleVertices[index + 0].attrib.color.alpha = 0;
            m_TriangleVertices[index + 1].attrib.color.alpha = 0;
            m_TriangleVertices[index + 2].attrib.color.alpha = 0;
        }

        m_TriangleBatch.updateBufferData = true;
    }

    uint32_t Renderer::drawQuad(Quad *object) {
        uint32_t ID = m_NextQuadID;
        m_NextQuadID++;
        GP_CORE_DEBUG("Drawing Quad {0}", ID);

        uint32_t index = m_QuadVertices.size();
        m_QuadToIndex.insert({ID, index});

        m_QuadVertices.push_back({object->m_Points[0], object->m_V1});
        m_QuadVertices.push_back({object->m_Points[1], object->m_V2});
        m_QuadVertices.push_back({object->m_Points[2], object->m_V3});
        m_QuadVertices.push_back({object->m_Points[3], object->m_V4});

        if (object->isHidden()) {
            m_QuadVertices[index + 0].attrib.color.alpha = 0;
            m_QuadVertices[index + 1].attrib.color.alpha = 0;
            m_QuadVertices[index + 2].attrib.color.alpha = 0;
            m_QuadVertices[index + 3].attrib.color.alpha = 0;
        }

        m_QuadBatch.indices += 6;
        m_QuadBatch.vertices += 4;
        m_QuadBatch.bufferData = &m_QuadVertices[0];
        m_QuadBatch.reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyQuad(uint32_t ID) {
        uint32_t index = m_QuadToIndex[ID];

        m_QuadVertices.erase(std::next(m_QuadVertices.begin(), index),
                             std::next(m_QuadVertices.begin(), index + 4));

        m_QuadToIndex.erase(ID);
        for (auto &i: m_QuadToIndex) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_QuadBatch.indices -= 6;
        m_QuadBatch.vertices -= 4;
        m_QuadBatch.bufferData = m_QuadVertices.empty() ? nullptr : &m_QuadVertices[0];
        m_QuadBatch.reallocateBufferData = true;
    }

    void Renderer::updateQuad(uint32_t ID, const Quad *object) {
        uint32_t index = m_QuadToIndex[ID];

        m_QuadVertices[index + 0] = {object->m_Points[0], object->m_V1};
        m_QuadVertices[index + 1] = {object->m_Points[1], object->m_V2};
        m_QuadVertices[index + 2] = {object->m_Points[2], object->m_V3};
        m_QuadVertices[index + 3] = {object->m_Points[3], object->m_V4};

        if (object->isHidden()) {
            m_QuadVertices[index + 0].attrib.color.alpha = 0;
            m_QuadVertices[index + 1].attrib.color.alpha = 0;
            m_QuadVertices[index + 2].attrib.color.alpha = 0;
            m_QuadVertices[index + 3].attrib.color.alpha = 0;
        }


        m_QuadBatch.updateBufferData = true;
    }

    uint32_t Renderer::drawEllipse(Ellipse *object) {
        uint32_t ID = m_NextEllipseID;
        m_NextEllipseID++;
        GP_CORE_DEBUG("Drawing Ellipse {0}", ID);

        uint32_t index = m_EllipseVertices.size();
        m_EllipseToIndex.insert({ID, index});

        m_EllipseVertices.push_back({object->m_Points[0], object->m_V1});
        m_EllipseVertices.push_back({object->m_Points[1], object->m_V2});
        m_EllipseVertices.push_back({object->m_Points[2], object->m_V3});
        m_EllipseVertices.push_back({object->m_Points[3], object->m_V4});

        if (object->isHidden()) {
            m_EllipseVertices[index + 0].attrib.color.alpha = 0;
            m_EllipseVertices[index + 1].attrib.color.alpha = 0;
            m_EllipseVertices[index + 2].attrib.color.alpha = 0;
            m_EllipseVertices[index + 3].attrib.color.alpha = 0;
        }

        m_EllipseBatch.indices += 6;
        m_EllipseBatch.vertices += 4;
        m_EllipseBatch.bufferData = &m_EllipseVertices[0];
        m_EllipseBatch.reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyEllipse(uint32_t ID) {
        uint32_t index = m_EllipseToIndex[ID];

        m_EllipseVertices.erase(std::next(m_EllipseVertices.begin(), index),
                                std::next(m_EllipseVertices.begin(), index + 4));

        m_EllipseToIndex.erase(ID);
        for (auto &i: m_EllipseToIndex) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_EllipseBatch.indices -= 6;
        m_EllipseBatch.vertices -= 4;
        m_EllipseBatch.bufferData = m_EllipseVertices.empty() ? nullptr : &m_EllipseVertices[0];
        m_EllipseBatch.reallocateBufferData = true;
    }

    void Renderer::updateEllipse(uint32_t ID, const Ellipse *object) {
        uint32_t index = m_EllipseToIndex[ID];

        m_EllipseVertices[index + 0] = {object->m_Points[0], object->m_V1};
        m_EllipseVertices[index + 1] = {object->m_Points[1], object->m_V2};
        m_EllipseVertices[index + 2] = {object->m_Points[2], object->m_V3};
        m_EllipseVertices[index + 3] = {object->m_Points[3], object->m_V4};

        if (object->isHidden()) {
            m_EllipseVertices[index + 0].attrib.color.alpha = 0;
            m_EllipseVertices[index + 1].attrib.color.alpha = 0;
            m_EllipseVertices[index + 2].attrib.color.alpha = 0;
            m_EllipseVertices[index + 3].attrib.color.alpha = 0;
        }

        m_EllipseBatch.updateBufferData = true;
    }

    uint32_t Renderer::drawImage(Image *object) {
        uint32_t ID = m_NextImageID;
        m_NextImageID++;
        GP_CORE_DEBUG("gp::Renderer::drawImage({0})", ID);

        uint32_t texIndex, texSlot;
        if (m_TexturesCache.find(object->m_Path) == m_TexturesCache.end()) {
            GP_CORE_TRACE("gp::Renderer::drawImage() - no cached texture '{0}'", object->m_Path);
            texIndex = _cacheTexture(object->m_Path);
            texSlot = texIndex % 16;

            if (texSlot == 0) {
                _createTexturedQuadBuffer();
            }
        }
        else {
            GP_CORE_TRACE("gp::Renderer::drawImage() - using cached texture '{0}'", object->m_Path);
            texIndex = m_TexturesCache[object->m_Path].index;
            texSlot = texIndex % 16;
        }

        GP_CORE_TRACE("gp::Renderer::drawImage() - texIndex={0}", texIndex);

        object->m_V1.texSlot = texSlot;
        object->m_V2.texSlot = texSlot;
        object->m_V3.texSlot = texSlot;
        object->m_V4.texSlot = texSlot;

        unsigned int batch = texIndex / s_TextureSlots;

        uint32_t index = m_TexturedQuadVertices[batch].size();
        m_TexturedQuadToBatch.insert({ID, batch});
        m_TexturedQuadToIndex[batch].insert({ID, index});

        m_TexturedQuadVertices[batch].push_back({object->m_Points[0], object->m_V1});
        m_TexturedQuadVertices[batch].push_back({object->m_Points[1], object->m_V2});
        m_TexturedQuadVertices[batch].push_back({object->m_Points[2], object->m_V3});
        m_TexturedQuadVertices[batch].push_back({object->m_Points[3], object->m_V4});

        if (object->isHidden()) {
            m_TexturedQuadVertices[batch][index + 0].attrib.color.alpha = 0;
            m_TexturedQuadVertices[batch][index + 1].attrib.color.alpha = 0;
            m_TexturedQuadVertices[batch][index + 2].attrib.color.alpha = 0;
            m_TexturedQuadVertices[batch][index + 3].attrib.color.alpha = 0;
        }

        m_TexturedQuadBatches[batch].indices += 6;
        m_TexturedQuadBatches[batch].vertices += 4;
        m_TexturedQuadBatches[batch].bufferData = &m_TexturedQuadVertices[batch][0];
        m_TexturedQuadBatches[batch].reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyImage(uint32_t ID) {
        uint32_t batch = m_TexturedQuadToBatch[ID];
        auto &imageIDs = m_TexturedQuadToIndex[batch];
        uint32_t index = imageIDs[ID];

        m_TexturedQuadVertices[batch].erase(std::next(m_TexturedQuadVertices[batch].begin(), index),
                                            std::next(m_TexturedQuadVertices[batch].begin(), index + 4));

        imageIDs.erase(ID);
        for (auto &i: imageIDs) {
            if (i.second > index) {
                i.second -= 4;
            }
        }

        m_TexturedQuadBatches[batch].indices -= 6;
        m_TexturedQuadBatches[batch].vertices -= 4;
        m_TexturedQuadBatches[batch].bufferData = m_TexturedQuadVertices[batch].empty() ? nullptr
                                                                                        : &m_TexturedQuadVertices[batch][0];
        m_TexturedQuadBatches[batch].reallocateBufferData = true;
    }

    void Renderer::updateImage(uint32_t ID, const Image *object) {
        uint32_t batch = m_TexturedQuadToBatch[ID];
        uint32_t index = m_TexturedQuadToIndex[batch][ID];

        m_TexturedQuadVertices[batch][index + 0] = {object->m_Points[0], object->m_V1};
        m_TexturedQuadVertices[batch][index + 1] = {object->m_Points[1], object->m_V2};
        m_TexturedQuadVertices[batch][index + 2] = {object->m_Points[2], object->m_V3};
        m_TexturedQuadVertices[batch][index + 3] = {object->m_Points[3], object->m_V4};

        if (object->isHidden()) {
            m_TexturedQuadVertices[batch][index + 0].attrib.color.alpha = 0;
            m_TexturedQuadVertices[batch][index + 1].attrib.color.alpha = 0;
            m_TexturedQuadVertices[batch][index + 2].attrib.color.alpha = 0;
            m_TexturedQuadVertices[batch][index + 3].attrib.color.alpha = 0;
        }

        m_TexturedQuadBatches[batch].updateBufferData = true;
    }

    void Renderer::flush() {
        GP_CORE_TRACE_ALL("gp::Renderer::flush()");

        m_ShaderUniform->setData(&m_Camera.m_ProjectionViewMatrix, 1, 0);

        if (m_LineBatch.indices or m_TriangleBatch.indices or m_QuadBatch.indices) {
            m_SolidShader->bind();
        }

        if (m_LineBatch.indices) {
            _updateRenderingObjectVBO(m_LineBatch);
            m_LineBatch.VAO->draw(m_LineBatch.indices, m_LineBatch.mode);
        }

        if (m_TriangleBatch.indices) {
            _updateRenderingObjectVBO(m_TriangleBatch);
            m_TriangleBatch.VAO->draw(m_TriangleBatch.indices, m_TriangleBatch.mode);
        }

        if (m_QuadBatch.indices) {
            _updateRenderingObjectEBO(m_QuadBatch);
            _updateRenderingObjectVBO(m_QuadBatch);
            m_QuadBatch.VAO->draw(m_QuadBatch.indices, m_QuadBatch.mode);
        }

        if (m_EllipseBatch.indices) {
            _updateRenderingObjectEBO(m_EllipseBatch);
            _updateRenderingObjectVBO(m_EllipseBatch);

            m_EllipseShader->bind();
            m_EllipseBatch.VAO->draw(m_EllipseBatch.indices, m_EllipseBatch.mode);
        }

        m_TextureShader->bind();
        uint32_t offset = 0;
        for (auto &batch: m_TexturedQuadBatches) {
            for (uint32_t slot = offset; slot < min(offset + s_TextureSlots, (uint32_t) m_Textures.size()); slot++) {
                m_Textures[slot]->bind(slot % 16);
            }
            offset += s_TextureSlots;

            if (batch.indices) {
                _updateRenderingObjectEBO(batch);
                _updateRenderingObjectVBO(batch);

                batch.VAO->draw(batch.indices, batch.mode);
            }
        }
    }

    uint32_t Renderer::_cacheTexture(const char *path) {
        GP_CORE_DEBUG("gp::Renderer::_cacheTexture('{0}')", path);

        auto texture = Ref<Texture2D>(new Texture2D(path));
        uint32_t texIndex = m_Textures.size();

        m_TexturesCache.insert({path, {texture, texIndex}});
        m_Textures.push_back(texture);

        return texIndex;
    }

    void Renderer::_bindTextureBatch(uint32_t batch) {
        uint32_t textures = min((batch + 1) * s_TextureSlots, (uint32_t) m_Textures.size());

        for (uint32_t i = batch * s_TextureSlots; i < textures; i++) {
            m_Textures[i]->bind(i % s_TextureSlots);
        }
    }

    void Renderer::_updateRenderingObjectVBO(RenderingBatch &object) {
        if (object.reallocateBufferData) {
            object.VAO->m_VertexBuffer->setData(object.bufferData, object.vertices);
            object.reallocateBufferData = false;
            object.updateBufferData = false;
        }
        else if (object.updateBufferData) {
            object.VAO->m_VertexBuffer->setData(object.bufferData, object.vertices, 0);
            object.updateBufferData = false;
        }
    }

    void Renderer::_updateRenderingObjectEBO(RenderingBatch &object) {
        if (object.reallocateBufferData) {

            auto *indices = new uint32_t[object.indices];

            for (uint32_t i = 0; i < object.vertices / 4; i++) {
                uint32_t indicesIndex = i * 6;
                uint32_t vertexIndex = i * 4;

                indices[indicesIndex + 0] = vertexIndex + 0;
                indices[indicesIndex + 1] = vertexIndex + 1;
                indices[indicesIndex + 2] = vertexIndex + 2;

                indices[indicesIndex + 3] = vertexIndex + 0;
                indices[indicesIndex + 4] = vertexIndex + 2;
                indices[indicesIndex + 5] = vertexIndex + 3;
            }
            object.VAO->setIndexBuffer(object.indices, indices);

            delete[] indices;
        }
    }
}
