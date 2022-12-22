#pragma once

#include "src/pch.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/goopylib/Shader/Shader.h"
#include "src/Platform/Independent/BaseVertexArray.h"

namespace gp {
    class Window;

    class VertexArray final : public BaseVertexArray {

        friend class Renderer;

    public:
        VertexArray();

        ~VertexArray() override;

        void setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;

    private:
        void bind() const override;

        void unbind() const override;

        void draw(int32_t count = 0) const override;

    private:
        uint32_t m_RendererID = 0;
    };
}
