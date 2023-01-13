#include "Batch.h"
#include "src/goopylib/objects/Vertex.h"


// Batch Data
namespace gp {
    BatchData::BatchData(const Ref<VertexArray> &VAO, void *bufferData, bool isQuad, int32_t mode)
            : m_VAO(VAO),
              m_BufferData(bufferData),
              m_Mode(mode),
              m_IsQuad(isQuad) {
    }

    void BatchData::update() {
        if (m_IsQuad) {
            _updateRenderingObjectEBO();
        }
        _updateRenderingObjectVBO();
    }

    void BatchData::_updateRenderingObjectVBO() {
        if (m_ReallocateBufferData) {
            m_VAO->getVertexBuffer()->setData(m_BufferData, m_Vertices);
            m_ReallocateBufferData = false;
            m_UpdateBufferData = false;
        }
        else if (m_UpdateBufferData) {
            m_VAO->getVertexBuffer()->setData(m_BufferData, m_Vertices, 0);
            m_UpdateBufferData = false;
        }
    }

    void BatchData::_updateRenderingObjectEBO() const {
        if (m_ReallocateBufferData) {
            auto *indices = new uint32_t[m_Indices];

            for (uint32_t i = 0; i < m_Vertices / 4; i++) {
                uint32_t indicesIndex = i * 6;
                uint32_t vertexIndex = i * 4;

                indices[indicesIndex + 0] = vertexIndex + 0;
                indices[indicesIndex + 1] = vertexIndex + 1;
                indices[indicesIndex + 2] = vertexIndex + 2;

                indices[indicesIndex + 3] = vertexIndex + 0;
                indices[indicesIndex + 4] = vertexIndex + 2;
                indices[indicesIndex + 5] = vertexIndex + 3;
            }
            m_VAO->setIndexBuffer(m_Indices, indices);

            delete[] indices;
        }
    }

    void BatchData::draw() {
        m_VAO->draw(m_Indices, m_Mode);
    }
}

// Batch
namespace gp {
    template<class T>
        Batch<T>::Batch(BatchData data, uint32_t verticesPerObject, uint32_t indicesPerObject)
                : m_Data(std::move(data)),
                  m_VerticesPerObject(verticesPerObject),
                  m_IndicesPerObject(indicesPerObject) {
        }

    template Batch<SolidVertex>::Batch(BatchData data, uint32_t verticesPerObject, uint32_t indicesPerObject);
    template Batch<EllipseVertex>::Batch(BatchData data, uint32_t verticesPerObject, uint32_t indicesPerObject);

    template<class T>
        uint32_t Batch<T>::newObject(T *vertices) {
            uint32_t ID = m_NextID;
            m_NextID++;

            uint32_t index = m_Vertices.size();
            m_ToIndex.insert({ID, index});

            for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                m_Vertices.push_back(vertices[i]);
            }

            m_Data.m_Indices += m_IndicesPerObject;
            m_Data.m_Vertices += m_VerticesPerObject;
            m_Data.m_ReallocateBufferData = true;
            m_Data.m_BufferData = &m_Vertices[0];

            return ID;
        }

    template uint32_t Batch<SolidVertex>::newObject(SolidVertex *vertices);
    template uint32_t Batch<EllipseVertex>::newObject(EllipseVertex *vertices);

    template<class T>
        void Batch<T>::destroyObject(uint32_t ID) {
            uint32_t index = m_ToIndex[ID];

            m_Vertices.erase(std::next(m_Vertices.begin(), index),
                             std::next(m_Vertices.begin(), index + m_VerticesPerObject));

            m_ToIndex.erase(ID);

            for (auto &i: m_ToIndex) {
                if (i.second > index) {
                    i.second -= m_VerticesPerObject;
                }
            }

            m_Data.m_Indices -= 2;
            m_Data.m_Vertices -= 2;
            m_Data.m_BufferData = m_Vertices.empty() ? nullptr : &m_Vertices[0];
            m_Data.m_ReallocateBufferData = true;
        }

    template void Batch<SolidVertex>::destroyObject(uint32_t ID);
    template void Batch<EllipseVertex>::destroyObject(uint32_t ID);

    template<class T>
        void Batch<T>::updateObject(uint32_t ID, T *vertices) {
            uint32_t index = m_ToIndex[ID];

            for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                m_Vertices[index + i] = vertices[i];
            }

            m_Data.m_UpdateBufferData = true;
        }

    template void Batch<SolidVertex>::updateObject(uint32_t ID, SolidVertex *vertices);
    template void Batch<EllipseVertex>::updateObject(uint32_t ID, EllipseVertex *vertices);

    template<class T>
        void Batch<T>::draw() {
            if (m_Data.m_Indices) {
                m_Data.update();
                m_Data.draw();
            }
        }

    template void Batch<SolidVertex>::draw();
    template void Batch<EllipseVertex>::draw();
}
