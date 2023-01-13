#include "Batch.h"
#include "src/goopylib/objects/Vertex.h"


// Batch Data
namespace gp {
    Batch::Batch(const Ref<VertexArray> &VAO, uint32_t verticesPerObject)
            : m_VAO(VAO),
              m_Mode(verticesPerObject == 2 ? GP_DRAW_MODE_LINES : GP_DRAW_MODE_TRIANGLES),
              m_IsQuad(verticesPerObject == 4) {
    }

    void Batch::_update() {
        if (m_IsQuad) {
            _updateRenderingObjectEBO();
        }
        _updateRenderingObjectVBO();
    }

    void Batch::_updateRenderingObjectVBO() {
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

    void Batch::_updateRenderingObjectEBO() const {
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

    bool Batch::empty() const {
        return m_Vertices == 0;
    }

    void Batch::draw() {
        if (m_Indices) {
            _update();
            m_VAO->draw(m_Indices, m_Mode);
        }
    }
}

// Batch
namespace gp {
    template<class T>
        BatchHandler<T>::BatchHandler(const Ref<VertexArray> &VAO, uint32_t verticesPerObject, uint32_t indicesPerObject)
                : m_Batch({VAO, verticesPerObject}),
                  m_VerticesPerObject(verticesPerObject),
                  m_IndicesPerObject(indicesPerObject) {
        }

    template BatchHandler<SolidVertex>::BatchHandler(const Ref<VertexArray> &VAO, uint32_t verticesPerObject,
                                                     uint32_t indicesPerObject);

    template BatchHandler<EllipseVertex>::BatchHandler(const Ref<VertexArray> &VAO, uint32_t verticesPerObject,
                                                       uint32_t indicesPerObject);

    template<class T>
        uint32_t BatchHandler<T>::newObject(T *vertices) {
            uint32_t ID = m_NextID;
            m_NextID++;

            uint32_t index = m_Vertices.size();
            m_ToIndex.insert({ID, index});

            for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                m_Vertices.push_back(vertices[i]);
            }

            m_Batch.m_Indices += m_IndicesPerObject;
            m_Batch.m_Vertices += m_VerticesPerObject;
            m_Batch.m_ReallocateBufferData = true;
            m_Batch.m_BufferData = &m_Vertices[0];

            return ID;
        }

    template uint32_t BatchHandler<SolidVertex>::newObject(SolidVertex *vertices);

    template uint32_t BatchHandler<EllipseVertex>::newObject(EllipseVertex *vertices);

    template<class T>
        void BatchHandler<T>::destroyObject(uint32_t ID) {
            uint32_t index = m_ToIndex[ID];

            m_Vertices.erase(std::next(m_Vertices.begin(), index),
                             std::next(m_Vertices.begin(), index + m_VerticesPerObject));

            m_ToIndex.erase(ID);

            for (auto &i: m_ToIndex) {
                if (i.second > index) {
                    i.second -= m_VerticesPerObject;
                }
            }

            m_Batch.m_Indices -= m_IndicesPerObject;
            m_Batch.m_Vertices -= m_VerticesPerObject;
            m_Batch.m_BufferData = m_Vertices.empty() ? nullptr : &m_Vertices[0];
            m_Batch.m_ReallocateBufferData = true;
        }

    template void BatchHandler<SolidVertex>::destroyObject(uint32_t ID);

    template void BatchHandler<EllipseVertex>::destroyObject(uint32_t ID);

    template<class T>
        void BatchHandler<T>::updateObject(uint32_t ID, T *vertices) {
            uint32_t index = m_ToIndex[ID];

            for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                m_Vertices[index + i] = vertices[i];
            }

            m_Batch.m_UpdateBufferData = true;
        }

    template void BatchHandler<SolidVertex>::updateObject(uint32_t ID, SolidVertex *vertices);

    template void BatchHandler<EllipseVertex>::updateObject(uint32_t ID, EllipseVertex *vertices);

    template<class T>
        void BatchHandler<T>::draw() {
            m_Batch.draw();
        }

    template void BatchHandler<SolidVertex>::draw();

    template void BatchHandler<EllipseVertex>::draw();
}
