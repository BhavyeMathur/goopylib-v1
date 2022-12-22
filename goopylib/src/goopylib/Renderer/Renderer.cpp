#include "Renderer.h"

#include <filesystem>

namespace gp {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::init() {
        auto shader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/vec2.vert",
                                        GP_DIRECTORY "goopylib/Shader/solid.frag");
        auto triangleVAO = Ref<VertexArray>(new VertexArray());
        auto triangleVBO = Ref<VertexBuffer>(new VertexBuffer());

        triangleVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                        {ShaderDataType::Float3, "color"}});
        triangleVAO->setVertexBuffer(triangleVBO);

        m_RenderingObjects.insert({"triangle", {triangleVAO, nullptr, shader}});

        auto quadVAO = Ref<VertexArray>(new VertexArray());
        auto quadVBO = Ref<VertexBuffer>(new VertexBuffer());

        quadVBO->setLayout({{ShaderDataType::Float2, "vertices"},
                        {ShaderDataType::Float3, "color"}});
        quadVAO->setVertexBuffer(quadVBO);

        m_RenderingObjects.insert({"quad", {quadVAO, nullptr, shader}});
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

        for (auto &object: m_RenderingObjects) {
            if (object.second.reallocateBufferData) {
                GP_CORE_TRACE("Reallocating '{0}' VertexBuffer", object.first);

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
