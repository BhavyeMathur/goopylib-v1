#pragma once

#include "gp.h"
#include "Buffer.h"

#if GP_USING_OPENGL
#define GP_DRAW_MODE_TRIANGLES GL_TRIANGLES
#define GP_DRAW_MODE_LINES GL_LINES
#else
#define GP_DRAW_MODE_TRIANGLES
#define GP_DRAW_MODE_LINES
#endif

namespace gp {
    class Window;

    class VertexArray final {

        friend class Renderer;

    public:
        ~VertexArray();

        void bind() const;

        static void unbind() ;

        void draw(int32_t count = 0, int32_t mode = GP_DRAW_MODE_TRIANGLES) const;

        void setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer);

        [[nodiscard]] const Ref<VertexBuffer> &getVertexBuffer() const;

        void setIndexBuffer(std::initializer_list<uint32_t> indices);

        void setIndexBuffer(uint32_t count, uint32_t *indices);

        [[nodiscard]] const Ref<IndexBuffer> &getIndexBuffer() const;

    private:
        uint32_t m_RendererID = 0;

        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;

        VertexArray();
    };
}
