#pragma once

#include "gp.h"
#include "Buffer.h"


namespace gp {
    class Window;

    class VertexArray final {

        friend class Renderer;

    public:
//        GPAPI VertexArray(const VertexArray &) = delete;
//
//        GPAPI VertexArray(VertexArray &&other) = delete;

        GPAPI VertexArray();

        GPAPI ~VertexArray();

        GPAPI void init();

        GPAPI void bind() const;

        GPAPI static void unbind();

        GPAPI void draw(int32_t count = 0, int32_t mode = GP_DRAW_MODE_TRIANGLES) const;

        GPAPI void setVertexBuffer(const shared_ptr<VertexBuffer> &vertexBuffer);

        [[nodiscard]] GPAPI const shared_ptr<const VertexBuffer> getVertexBuffer() const;

        GPAPI void setIndexBuffer(std::initializer_list<uint32_t> indices);

        GPAPI void setIndexBuffer(uint32_t count, uint32_t *indices);

        [[nodiscard]] GPAPI const shared_ptr<IndexBuffer> &getIndexBuffer() const;

    private:
        uint32_t m_RendererID = 0;

        shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
        shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;
    };
}
