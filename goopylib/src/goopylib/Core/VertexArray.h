#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Platform/Independent/BaseVertexArray.h"

namespace gp {
    class VertexArray final : public BaseVertexArray {
    public:
        VertexArray();

        ~VertexArray() override;

        void bind() const override;

        void unbind() const override;

        void addVertexBuffer(const std::shared_ptr<BaseVertexBuffer> &vertexBuffer) override;

        void setIndexBuffer(const std::shared_ptr<BaseIndexBuffer> &indexBuffer) override;

    private:
        uint32_t m_RendererID = 0;
    };
}
