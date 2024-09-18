#pragma once

#include "gp.h"
#include <core/VertexArray.h>

namespace gp {
    struct RenderingBatch {
        VertexArray VAO;
        int32_t mode;

        int32_t indices = 0;
        std::vector<uint32_t> indicesData{};

        int32_t vertices = 0;
        void *bufferData = nullptr;

        bool reallocateBufferData = false;
        bool updateBufferData = false;

        RenderingBatch(const BufferLayout &layout, const int32_t mode = GP_DRAW_MODE_TRIANGLES);
    };
}
