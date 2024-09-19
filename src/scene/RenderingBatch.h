#pragma once

#include "gp.h"
#include <core/VertexArray.h>

namespace gp {
    class Shader;

    class RenderingBatch {
    public:
        RenderingBatch(const BufferLayout &layout, const uint32_t indexIncrement, const uint32_t vertexIncrement,
                       const Shader &shader, const int32_t mode = GP_DRAW_MODE_TRIANGLES);

        void init();

        void draw();

        void addObject();

        void updateObjects();

        void removeObject();

        [[nodiscard]] bool empty() const;

    private:
        VertexArray m_VAO;
        int32_t m_Mode;
        const Shader &m_Shader;

        const uint32_t m_IndexIncrement;
        uint32_t m_Indices = 0;
        std::vector<uint32_t> m_IndicesData;

        const uint32_t m_VertexIncrement;
        uint32_t m_Vertices = 0;
        void *m_BufferData = nullptr;

        bool m_ReallocateBufferData = false;
        bool m_UpdateBufferData = false;

        void _reallocateBufferData();

        void _updateRenderingObjectVBO();

        // NOTE: this is only used for objects which have 6 indices / 4 vertexes (quads, ellipses, lines, etc.)
        void _updateRenderingObjectEBO();

        friend class Renderer;
    };
}
