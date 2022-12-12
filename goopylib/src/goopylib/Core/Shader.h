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

        void _setUniform(int location, float value) const override;

        void _setUniform(int location, float v1, float v2) const override;

        void _setUniform(int location, float v1, float v2, float v3) const override;

        void _setUniform(int location, float v1, float v2, float v3, float v4) const override;

        void _setUniform(int location, double value) const override;

        void _setUniform(int location, double v1, double v2) const override;

        void _setUniform(int location, double v1, double v2, double v3) const override;

        void _setUniform(int location, double v1, double v2, double v3, double v4) const override;

        void _setUniform(int location, int value) const override;

        void _setUniform(int location, int v1, int v2) const override;

        void _setUniform(int location, int v1, int v2, int v3) const override;

        void _setUniform(int location, int v1, int v2, int v3, int v4) const override;

        void _setUniform(int location, unsigned int value) const override;

        void _setUniform(int location, unsigned int v1, unsigned int v2) const override;

        void _setUniform(int location, unsigned int v1, unsigned int v2, unsigned int v3) const override;

        void _setUniform(int location, unsigned int v1, unsigned int v2, unsigned int v3,
                         unsigned int v4) const override;

        void _setUniform(int location, const glm::mat2& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat3& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat4& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat2x3& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat3x2& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat2x4& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat4x2& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat3x4& value, bool transpose) const override;

        void _setUniform(int location, const glm::mat4x3& value, bool transpose) const override;

        int _getUniform(const char *name) const override;
    };
}
