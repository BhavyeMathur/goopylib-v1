#pragma once

#include "BaseBuffer.h"

namespace gp {
    class BaseVertexArray {
    public:
        BaseVertexArray();

        virtual ~BaseVertexArray();

        const std::vector<const BaseVertexBuffer*> & getVertexBuffers() const;

        const std::shared_ptr<BaseIndexBuffer> &getIndexBuffer() const;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        virtual void draw() const = 0;

        virtual void addVertexBuffer(const BaseVertexBuffer &vertexBuffer) = 0;

        virtual void setIndexBuffer(const std::shared_ptr<BaseIndexBuffer> &indexBuffer) = 0;

        virtual void setIndexBuffer(std::initializer_list<uint32_t> indices) = 0;

    protected:
        std::vector<const BaseVertexBuffer*> m_VertexBuffers;
        std::shared_ptr<BaseIndexBuffer> m_IndexBuffer;
        uint32_t m_VertexBufferIndex = 0;
    };
}
