#include "Renderer.h"

namespace gp {
    Renderer::Renderer() {
        m_TriangleVertices = new float[s_MaxTriangleVertices];
    }

    void Renderer::drawTriangle(Point p1, Point p2, Point p3) {
        int vertexIndex = 6 * m_Triangles;

        m_TriangleVertices[vertexIndex + 0] = p1.x;
        m_TriangleVertices[vertexIndex + 1] = p1.y;
        m_TriangleVertices[vertexIndex + 2] = p2.x;
        m_TriangleVertices[vertexIndex + 3] = p2.y;
        m_TriangleVertices[vertexIndex + 4] = p3.x;
        m_TriangleVertices[vertexIndex + 5] = p3.y;

        m_Triangles++;

        m_UpdateTriangleVAO = true;

        if (m_Triangles > s_MaxTriangles) {
            GP_CORE_ERROR("More than max triangles not supported yet");
        }
    }

    void Renderer::flush() {
        if (m_Triangles) {

            if (m_UpdateTriangleVAO) {
                m_UpdateTriangleVAO = false;

                int triangleVertices = m_Triangles * 3;

                uint32_t *triangleIndices = new uint32_t[triangleVertices];
                for (uint32_t i = 0; i < triangleVertices; i++) {
                    triangleIndices[i] = i;
                }

                m_TriangleVAO = CreateRef<VertexArray>(triangleIndices, triangleVertices);

                BufferLayout layout = {{ShaderDataType::Float2, "vertices"}};
                m_TriangleVBO = CreateRef<VertexBuffer>(layout, m_TriangleVertices, 2 * triangleVertices);

                m_TriangleVAO->addVertexBuffer(m_TriangleVBO);

                delete[] triangleIndices;
            }

            Triangle::bindShader();
            m_TriangleVAO->draw();

            GP_CORE_TRACE("Drawing {0} triangles", m_Triangles);
        }
    }
}
