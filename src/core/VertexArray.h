#pragma once

#include "gp.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace gp {
    class Window;

    class GPAPI VertexArray final {

        friend class Renderer;

    public:
        VertexArray(const BufferLayout &layout);

        VertexArray(const VertexArray &) = delete;

        VertexArray(VertexArray &&other) noexcept;

        ~VertexArray();

        void init();

        void bind() const;

        static void unbind();

        void draw(int32_t count = 0, int32_t mode = GP_DRAW_MODE_TRIANGLES) const;

        [[nodiscard]] const VertexBuffer &getVertexBuffer() const;

        void setIndexBuffer(std::initializer_list<uint32_t> indices);

        void setIndexBuffer(uint32_t *indices, uint32_t count);

        [[nodiscard]] const shared_ptr<IndexBuffer> &getIndexBuffer() const;

    private:
        uint32_t m_RendererID = 0;

        VertexBuffer m_VertexBuffer;
        shared_ptr<IndexBuffer> m_IndexBuffer = nullptr;

        void _setVertexAttribs();
    };
}
