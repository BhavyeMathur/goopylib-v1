#pragma once

#include "BaseBuffer.h"

namespace gp {
    class BaseVertexArray {
    public:
        BaseVertexArray() = default;

        virtual ~BaseVertexArray() = default;

        const std::vector<std::shared_ptr<BaseVertexBuffer>> &getVertexBuffers() const;

        const std::shared_ptr<BaseIndexBuffer> &getIndexBuffer() const;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const std::shared_ptr<BaseVertexBuffer> &vertexBuffer) = 0;

        virtual void setIndexBuffer(const std::shared_ptr<BaseIndexBuffer> &indexBuffer) = 0;

    protected:
        std::vector<std::shared_ptr<BaseVertexBuffer>> m_VertexBuffers;
        std::shared_ptr<BaseIndexBuffer> m_IndexBuffer;
        uint32_t m_VertexBufferIndex = 0;
    };
}
