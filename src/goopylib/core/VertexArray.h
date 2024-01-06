#pragma once

#include "gp.h"
#include "Buffer.h"


namespace gp {
    class Window;

    class VertexArray final {

        friend class Renderer;

    public:
        GPAPI VertexArray();

        GPAPI ~VertexArray();

        GPAPI void bind() const;

        GPAPI static void unbind();

        GPAPI void draw(int32_t count = 0, int32_t mode = GP_DRAW_MODE_TRIANGLES) const;

        GPAPI void setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer);

        [[nodiscard]] GPAPI const Ref<VertexBuffer> &getVertexBuffer() const;

        GPAPI void setIndexBuffer(std::initializer_list<uint32_t> indices);

        GPAPI void setIndexBuffer(uint32_t count, uint32_t *indices);

        [[nodiscard]] GPAPI const Ref<IndexBuffer> &getIndexBuffer() const;

    private:
        uint32_t m_RendererID = 0;

        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}
