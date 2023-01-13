#pragma once

#include "gp.h"
#include "src/goopylib/core/VertexArray.h"


namespace gp {
    class Batch {

    public:
        int32_t m_Indices = 0;
        int32_t m_Vertices = 0;

        void *m_BufferData = nullptr;
        bool m_ReallocateBufferData = false;
        bool m_UpdateBufferData = false;

        Batch() = default;

        Batch(const Ref<VertexArray> &VAO, uint32_t verticesPerObject = 0);

        bool empty() const;

        void draw();

    private:
        Ref<VertexArray> m_VAO;
        int32_t m_Mode = GP_DRAW_MODE_TRIANGLES;

        bool m_IsQuad = false;

        void _update();

        void _updateRenderingObjectVBO();

        void _updateRenderingObjectEBO() const;
    };

    template<class T>
    class BatchHandler {

        friend class Renderer;

    public:
        Batch m_Batch;

    private:
        uint32_t m_NextID = 0;
        std::unordered_map<uint32_t, uint32_t> m_ToIndex;
        std::vector<T> m_Vertices;

        uint32_t m_VerticesPerObject = 0;
        uint32_t m_IndicesPerObject = 0;

        BatchHandler() = default;

        BatchHandler(const Ref<VertexArray> &VAO, uint32_t verticesPerObject, uint32_t indicesPerObject);

        uint32_t newObject(T *vertices);

        void updateObject(uint32_t ID, T *vertices);

        void destroyObject(uint32_t ID);

        void draw();
    };
}
