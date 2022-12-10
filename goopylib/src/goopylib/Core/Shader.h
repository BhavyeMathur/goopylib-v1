#pragma once

#include "Platform/Independent/BaseShader.h"

namespace gp {
    class Shader final : public BaseShader {
    public:
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

        ~Shader() override;

        void bind() const override;

        void unbind() const override;

    private:
        uint32_t m_RendererID = 0;
    };
}
