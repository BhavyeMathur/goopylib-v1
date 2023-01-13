#pragma once

#include "gp.h"
#include "src/goopylib/core/VertexArray.h"


namespace gp {
    class VertexArray;

    static uint32_t nextObjectID = 0;

    class BatchBase {

    public:
        virtual void destroyObject(uint32_t ID) = 0;

        bool contains(uint32_t ID);

        bool empty() const;

        void draw();

    protected:
        Ref<VertexArray> m_VAO;

        int32_t m_Mode = 0;

        uint32_t m_VerticesPerObject = 0;
        uint32_t m_IndicesPerObject = 0;
        uint32_t m_TotalIndices = 0;
        uint32_t m_TotalVertices = 0;

        uint32_t m_TotalObjects = 0;
        std::unordered_map<uint32_t, uint32_t> m_ToIndex;

        bool m_ReallocateBufferData = false;
        bool m_UpdateBufferData = false;

        BatchBase() = default;

        BatchBase(const Ref<VertexArray> &VAO, uint32_t indicesPerObject, uint32_t verticesPerObject);

    private:
        void _update();

        void _updateEBO() const;

        void _updateVBO();

        virtual void *getBufferData() = 0;
    };

    template<class T>
        class Batch : public BatchBase {

        public:
            Batch() = default;

            Batch(const Ref<VertexArray> &VAO, uint32_t indicesPerObject, uint32_t verticesPerObject)
                    : BatchBase(VAO, indicesPerObject, verticesPerObject) {
            }

            uint32_t newObject(T *vertices) {
                uint32_t ID = nextObjectID;
                nextObjectID++;

                uint32_t index = m_Vertices.size();
                m_ToIndex.insert({ID, index});

                for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                    m_Vertices.push_back(vertices[i]);
                }

                m_TotalObjects++;
                m_TotalIndices += m_IndicesPerObject;
                m_TotalVertices += m_VerticesPerObject;
                m_ReallocateBufferData = true;

                return ID;
            }

            void updateObject(uint32_t ID, T *vertices) {
                uint32_t index = m_ToIndex[ID];

                for (uint32_t i = 0; i < m_VerticesPerObject; i++) {
                    m_Vertices[i + index] = vertices[i];
                }

                m_UpdateBufferData = true;
            }

            void destroyObject(uint32_t ID) override {
                uint32_t index = m_ToIndex[ID];

                m_Vertices.erase(std::next(m_Vertices.begin(), index),
                                 std::next(m_Vertices.begin(), index + m_VerticesPerObject));

                m_ToIndex.erase(m_ToIndex.find(ID));
                for (auto &i: m_ToIndex) {
                    if (i.second > index) {
                        i.second -= m_VerticesPerObject;
                    }
                }

                m_TotalObjects--;
                m_TotalIndices -= m_IndicesPerObject;
                m_TotalVertices -= m_VerticesPerObject;
                m_ReallocateBufferData = true;
            }

        private:
            std::vector<T> m_Vertices;

            void* getBufferData() override {
                return &m_Vertices[0];
            };
        };
}
