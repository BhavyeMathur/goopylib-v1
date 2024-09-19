#define GP_LOGGING_LEVEL 3

#include "RenderingBatchBase.h"
#include "shader/Shader.h"
#include "debug/Error.h"

namespace gp {
    RenderingBatchBase::RenderingBatchBase(const BufferLayout &layout, const uint32_t indexIncrement,
                                           const uint32_t vertexIncrement, const Shader &shader, const int32_t mode)
            : m_IndexIncrement(indexIncrement),
              m_VertexIncrement(vertexIncrement),
              m_VAO(layout),
              m_Mode(mode),
              m_Shader(shader) {
    }

    void RenderingBatchBase::init() {
        m_VAO.init();
    }

    void RenderingBatchBase::draw() {
        if (m_Indices == 0)
            return;

        if (m_IndexIncrement == 6)
            _updateRenderingObjectEBO();
        _updateRenderingObjectVBO();

        m_Shader.bind();
        m_VAO.draw(m_Indices, m_Mode);
    }

    void RenderingBatchBase::_updateRenderingObjectVBO() {
        GP_CORE_TRACE_ALL("gp::RenderingBatch::updateRenderingObjectVBO()");
        if (m_ReallocateBufferData) {
            _reallocateBufferData();

        } else if (m_UpdateBufferData) {
            // TODO optimise, don't update the entire vertex buffer each time
            m_VAO.getVertexBuffer().setData(m_BufferData, m_Vertices, 0);
            m_UpdateBufferData = false;
        }
    }

    void RenderingBatchBase::_updateRenderingObjectEBO() {
        if (!m_ReallocateBufferData)
            return;
        GP_CORE_TRACE_ALL("gp::RenderingBatch::updateRenderingObjectEBO(indices={0}, vertices={1})",
                          object.indices, object.vertices);

        m_IndicesData.clear();
        m_IndicesData = std::vector<uint32_t>(m_Indices);

        for (int32_t i = 0; i < m_Vertices / m_VertexIncrement; i++) {
            const uint32_t indicesIndex = i * m_IndexIncrement;
            const uint32_t vertexIndex = i * m_VertexIncrement;

            m_IndicesData[indicesIndex + 0] = vertexIndex + 0;
            m_IndicesData[indicesIndex + 1] = vertexIndex + 1;
            m_IndicesData[indicesIndex + 2] = vertexIndex + 2;

            m_IndicesData[indicesIndex + 3] = vertexIndex + 0;
            m_IndicesData[indicesIndex + 4] = vertexIndex + 2;
            m_IndicesData[indicesIndex + 5] = vertexIndex + 3;
        }
        m_VAO.getIndexBuffer().setData(m_IndicesData.data(), m_Indices);
    }

    void RenderingBatchBase::_reallocateBufferData() {
        m_VAO.getVertexBuffer().setData(m_BufferData, m_Vertices);
        m_ReallocateBufferData = false;
        m_UpdateBufferData = false;
    }
}
