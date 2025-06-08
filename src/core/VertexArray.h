#pragma once

#include "gp.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace gp {
    class GPAPI VertexArray final {
    public:
        VertexArray(const BufferLayout &layout);

        VertexArray(const VertexArray &) = delete;

        VertexArray(VertexArray &&other) noexcept;

        ~VertexArray();

        void init();

        void bind() const;

        static void unbind();

        void draw(int32_t count = 0, int32_t mode = GP_DRAW_MODE_TRIANGLES) const;

        [[nodiscard]] VertexBuffer &getVertexBuffer();

        [[nodiscard]] IndexBuffer &getIndexBuffer();

    private:
        uint32_t m_RendererID = 0;

        VertexBuffer m_VertexBuffer;
        IndexBuffer m_IndexBuffer;

        void _setVertexAttribs() const;
    };
}
