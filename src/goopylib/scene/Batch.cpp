#include "Batch.h"
#include "src/goopylib/objects/Vertex.h"


// Batch Data
namespace gp {
    BatchData::BatchData(const Ref<VertexArray> &VAO, void *bufferData, int32_t mode)
            : VAO(VAO),
              bufferData(bufferData),
              mode(mode) {
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

    template<class T>
        uint32_t Batch<T>::newObject(T *vertices) {
            uint32_t ID = m_NextID;
            m_NextID++;

            uint32_t index = m_Vertices.size();
            m_ToIndex.insert({ID, index});

            for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                m_Vertices.push_back(vertices[i]);
            }

            m_Data.indices += m_IndicesPerObject;
            m_Data.vertices += m_VerticesPerObject;
            m_Data.reallocateBufferData = true;
            m_Data.bufferData = &m_Vertices[0];

            return ID;
        }

    template uint32_t Batch<SolidVertex>::newObject(SolidVertex *vertices);

    template<class T>
        void Batch<T>::deleteObject(uint32_t ID) {
            uint32_t index = m_ToIndex[ID];

            m_Vertices.erase(std::next(m_Vertices.begin(), index),
                             std::next(m_Vertices.begin(), index + m_VerticesPerObject));

            m_ToIndex.erase(ID);

            for (auto &i: m_ToIndex) {
                if (i.second > index) {
                    i.second -= m_VerticesPerObject;
                }
            }

            m_Data.indices -= 2;
            m_Data.vertices -= 2;
            m_Data.bufferData = m_Vertices.empty() ? nullptr : &m_Vertices[0];
            m_Data.reallocateBufferData = true;
        }

    template void Batch<SolidVertex>::deleteObject(uint32_t ID);

    template<class T>
        void Batch<T>::updateObject(uint32_t ID, T *vertices) {
            uint32_t index = m_ToIndex[ID];

            for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                m_Vertices[index + i] = vertices[i];
            }

            m_Data.updateBufferData = true;
        }

    template void Batch<SolidVertex>::updateObject(uint32_t ID, SolidVertex *vertices);
}
