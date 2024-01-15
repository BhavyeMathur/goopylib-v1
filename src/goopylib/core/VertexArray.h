#pragma once

#include "gp.h"
#include "Buffer.h"


namespace gp {
    class Window;

    class VertexArray final {

        friend class Renderer;

    public:
        GPAPI VertexArray(const BufferLayout &layout);

        GPAPI VertexArray(const VertexArray &) = delete;

        GPAPI VertexArray(VertexArray &&other) noexcept;

        GPAPI ~VertexArray();

        GPAPI void init();

        GPAPI void bind() const;

        GPAPI static void unbind();

        GPAPI void draw(int32_t count = 0, int32_t mode = GP_DRAW_MODE_TRIANGLES) const;

        [[nodiscard]] GPAPI const VertexBuffer &getVertexBuffer() const;

        GPAPI void setIndexBuffer(std::initializer_list<uint32_t> indices);

        GPAPI void setIndexBuffer(uint32_t count, uint32_t *indices);

        [[nodiscard]] GPAPI const shared_ptr<IndexBuffer> &getIndexBuffer() const;

    private:
        uint32_t m_RendererID = 0;

        VertexBuffer m_VertexBuffer;
        shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;

        GPAPI void _setVertexAttribs();
    };
}
