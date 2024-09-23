#pragma once

#include "gp.h"
#include <core/VertexArray.h>

namespace gp {
    class Shader;

    class GPAPI RenderingBatchBase {
    public:
        RenderingBatchBase(const BufferLayout &layout, const uint32_t indexIncrement, const uint32_t vertexIncrement,
                           const Shader &shader, const int32_t mode = GP_DRAW_MODE_TRIANGLES);

        void init();

        void draw();

    protected:
        uint32_t m_Indices = 0;
        uint32_t m_Vertices = 0;

        const uint32_t m_IndexIncrement;
        const uint32_t m_VertexIncrement;

        bool m_ReallocateBufferData = false;
        bool m_UpdateBufferData = false;
        void *m_BufferData = nullptr;

        std::unordered_map<uint32_t, uint32_t> m_IDToIndex;

    private:
        VertexArray m_VAO;
        int32_t m_Mode;
        const Shader &m_Shader;

        std::vector<uint32_t> m_IndicesData;

        void _reallocateBufferData();

        void _updateRenderingObjectVBO();

        // NOTE: this is only used for objects which have 6 indices / 4 vertexes (quads, ellipses, lines, etc.)
        void _updateRenderingObjectEBO();

        friend class Renderer;
    };
}
