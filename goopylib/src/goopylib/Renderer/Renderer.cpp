#include "Renderer.h"
#include "Image.h"

namespace gp {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::init() {
        GP_CORE_INFO("Initializing Renderer");

        GP_CORE_TRACE("Initializing Polygon Shader");
        m_PolygonShader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/vec2.vert",
                                            GP_DIRECTORY "goopylib/Shader/solid.frag");

        GP_CORE_TRACE("Initializing Ellipse Shader");
        m_EllipseShader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/ellipse.vert",
                                            GP_DIRECTORY "goopylib/Shader/ellipse.frag");

        _createTriangleBuffer();
        _createQuadBuffer();
        _createEllipseBuffer();

        GP_CORE_TRACE("Initializing Image Shader");
        m_ImageShader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/image.vert",
                                          GP_DIRECTORY "goopylib/Shader/image.frag");

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};
        m_ImageShader->set("Texture", s_TextureSlots, samplers);
    }

    void Renderer::_createTriangleBuffer() {
        GP_CORE_TRACE("Creating Triangle Buffers");

        auto triangleVAO = Ref<VertexArray>(new VertexArray());
        auto triangleVBO = Ref<VertexBuffer>(new VertexBuffer());

        triangleVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                                {ShaderDataType::Float3, "color"}});
        triangleVAO->setVertexBuffer(triangleVBO);

        m_RenderingObjects.emplace_back(triangleVAO, nullptr, m_PolygonShader);
    }

    void Renderer::_createQuadBuffer() {
        GP_CORE_TRACE("Creating Quad Buffers");

        auto quadVAO = Ref<VertexArray>(new VertexArray());
        auto quadVBO = Ref<VertexBuffer>(new VertexBuffer());

        quadVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                            {ShaderDataType::Float3, "color"}});
        quadVAO->setVertexBuffer(quadVBO);

        m_RenderingObjects.emplace_back(quadVAO, nullptr, m_PolygonShader);
    }

    void Renderer::_createEllipseBuffer() {
        GP_CORE_TRACE("Creating Ellipse Buffers");

        auto ellipseVAO = Ref<VertexArray>(new VertexArray());
        auto ellipseVBO = Ref<VertexBuffer>(new VertexBuffer());

        ellipseVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                               {ShaderDataType::Float2, "localCoord"},
                               {ShaderDataType::Float3, "color"}});
        ellipseVAO->setVertexBuffer(ellipseVBO);

        m_RenderingObjects.emplace_back(ellipseVAO, nullptr, m_EllipseShader);
    }

    void Renderer::_newImageBuffer() {
        GP_CORE_TRACE("Creating New Image Buffer");

        auto imageVAO = Ref<VertexArray>(new VertexArray());
        auto imageVBO = Ref<VertexBuffer>(new VertexBuffer());

        imageVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                             {ShaderDataType::Float2, "texCoord"},
                             {ShaderDataType::Int, "texSlot"}});
        imageVAO->setVertexBuffer(imageVBO);

        m_RenderingObjects.emplace_back(imageVAO, nullptr, m_ImageShader);
        m_ImageVertices.emplace_back();
        m_ImageIDs.emplace_back();
    }

    uint32_t Renderer::drawTriangle(TriangleVertex v1, TriangleVertex v2, TriangleVertex v3) {
        uint32_t ID = m_NextTriangleID;
        m_NextTriangleID++;
        GP_CORE_DEBUG("Drawing Triangle {0}", ID);

        m_TriangleIDs.insert({ID, m_TriangleVertices.size()});

        m_TriangleVertices.push_back(v1);
        m_TriangleVertices.push_back(v2);
        m_TriangleVertices.push_back(v3);

        m_RenderingObjects[TRIANGLES].indices += 3;
        m_RenderingObjects[TRIANGLES].vertices += 3;
        m_RenderingObjects[TRIANGLES].bufferData = &m_TriangleVertices[0];
        m_RenderingObjects[TRIANGLES].reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyTriangle(uint32_t ID) {
        uint32_t index = m_TriangleIDs.at(ID);

        m_TriangleVertices.erase(std::next(m_TriangleVertices.begin(), index),
                                 std::next(m_TriangleVertices.begin(), index + 3));

        m_TriangleIDs.erase(ID);
        for (uint32_t i = ID + 1; i < m_TriangleIDs.size(); i++) {
            if (m_TriangleIDs.find(i) != m_TriangleIDs.end()) {
                m_TriangleIDs.at(i) -= 3;
            }
        }

        m_RenderingObjects[TRIANGLES].indices -= 3;
        m_RenderingObjects[TRIANGLES].vertices -= 3;
        m_RenderingObjects[TRIANGLES].bufferData = &m_TriangleVertices[0];
        m_RenderingObjects[TRIANGLES].reallocateBufferData = true;
    }

    void Renderer::updateTriangle(uint32_t ID, TriangleVertex v1, TriangleVertex v2, TriangleVertex v3) {
        uint32_t index = m_TriangleIDs.at(ID);

        m_TriangleVertices[index + 0] = v1;
        m_TriangleVertices[index + 1] = v2;
        m_TriangleVertices[index + 2] = v3;

        m_RenderingObjects[TRIANGLES].updateBufferData = true;
    }

    uint32_t Renderer::drawQuad(QuadVertex v1, QuadVertex v2, QuadVertex v3, QuadVertex v4) {
        uint32_t ID = m_NextQuadID;
        m_NextQuadID++;
        GP_CORE_DEBUG("Drawing Quad {0}", ID);

        m_QuadIDs.insert({ID, m_QuadVertices.size()});

        m_QuadVertices.push_back(v1);
        m_QuadVertices.push_back(v2);
        m_QuadVertices.push_back(v3);
        m_QuadVertices.push_back(v4);

        m_RenderingObjects[QUADS].indices += 6;
        m_RenderingObjects[QUADS].vertices += 4;
        m_RenderingObjects[QUADS].bufferData = &m_QuadVertices[0];
        m_RenderingObjects[QUADS].reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyQuad(uint32_t ID) {
        uint32_t index = m_QuadIDs.at(ID);

        m_QuadVertices.erase(std::next(m_QuadVertices.begin(), index),
                             std::next(m_QuadVertices.begin(), index + 4));

        m_QuadIDs.erase(ID);
        for (uint32_t i = ID + 1; i < m_QuadIDs.size(); i++) {
            if (m_QuadIDs.find(i) != m_QuadIDs.end()) {
                m_QuadIDs.at(i) -= 4;
            }
        }

        m_RenderingObjects[QUADS].indices -= 6;
        m_RenderingObjects[QUADS].vertices -= 4;
        m_RenderingObjects[QUADS].bufferData = &m_QuadVertices[0];
        m_RenderingObjects[QUADS].reallocateBufferData = true;
    }

    void Renderer::updateQuad(uint32_t ID, QuadVertex v1, QuadVertex v2, QuadVertex v3, QuadVertex v4) {
        uint32_t index = m_QuadIDs.at(ID);

        m_QuadVertices[index + 0] = v1;
        m_QuadVertices[index + 1] = v2;
        m_QuadVertices[index + 2] = v3;
        m_QuadVertices[index + 3] = v4;

        m_RenderingObjects[QUADS].updateBufferData = true;
    }

    uint32_t Renderer::drawEllipse(EllipseVertex v1, EllipseVertex v2, EllipseVertex v3, EllipseVertex v4) {
        uint32_t ID = m_NextEllipseID;
        m_NextEllipseID++;
        GP_CORE_DEBUG("Drawing Ellipse {0}", ID);

        m_EllipseIDs.insert({ID, m_EllipseVertices.size()});

        m_EllipseVertices.push_back(v1);
        m_EllipseVertices.push_back(v2);
        m_EllipseVertices.push_back(v3);
        m_EllipseVertices.push_back(v4);

        m_RenderingObjects[ELLIPSES].indices += 6;
        m_RenderingObjects[ELLIPSES].vertices += 4;
        m_RenderingObjects[ELLIPSES].bufferData = &m_EllipseVertices[0];
        m_RenderingObjects[ELLIPSES].reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyEllipse(uint32_t ID) {
        uint32_t index = m_EllipseIDs.at(ID);

        m_EllipseVertices.erase(std::next(m_EllipseVertices.begin(), index),
                                std::next(m_EllipseVertices.begin(), index + 4));

        m_EllipseIDs.erase(ID);
        for (uint32_t i = ID + 1; i < m_EllipseIDs.size(); i++) {
            if (m_EllipseIDs.find(i) != m_EllipseIDs.end()) {
                m_EllipseIDs.at(i) -= 4;
            }
        }

        m_RenderingObjects[ELLIPSES].indices -= 6;
        m_RenderingObjects[ELLIPSES].vertices -= 4;
        m_RenderingObjects[ELLIPSES].bufferData = &m_EllipseVertices[0];
        m_RenderingObjects[ELLIPSES].reallocateBufferData = true;
    }

    void Renderer::updateEllipse(uint32_t ID, EllipseVertex v1, EllipseVertex v2, EllipseVertex v3, EllipseVertex v4) {
        uint32_t index = m_EllipseIDs.at(ID);

        m_EllipseVertices[index + 0] = v1;
        m_EllipseVertices[index + 1] = v2;
        m_EllipseVertices[index + 2] = v3;
        m_EllipseVertices[index + 3] = v4;

        m_RenderingObjects[ELLIPSES].updateBufferData = true;
    }

    uint32_t Renderer::drawImage(Image *image) {
        uint32_t ID = m_NextImageID;
        m_NextImageID++;
        GP_CORE_DEBUG("Drawing Image {0}", ID);

        uint32_t texIndex, texSlot;
        if (m_TexturesCache.find(image->m_Path) == m_TexturesCache.end()) {
            texIndex = _cacheTexture(image->m_Path);
            texSlot = texIndex % 16;

            if (texSlot == 0) {
                _newImageBuffer();
            }
        }
        else {
            texIndex = m_TexturesCache.at(image->m_Path).index;
            texSlot = texIndex % 16;
        }

        image->m_V1.texSlot = texSlot;
        image->m_V2.texSlot = texSlot;
        image->m_V3.texSlot = texSlot;
        image->m_V4.texSlot = texSlot;

        unsigned int batch = texIndex / s_TextureSlots;
        unsigned int i = IMAGES + batch;

        m_ImageBatches.insert({ID, batch});
        m_ImageIDs[batch].insert({ID, m_ImageVertices[batch].size()});

        m_ImageVertices[batch].push_back(image->m_V1);
        m_ImageVertices[batch].push_back(image->m_V2);
        m_ImageVertices[batch].push_back(image->m_V3);
        m_ImageVertices[batch].push_back(image->m_V4);

        m_RenderingObjects[i].indices += 6;
        m_RenderingObjects[i].vertices += 4;
        m_RenderingObjects[i].bufferData = &m_ImageVertices[batch][0];
        m_RenderingObjects[i].reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyImage(uint32_t ID) {
        uint32_t batch = m_ImageBatches.at(ID);
        auto &imageIDs = m_ImageIDs[batch];
        uint32_t index = imageIDs.at(ID);

        m_ImageVertices[batch].erase(std::next(m_ImageVertices[batch].begin(), index),
                                             std::next(m_ImageVertices[batch].begin(), index + 4));

        imageIDs.erase(ID);
        for (uint32_t i = ID + 1; i < imageIDs.size(); i++) {
            if (imageIDs.find(i) != imageIDs.end()) {
               imageIDs.at(ID) -= 4;
            }
        }

        m_RenderingObjects[IMAGES + batch].indices -= 6;
        m_RenderingObjects[IMAGES + batch].vertices -= 4;
        m_RenderingObjects[IMAGES + batch].bufferData = &m_ImageVertices[batch][0];
        m_RenderingObjects[IMAGES + batch].reallocateBufferData = true;
    }

    void Renderer::updateImage(uint32_t ID, const Image *image) {
        uint32_t batch = m_ImageBatches.at(ID);
        uint32_t index = m_ImageIDs[batch].at(ID);

        m_ImageVertices[batch][index + 0] = image->m_V1;
        m_ImageVertices[batch][index + 1] = image->m_V2;
        m_ImageVertices[batch][index + 2] = image->m_V3;
        m_ImageVertices[batch][index + 3] = image->m_V4;

        m_RenderingObjects[IMAGES + batch].updateBufferData = true;
    }

    void Renderer::flush() {
        _updateRenderingObjectVBO(m_RenderingObjects[TRIANGLES]);

        for (int i = QUADS; i < m_RenderingObjects.size(); i++) {
            auto &object = m_RenderingObjects[i];

            _updateRenderingObjectEBO(object);
            _updateRenderingObjectVBO(object);
        }

        for (int i = 0; i < IMAGES; i++) {
            auto &object = m_RenderingObjects[i];

            if (object.indices) {
                object.shader->bind();
                object.VAO->draw(object.indices, object.mode);
            }
        }

        m_ImageShader->bind();

        for (int i = IMAGES; i < m_RenderingObjects.size(); i++) {
            auto &object = m_RenderingObjects[i];

            if (object.indices) {
                _bindTextureBatch(i - IMAGES);
                object.VAO->draw(object.indices, object.mode);
            }
        }
    }

    uint32_t Renderer::_cacheTexture(const char *path) {
        GP_CORE_DEBUG("Adding '{}' to Textures Cache", path);

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

    void Renderer::_updateRenderingObjectVBO(RenderingData &object) {
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

    void Renderer::_updateRenderingObjectEBO(RenderingData &object) {
        if (object.reallocateBufferData) {

            uint32_t *indices = new uint32_t[object.indices];

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
