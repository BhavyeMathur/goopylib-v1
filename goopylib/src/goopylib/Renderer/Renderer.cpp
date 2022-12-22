#include "Renderer.h"

#include <filesystem>

namespace gp {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::init() {
        auto shader = CreateRef<Shader>(GP_DIRECTORY "goopylib/Shader/vec2.vert",
                                        GP_DIRECTORY "goopylib/Shader/solid.frag");
        auto VAO = CreateRef<VertexArray>();
        auto VBO = VertexBuffer::create();

        VBO->setLayout({{ShaderDataType::Float2, "vertices"},
                        {ShaderDataType::Float3, "color"}});
        VAO->setVertexBuffer(VBO);

        m_RenderingObjects.insert({"triangle", {VAO, VBO, nullptr, shader}});
    }

    void Renderer::drawVertexArray(const Ref<VertexArray>& VAO, const Ref<Shader>& shader, int32_t count) {
        m_RenderingObjects.insert({("VAO" + std::to_string(VAO->m_RendererID)).c_str(),
                                   {VAO, VAO->getVertexBuffer(), nullptr, shader, count}});
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

        m_RenderingObjects.at("triangle").VBO->setData(&m_TriangleVertices[index], 3, index);
    }

    void Renderer::flush() {
        for (auto &object: m_RenderingObjects) {
            if (object.second.reallocateBufferData) {
                GP_CORE_TRACE("Reallocating '{0}' VertexBuffer", object.first);

                object.second.VBO->setData(object.second.bufferData, object.second.count);
                object.second.reallocateBufferData = false;
            }

            object.second.shader->bind();
            object.second.VAO->draw(object.second.count);
        }
    }
}
