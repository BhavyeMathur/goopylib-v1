#pragma once

#include "src/pch.h"
#include "src/goopylib/Core/Buffer.h"
#include "src/Platform/Independent/BaseVertexArray.h"

namespace gp {
    class VertexArray final : public BaseVertexArray {
    public:
        VertexArray();

        ~VertexArray() override;

        void bind() const override;

        void unbind() const override;

        void draw(int32_t count = 0) const override;

        void setVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;

        uint32_t getID() const { return m_RendererID; };

        static Ref<VertexArray> create() {
            return Ref<VertexArray>(new VertexArray());
        }

    private:
        uint32_t m_RendererID = 0;
    };
}
