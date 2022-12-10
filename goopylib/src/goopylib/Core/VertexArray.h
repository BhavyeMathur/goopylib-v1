#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Platform/Independent/BaseVertexArray.h"

namespace gp {
    class VertexArray final : public BaseVertexArray {
    public:
        VertexArray();

        VertexArray(uint32_t *indices, int count);

        VertexArray(std::initializer_list<uint32_t> indices);

        ~VertexArray() override;

        void bind() const override;

        void unbind() const override;

        void draw() const override;

        void addVertexBuffer(const BaseVertexBuffer &vertexBuffer) override;

        void setIndexBuffer(const std::shared_ptr<BaseIndexBuffer> &indexBuffer) override;

    private:
        uint32_t m_RendererID = 0;
    };
}
