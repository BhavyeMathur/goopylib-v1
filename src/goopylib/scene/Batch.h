#pragma once

#include "gp.h"
#include "src/goopylib/core/VertexArray.h"


namespace gp {
    struct BatchData {
        Ref<VertexArray> VAO;

        int32_t indices = 0;
        int32_t vertices = 0;
        void *bufferData;
        bool reallocateBufferData = false;
        bool updateBufferData = false;

        int32_t mode;

        BatchData(const Ref<VertexArray> &VAO = nullptr,
                  void *bufferData = nullptr,
                  int32_t mode = GP_DRAW_MODE_TRIANGLES);
    };

    template<class T>
    class Batch {

        friend class Renderer;

    public:
        uint32_t m_NextID = 0;
        BatchData m_Data;
        std::vector<T> m_Vertices;
        std::unordered_map<uint32_t, uint32_t> m_ToIndex;

    private:
        uint32_t m_VerticesPerObject = 0;
        uint32_t m_IndicesPerObject = 0;

        Batch() = default;

        Batch(BatchData data, uint32_t verticesPerObject,uint32_t indicesPerObject);

        uint32_t newObject(T *vertices);

        void updateObject(uint32_t ID, T *vertices);

        void deleteObject(uint32_t ID);
    };
}
