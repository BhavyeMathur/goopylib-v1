#pragma once

#include "pch.h"


namespace gp {
    class BaseShader {
    public:
        virtual ~BaseShader() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        template<typename... T>
            void set(const char *name, T &&... args) {
                bind();
                _setUniform(_getLocation(name), std::forward<T>(args)...);
            }

    private:
        std::unordered_map<const char *, int> m_Uniforms;

        int _getLocation(const char *name);

        virtual void _setUniform(int location, float value) const = 0;

        virtual void _setUniform(int location, float v1, float v2) const = 0;

        virtual void _setUniform(int location, float v1, float v2, float v3) const = 0;

        virtual void _setUniform(int location, float v1, float v2, float v3, float v4) const = 0;

        virtual void _setUniform(int location, double value) const = 0;

        virtual void _setUniform(int location, double v1, double v2) const = 0;

        virtual void _setUniform(int location, double v1, double v2, double v3) const = 0;

        virtual void _setUniform(int location, double v1, double v2, double v3, double v4) const = 0;

        virtual void _setUniform(int location, int value) const = 0;

        virtual void _setUniform(int location, int v1, int v2) const = 0;

        virtual void _setUniform(int location, int v1, int v2, int v3) const = 0;

        virtual void _setUniform(int location, int v1, int v2, int v3, int v4) const = 0;

        virtual void _setUniform(int location, unsigned int value) const = 0;

        virtual void _setUniform(int location, unsigned int v1, unsigned int v2) const = 0;

        virtual void _setUniform(int location, unsigned int v1, unsigned int v2, unsigned int v3) const = 0;

        virtual void _setUniform(int location, unsigned int v1, unsigned int v2, unsigned int v3,
                                 unsigned int v4) const = 0;

        virtual void _setUniform(int location, const glm::mat2& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat3& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat4& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat2x3& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat3x2& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat2x4& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat4x2& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat3x4& value, bool transpose = false) const = 0;

        virtual void _setUniform(int location, const glm::mat4x3& value, bool transpose = false) const = 0;

        virtual int _getUniform(const char *name) const = 0;
    };
}
