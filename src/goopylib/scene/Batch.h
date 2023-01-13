#pragma once

#include "gp.h"
#include "src/goopylib/core/VertexArray.h"


namespace gp {
    class BatchData {

    public:
        int32_t m_Indices = 0;
        int32_t m_Vertices = 0;
        void *m_BufferData;
        bool m_ReallocateBufferData = false;
        bool m_UpdateBufferData = false;

        int32_t m_Mode = GP_DRAW_MODE_TRIANGLES;

        bool m_IsQuad = false;

        BatchData(const Ref<VertexArray> &VAO = nullptr,
                  void *bufferData = nullptr,
                  bool isQuad = false,
                  int32_t mode = GP_DRAW_MODE_TRIANGLES);

        void update();

        void draw();

    private:
        Ref<VertexArray> m_VAO;

        void _updateRenderingObjectVBO();

        void _updateRenderingObjectEBO() const;
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

        void destroyObject(uint32_t ID);

        void draw();
    };
}
