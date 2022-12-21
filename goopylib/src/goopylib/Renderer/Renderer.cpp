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

        VBO->setLayout({{ShaderDataType::Float2, "vertices"}});
        VAO->setVertexBuffer(VBO);

        m_RenderingObjects.insert({"triangle", RenderingData(VAO, VBO, shader)});
    }

    uint32_t Renderer::drawTriangle(Point p1, Point p2, Point p3) {
        uint32_t ID = m_TriangleIDs.empty() ? 0 : m_TriangleIDs.back() + 1;
        GP_CORE_DEBUG("Drawing Triangle {0}", ID);

        m_TriangleIDs.push_back(ID);

        if (m_Triangles == s_MaxTriangles) {
            GP_CORE_ERROR("More than {0} triangles not supported yet", m_Triangles);
        }

        m_TriangleVertices.push_back(p1.x);
        m_TriangleVertices.push_back(p1.y);
        m_TriangleVertices.push_back(p2.x);
        m_TriangleVertices.push_back(p2.y);
        m_TriangleVertices.push_back(p3.x);
        m_TriangleVertices.push_back(p3.y);

        m_Triangles++;
        m_UpdateTriangleVBO = true;

        return ID;
    }

    void Renderer::destroyTriangle(uint32_t ID) {
        auto indexi = std::find(m_TriangleIDs.begin(), m_TriangleIDs.end(), ID);

        if (indexi == m_TriangleIDs.end()) {
            GP_CORE_WARN("Triangle {0} does not exist and cannot be destroyed", ID);
            return;
        }

        uint32_t index = indexi - m_TriangleIDs.begin();

        m_TriangleVertices.erase(std::next(m_TriangleVertices.begin(), index * 6),
                                 std::next(m_TriangleVertices.begin(), index * 6 + 6));
        m_TriangleIDs.erase(std::next(m_TriangleIDs.begin(), index));

        m_Triangles--;
        m_UpdateTriangleVBO = true;
    }

    void Renderer::flush() {
        if (m_UpdateTriangleVBO) {
            m_RenderingObjects.at("triangle").count = m_Triangles * 6;

            GP_CORE_TRACE("Updating triangle VertexBuffer, count={0}", m_RenderingObjects.at("triangle").count);

            m_RenderingObjects.at("triangle").VBO->setData(&m_TriangleVertices[0], m_Triangles * 6);
            m_UpdateTriangleVBO = false;
        }

        for (const auto &object: m_RenderingObjects) {
            object.second.shader->bind();
            object.second.VAO->draw(object.second.count);
        }
    }
}
