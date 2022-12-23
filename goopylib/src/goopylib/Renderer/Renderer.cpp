#include "Renderer.h"
#include "Image.h"

namespace gp {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::init() {
        auto shader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/vec2Vertex.glsl",
                                        GP_DIRECTORY "goopylib/Shader/vec2Fragment.glsl");

        // Triangles
        auto triangleVAO = Ref<VertexArray>(new VertexArray());
        auto triangleVBO = Ref<VertexBuffer>(new VertexBuffer());

        triangleVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                                {ShaderDataType::Float3, "color"}});
        triangleVAO->setVertexBuffer(triangleVBO);

        m_RenderingObjects.insert({"triangle", {triangleVAO, nullptr, shader}});

        // Quads
        auto quadVAO = Ref<VertexArray>(new VertexArray());
        auto quadVBO = Ref<VertexBuffer>(new VertexBuffer());

        quadVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                            {ShaderDataType::Float3, "color"}});
        quadVAO->setVertexBuffer(quadVBO);

        m_RenderingObjects.insert({"quad", {quadVAO, nullptr, shader}});

        // Ellipses
        auto ellipseShader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/ellipseVertex.glsl",
                                               GP_DIRECTORY "goopylib/Shader/ellipseFragment.glsl");

        auto ellipseVAO = Ref<VertexArray>(new VertexArray());
        auto ellipseVBO = Ref<VertexBuffer>(new VertexBuffer());

        ellipseVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                               {ShaderDataType::Float2, "localCoord"},
                               {ShaderDataType::Float3, "color"}});
        ellipseVAO->setVertexBuffer(ellipseVBO);

        m_RenderingObjects.insert({"ellipse", {ellipseVAO, nullptr, ellipseShader}});

        // Images
        auto imageShader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/imageVertex.glsl",
                                             GP_DIRECTORY "goopylib/Shader/imageFragment.glsl");

        auto imageVAO = Ref<VertexArray>(new VertexArray());
        auto imageVBO = Ref<VertexBuffer>(new VertexBuffer());

        imageVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                             {ShaderDataType::Float2, "texCoord"},
                             {ShaderDataType::Int, "texIndex"}});
        imageVAO->setVertexBuffer(imageVBO);

        int32_t samplers[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                9, 10, 11, 12, 13, 14, 15};
        imageShader->set("Texture", 16, samplers);

        m_RenderingObjects.insert({"image", {imageVAO, nullptr, imageShader}});
    }

    uint32_t Renderer::drawTriangle(TriangleVertex v1, TriangleVertex v2, TriangleVertex v3) {
        uint32_t ID = m_NextTriangleID;
        m_NextTriangleID++;
        GP_CORE_DEBUG("Drawing Triangle {0}", ID);

        m_TriangleIDs.insert({ID, m_TriangleVertices.size()});

        m_TriangleVertices.push_back(v1);
        m_TriangleVertices.push_back(v2);
        m_TriangleVertices.push_back(v3);

        m_RenderingObjects.at("triangle").count += 3;
        m_RenderingObjects.at("triangle").bufferData = &m_TriangleVertices[0];
        m_RenderingObjects.at("triangle").reallocateBufferData = true;

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

        m_RenderingObjects.at("triangle").count -= 3;
        m_RenderingObjects.at("triangle").bufferData = &m_TriangleVertices[0];
        m_RenderingObjects.at("triangle").reallocateBufferData = true;
    }

    void Renderer::updateTriangle(uint32_t ID, TriangleVertex v1, TriangleVertex v2, TriangleVertex v3) {
        uint32_t index = m_TriangleIDs.at(ID);

        m_TriangleVertices[index + 0] = v1;
        m_TriangleVertices[index + 1] = v2;
        m_TriangleVertices[index + 2] = v3;

        m_RenderingObjects.at("triangle").updateBufferData = true;
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

        m_RenderingObjects.at("quad").count += 6;
        m_RenderingObjects.at("quad").bufferData = &m_QuadVertices[0];
        m_RenderingObjects.at("quad").reallocateBufferData = true;

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

        m_RenderingObjects.at("quad").count -= 6;
        m_RenderingObjects.at("quad").bufferData = &m_QuadVertices[0];
        m_RenderingObjects.at("quad").reallocateBufferData = true;
    }

    void Renderer::updateQuad(uint32_t ID, QuadVertex v1, QuadVertex v2, QuadVertex v3, QuadVertex v4) {
        uint32_t index = m_QuadIDs.at(ID);

        m_QuadVertices[index + 0] = v1;
        m_QuadVertices[index + 1] = v2;
        m_QuadVertices[index + 2] = v3;
        m_QuadVertices[index + 3] = v4;

        m_RenderingObjects.at("quad").updateBufferData = true;
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

        m_RenderingObjects.at("ellipse").count += 6;
        m_RenderingObjects.at("ellipse").bufferData = &m_EllipseVertices[0];
        m_RenderingObjects.at("ellipse").reallocateBufferData = true;

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

        m_RenderingObjects.at("ellipse").count -= 6;
        m_RenderingObjects.at("ellipse").bufferData = &m_EllipseVertices[0];
        m_RenderingObjects.at("ellipse").reallocateBufferData = true;
    }

    void Renderer::updateEllipse(uint32_t ID, EllipseVertex v1, EllipseVertex v2, EllipseVertex v3, EllipseVertex v4) {
        uint32_t index = m_EllipseIDs.at(ID);

        m_EllipseVertices[index + 0] = v1;
        m_EllipseVertices[index + 1] = v2;
        m_EllipseVertices[index + 2] = v3;
        m_EllipseVertices[index + 3] = v4;

        m_RenderingObjects.at("ellipse").updateBufferData = true;
    }

    uint32_t Renderer::drawImage(Image *image) {
        uint32_t ID = m_NextImageID;
        m_NextImageID++;
        GP_CORE_DEBUG("Drawing Image {0}", ID);

        m_ImageIDs.insert({ID, m_ImageVertices.size()});

        if (m_Textures.find(image->m_Path) == m_Textures.end()) {
            auto texture = Ref<Texture2D>(new Texture2D(image->m_Path));
            texture->init(m_FreeTextureSlots.back());

            m_Textures.insert({image->m_Path, texture});
            m_FreeTextureSlots.pop_back();
        }

        image->m_V1.texIndex = m_Textures.at(image->m_Path)->m_Slot;
        image->m_V2.texIndex = image->m_V1.texIndex;
        image->m_V3.texIndex = image->m_V1.texIndex;
        image->m_V4.texIndex = image->m_V1.texIndex;

        m_ImageVertices.push_back(image->m_V1);
        m_ImageVertices.push_back(image->m_V2);
        m_ImageVertices.push_back(image->m_V3);
        m_ImageVertices.push_back(image->m_V4);

        m_RenderingObjects.at("image").count += 6;
        m_RenderingObjects.at("image").bufferData = &m_ImageVertices[0];
        m_RenderingObjects.at("image").reallocateBufferData = true;

        return ID;
    }

    void Renderer::destroyImage(uint32_t ID) {
        uint32_t index = m_ImageIDs.at(ID);

        m_ImageVertices.erase(std::next(m_ImageVertices.begin(), index),
                              std::next(m_ImageVertices.begin(), index + 4));

        m_ImageIDs.erase(ID);
        for (uint32_t i = ID + 1; i < m_ImageIDs.size(); i++) {
            if (m_ImageIDs.find(i) != m_ImageIDs.end()) {
                m_ImageIDs.at(i) -= 4;
            }
        }

        m_RenderingObjects.at("image").count -= 6;
        m_RenderingObjects.at("image").bufferData = &m_ImageVertices[0];
        m_RenderingObjects.at("image").reallocateBufferData = true;
    }

    void Renderer::updateImage(uint32_t ID, const Image *image) {
        uint32_t index = m_ImageIDs.at(ID);

        m_ImageVertices[index + 0] = image->m_V1;
        m_ImageVertices[index + 1] = image->m_V2;
        m_ImageVertices[index + 2] = image->m_V3;
        m_ImageVertices[index + 3] = image->m_V4;

        m_RenderingObjects.at("image").updateBufferData = true;
    }

    void Renderer::flush() {
        if (m_RenderingObjects.at("quad").reallocateBufferData) {

            uint32_t *indices = new uint32_t[6 * m_QuadIDs.size()];

            for (uint32_t i = 0; i < m_QuadIDs.size(); i++) {
                uint32_t indicesIndex = i * 6;
                uint32_t vertexIndex = i * 4;

                indices[indicesIndex + 0] = vertexIndex + 0;
                indices[indicesIndex + 1] = vertexIndex + 1;
                indices[indicesIndex + 2] = vertexIndex + 2;

                indices[indicesIndex + 3] = vertexIndex + 0;
                indices[indicesIndex + 4] = vertexIndex + 2;
                indices[indicesIndex + 5] = vertexIndex + 3;
            }

            auto quadEBO = Ref<IndexBuffer>(new IndexBuffer(6 * m_QuadIDs.size(), indices));
            m_RenderingObjects.at("quad").VAO->setIndexBuffer(quadEBO);

            delete[] indices;
        }

        if (m_RenderingObjects.at("ellipse").reallocateBufferData) {

            uint32_t *indices = new uint32_t[6 * m_EllipseIDs.size()];

            for (uint32_t i = 0; i < m_EllipseIDs.size(); i++) {
                uint32_t indicesIndex = i * 6;
                uint32_t vertexIndex = i * 4;

                indices[indicesIndex + 0] = vertexIndex + 0;
                indices[indicesIndex + 1] = vertexIndex + 1;
                indices[indicesIndex + 2] = vertexIndex + 2;

                indices[indicesIndex + 3] = vertexIndex + 0;
                indices[indicesIndex + 4] = vertexIndex + 2;
                indices[indicesIndex + 5] = vertexIndex + 3;
            }

            auto ellipseEBO = Ref<IndexBuffer>(new IndexBuffer(6 * m_EllipseIDs.size(), indices));
            m_RenderingObjects.at("ellipse").VAO->setIndexBuffer(ellipseEBO);

            delete[] indices;
        }

        if (m_RenderingObjects.at("image").reallocateBufferData) {

            uint32_t *indices = new uint32_t[6 * m_ImageIDs.size()];

            for (uint32_t i = 0; i < m_ImageIDs.size(); i++) {
                uint32_t indicesIndex = i * 6;
                uint32_t vertexIndex = i * 4;

                indices[indicesIndex + 0] = vertexIndex + 0;
                indices[indicesIndex + 1] = vertexIndex + 1;
                indices[indicesIndex + 2] = vertexIndex + 2;

                indices[indicesIndex + 3] = vertexIndex + 0;
                indices[indicesIndex + 4] = vertexIndex + 2;
                indices[indicesIndex + 5] = vertexIndex + 3;
            }

            auto imageEBO = Ref<IndexBuffer>(new IndexBuffer(6 * m_ImageIDs.size(), indices));
            m_RenderingObjects.at("image").VAO->setIndexBuffer(imageEBO);

            delete[] indices;
        }

        for (auto &object: m_RenderingObjects) {
            if (object.second.count) {
                if (object.second.reallocateBufferData) {
                    GP_CORE_DEBUG("Reallocating '{0}' VertexBuffer", object.first);

                    object.second.VBO->setData(object.second.bufferData, object.second.count);
                    object.second.reallocateBufferData = false;
                    object.second.updateBufferData = false;
                }
                else if (object.second.updateBufferData) {
                    object.second.VBO->setData(object.second.bufferData, object.second.count, 0);
                    object.second.updateBufferData = false;
                }

                object.second.shader->bind();
                object.second.VAO->draw(object.second.count, object.second.mode);
            }
        }
    }
}
