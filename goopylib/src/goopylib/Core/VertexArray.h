#pragma once

#include "Buffer.h"

namespace gp {
    class Window;

    class VertexArray final {

        friend class Renderer;

    public:
        ~VertexArray();

        void bind() const;

        static void unbind() ;

        void draw(int32_t count = 0) const;

        void setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer);

        const Ref<VertexBuffer> &getVertexBuffer() const;

        void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer);

        const Ref<IndexBuffer> &getIndexBuffer() const;

    private:
        uint32_t m_RendererID = 0;

        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;

        explicit VertexArray();
    };
}
