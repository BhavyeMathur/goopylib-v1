#pragma once

#include "gp.h"
#include <core/VertexArray.h>

namespace gp {
    class RenderingBatch {
    public:
        RenderingBatch(const BufferLayout &layout, const uint32_t indexIncrement, const uint32_t vertexIncrement,
                       const int32_t mode = GP_DRAW_MODE_TRIANGLES);

        void init();

        void draw();

        void addObject();

        void updateObjects();

        void removeObject();

        void updateRenderingObjectVBO();

        void updateRenderingObjectEBO();

        [[nodiscard]] bool empty();

    private:
        VertexArray m_VAO;
        int32_t m_Mode;

        const uint32_t m_IndexIncrement;
        int32_t m_Indices = 0;
        std::vector<uint32_t> m_IndicesData{};

        const int32_t m_VertexIncrement;
        int32_t m_Vertices = 0;
        void *m_BufferData = nullptr;

        bool m_ReallocateBufferData = false;
        bool m_UpdateBufferData = false;

        friend class Renderer;
    };
}
