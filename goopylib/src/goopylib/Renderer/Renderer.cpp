#include "Renderer.h"

#include <filesystem>

namespace gp {
    Renderer::Renderer() = default;

    Renderer::~Renderer() = default;

    void Renderer::init() {
        m_RenderingObjects["triangle"] = {CreateRef<VertexArray>(),
                                          CreateRef<VertexBuffer>(),
                                          Shader::load(GP_DIRECTORY "goopylib/Shader/vec2.vert",
                                                       GP_DIRECTORY "goopylib/Shader/solid.frag"), 0};

        m_RenderingObjects["triangle"].VBO->setLayout({{ShaderDataType::Float2, "vertices"}});
        m_RenderingObjects["triangle"].VAO->setVertexBuffer(m_RenderingObjects["triangle"].VBO);
    }

    uint32_t Renderer::drawTriangle(Point p1, Point p2, Point p3) {
        GP_CORE_DEBUG("0");

        uint32_t ID = m_TriangleIDs.empty() ? 0 : m_TriangleIDs.back() + 1;
        m_TriangleIDs.push_back(ID);

        GP_CORE_DEBUG("Drawing Triangle {0}", ID);

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
            m_UpdateTriangleVBO = false;
            m_RenderingObjects["triangle"].VBO->setData(&m_TriangleVertices[0], m_Triangles * 6);
            m_RenderingObjects["triangle"].count = m_Triangles * 6;
        }

        for (const auto &object: m_RenderingObjects) {
            object.second.shader->bind();
            object.second.VAO->draw(object.second.count);
        }
    }
}
