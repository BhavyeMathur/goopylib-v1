#include "RenderingBatch.h"

namespace gp {
    RenderingBatch::RenderingBatch(const BufferLayout &layout, const uint32_t indexIncrement,
                                   const uint32_t vertexIncrement, const int32_t mode)
            : m_VAO(layout),
              m_Mode(mode),
              m_IndexIncrement(indexIncrement),
              m_VertexIncrement(vertexIncrement) {
    }

    void RenderingBatch::init() {
        m_VAO.init();
    }

    void RenderingBatch::draw() {
        m_VAO.draw(m_Indices, m_Mode);
    }

    void RenderingBatch::updateObjects() {
        m_UpdateBufferData = true;
    }

    bool RenderingBatch::empty() {
        return m_Indices == 0;
    }

    void RenderingBatch::addObject() {
        m_Indices += m_IndexIncrement;
        m_Vertices += m_VertexIncrement;
        m_ReallocateBufferData = true;
    }

    void RenderingBatch::removeObject() {
        m_Indices -= m_IndexIncrement;
        m_Vertices -= m_VertexIncrement;
        m_ReallocateBufferData = true;
    }

    void RenderingBatch::updateRenderingObjectVBO() {
        GP_CORE_TRACE_ALL("gp::RenderingBatch::updateRenderingObjectVBO()");
        if (m_ReallocateBufferData) {
            m_VAO.getVertexBuffer().setData(m_BufferData, m_Vertices);
            m_ReallocateBufferData = false;
            m_UpdateBufferData = false;

        } else if (m_UpdateBufferData) {
            m_VAO.getVertexBuffer().setData(m_BufferData, m_Vertices, 0);
            m_UpdateBufferData = false;
        }
    }

    void RenderingBatch::updateRenderingObjectEBO() {
        if (!m_ReallocateBufferData) {
            return;
        }
        GP_CORE_TRACE_ALL("gp::RenderingBatch::updateRenderingObjectEBO(indices={0}, vertices={1})",
                          object.indices, object.vertices);

        m_IndicesData.clear();
        m_IndicesData = std::vector<uint32_t>(m_Indices);

        for (int32_t i = 0; i < m_Vertices / 4; i++) {
            const int32_t indicesIndex = i * 6;
            const int32_t vertexIndex = i * 4;

            m_IndicesData[indicesIndex + 0] = vertexIndex + 0;
            m_IndicesData[indicesIndex + 1] = vertexIndex + 1;
            m_IndicesData[indicesIndex + 2] = vertexIndex + 2;

            m_IndicesData[indicesIndex + 3] = vertexIndex + 0;
            m_IndicesData[indicesIndex + 4] = vertexIndex + 2;
            m_IndicesData[indicesIndex + 5] = vertexIndex + 3;
        }
        m_VAO.getIndexBuffer().setData(&m_IndicesData[0], m_Indices);
    }
}
