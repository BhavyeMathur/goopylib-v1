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

        m_RenderingObjects.insert({"triangle", RenderingData(VAO, VBO, shader)});
    }

    uint32_t Renderer::drawTriangle(TriangleVertex v1, TriangleVertex v2, TriangleVertex v3) {
        uint32_t ID = m_TriangleIDs.empty() ? 0 : m_TriangleIDs.back() + 1;
        GP_CORE_DEBUG("Drawing Triangle {0}", ID);

        m_TriangleIDs.push_back(ID);

        m_TriangleVertices.push_back(v1);
        m_TriangleVertices.push_back(v2);
        m_TriangleVertices.push_back(v3);

        m_Triangles++;
        m_UpdateTriangleVBO = true;

        return ID;
    }

    void Renderer::destroyTriangle(uint32_t ID) {
        auto indexi = std::find(m_TriangleIDs.begin(), m_TriangleIDs.end(), ID);

        #if GP_ERROR_CHECKING
        if (indexi == m_TriangleIDs.end()) {
            GP_CORE_WARN("Triangle {0} does not exist and cannot be destroyed", ID);
            return;
        }
        #endif

        uint32_t index = indexi - m_TriangleIDs.begin();

        m_TriangleVertices.erase(std::next(m_TriangleVertices.begin(), index * 3),
                                 std::next(m_TriangleVertices.begin(), index * 3 + 3));
        m_TriangleIDs.erase(std::next(m_TriangleIDs.begin(), index));

        m_Triangles--;
        m_UpdateTriangleVBO = true;
    }

    void Renderer::updateTriangle(uint32_t ID, TriangleVertex v1, TriangleVertex v2, TriangleVertex v3) {
        auto indexi = std::find(m_TriangleIDs.begin(), m_TriangleIDs.end(), ID);
        uint32_t index = indexi - m_TriangleIDs.begin();

        m_TriangleVertices[index * 3 + 0] = v1;
        m_TriangleVertices[index * 3 + 1] = v2;
        m_TriangleVertices[index * 3 + 2] = v3;

        m_UpdateTriangleVBO = true;
    }

    void Renderer::flush() {
        if (m_UpdateTriangleVBO) {
            m_RenderingObjects.at("triangle").count = m_Triangles * 3;

            GP_CORE_TRACE("Updating triangle VertexBuffer, count={0}", m_RenderingObjects.at("triangle").count);

            m_RenderingObjects.at("triangle").VBO->setData(&m_TriangleVertices[0],m_Triangles * 15);
            m_UpdateTriangleVBO = false;
        }

        for (const auto &object: m_RenderingObjects) {
            object.second.shader->bind();
            object.second.VAO->draw(object.second.count);
        }
    }
}
