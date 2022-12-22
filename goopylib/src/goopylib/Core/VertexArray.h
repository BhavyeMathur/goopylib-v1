#pragma once

#include "src/Platform/Independent/BaseVertexArray.h"

namespace gp {
    class Window;

    class VertexArray final : public BaseVertexArray {

        friend class Renderer;

    public:
        ~VertexArray() override;

        void bind() const override;

        void unbind() const override;

        void draw(int32_t count = 0) const override;

        void setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;

    private:
        uint32_t m_RendererID = 0;

        explicit VertexArray();
    };
}
