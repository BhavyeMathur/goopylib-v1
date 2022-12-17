#pragma once

#include "src/pch.h"


namespace gp {
    class BaseShader {
    public:
        BaseShader();

        virtual ~BaseShader();

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        template<typename... T>
            void set(const char *name, T &&... args) {
                bind();
                _setUniform(_getLocation(name), std::forward<T>(args)...);
            }

    private:
        std::unordered_map<const char *, int32_t> m_Uniforms;

        int32_t _getLocation(const char *name);

        virtual void _setUniform(int32_t location, float value) const = 0;

        virtual void _setUniform(int32_t location, float v1, float v2) const = 0;

        virtual void _setUniform(int32_t location, float v1, float v2, float v3) const = 0;

        virtual void _setUniform(int32_t location, float v1, float v2, float v3, float v4) const = 0;

        virtual void _setUniform(int32_t location, double value) const = 0;

        virtual void _setUniform(int32_t location, double v1, double v2) const = 0;

        virtual void _setUniform(int32_t location, double v1, double v2, double v3) const = 0;

        virtual void _setUniform(int32_t location, double v1, double v2, double v3, double v4) const = 0;

        virtual void _setUniform(int32_t location, int32_t value) const = 0;

        virtual void _setUniform(int32_t location, int32_t v1, int32_t v2) const = 0;

        virtual void _setUniform(int32_t location, int32_t v1, int32_t v2, int32_t v3) const = 0;

        virtual void _setUniform(int32_t location, int32_t v1, int32_t v2, int32_t v3, int32_t v4) const = 0;

        virtual void _setUniform(int32_t location, uint32_t value) const = 0;

        virtual void _setUniform(int32_t location, uint32_t v1, uint32_t v2) const = 0;

        virtual void _setUniform(int32_t location, uint32_t v1, uint32_t v2, uint32_t v3) const = 0;

        virtual void _setUniform(int32_t location, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat2 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat3 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat4 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat2x3 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat3x2 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat2x4 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat4x2 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat3x4 &value, bool transpose = false) const = 0;

        virtual void _setUniform(int32_t location, const glm::mat4x3 &value, bool transpose = false) const = 0;

        virtual int32_t _getUniform(const char *name) const = 0;
    };
}
