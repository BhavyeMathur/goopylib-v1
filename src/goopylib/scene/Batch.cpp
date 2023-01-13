#include "Batch.h"


namespace gp {
    BatchBase::BatchBase(const Ref<VertexArray> &VAO, uint32_t indicesPerObject, uint32_t verticesPerObject)
            : m_VAO(VAO),
              m_Mode(verticesPerObject == 2 ? GP_DRAW_MODE_LINES : GP_DRAW_MODE_TRIANGLES),
              m_IndicesPerObject(indicesPerObject),
              m_VerticesPerObject(verticesPerObject) {

    }

    bool BatchBase::contains(uint32_t ID) {
        return m_ToIndex.find(ID) != m_ToIndex.end();
    }

    bool BatchBase::empty() const {
        return m_TotalObjects == 0;
    }

    void BatchBase::draw() {
        if (m_TotalObjects) {
            _update();
            m_VAO->draw((int32_t) m_TotalIndices, m_Mode);
        }
    }

    void BatchBase::_update() {
        if (m_VerticesPerObject == 4) {
            _updateEBO();
        }
        _updateVBO();
        m_ReallocateBufferData = false;
        m_UpdateBufferData = false;
    }

    void BatchBase::_updateEBO() const {
        if (m_ReallocateBufferData) {
            auto *indices = new uint32_t[m_TotalIndices];

            for (uint32_t i = 0; i < m_TotalObjects; i++) {
                uint32_t indicesIndex = i * 6;
                uint32_t vertexIndex = i * 4;

                indices[indicesIndex + 0] = vertexIndex + 0;
                indices[indicesIndex + 1] = vertexIndex + 1;
                indices[indicesIndex + 2] = vertexIndex + 2;

                indices[indicesIndex + 3] = vertexIndex + 0;
                indices[indicesIndex + 4] = vertexIndex + 2;
                indices[indicesIndex + 5] = vertexIndex + 3;
            }
            m_VAO->setIndexBuffer(m_TotalIndices, indices);

            delete[] indices;
        }
    }

    void BatchBase::_updateVBO() {
        if (m_ReallocateBufferData) {
            m_VAO->getVertexBuffer()->setData(getBufferData(), m_TotalVertices);
        }
        else if (m_UpdateBufferData) {
            m_VAO->getVertexBuffer()->setData(getBufferData(), m_TotalVertices, 0);
        }
    }
}
