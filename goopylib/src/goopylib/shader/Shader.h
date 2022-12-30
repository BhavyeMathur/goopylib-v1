#pragma once

#include "gp.h"
#include <glm/fwd.hpp>
#include <unordered_map>

namespace gp {
    class UniformBuffer;

    std::string readFile(const char *filePath);

    class Shader final {

        friend class Renderer;

    public:
        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

        ~Shader();

        void setUniformBlock(const Ref<UniformBuffer> &uniform, const char *name, uint32_t binding) const;

        template<typename... T>
            void set(const char *name, T &&... args) {
                bind();
                _setUniform(_getLocation(name), std::forward < T > (args)...);
            }

        static Ref<Shader> load(const char *vertexShaderPath, const char *fragmentShaderPath) {
            return Ref<Shader>(new Shader(readFile(vertexShaderPath).c_str(),
                                          readFile(fragmentShaderPath).c_str()));
        }

    private:
        void bind() const;

        static void unbind();

    private:
        uint32_t m_RendererID = 0;

        std::unordered_map<std::string, int32_t> m_Uniforms;

        int32_t _getLocation(const char *name);

        void _setUniform(int32_t location, float value) const;

        void _setUniform(int32_t location, float v1, float v2) const;

        void _setUniform(int32_t location, float v1, float v2, float v3) const;

        void _setUniform(int32_t location, float v1, float v2, float v3, float v4) const;

        void _setUniform(int32_t location, double value) const;

        void _setUniform(int32_t location, double v1, double v2) const;

        void _setUniform(int32_t location, double v1, double v2, double v3) const;

        void _setUniform(int32_t location, double v1, double v2, double v3, double v4) const;

        void _setUniform(int32_t location, int32_t value) const;

        void _setUniform(int32_t location, int32_t v1, int32_t v2) const;

        void _setUniform(int32_t location, int32_t v1, int32_t v2, int32_t v3) const;

        void _setUniform(int32_t location, int32_t v1, int32_t v2, int32_t v3, int32_t v4) const;

        void _setUniform(int32_t location, uint32_t value) const;

        void _setUniform(int32_t location, uint32_t v1, uint32_t v2) const;

        void _setUniform(int32_t location, uint32_t v1, uint32_t v2, uint32_t v3) const;

        void _setUniform(int32_t location, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) const;

        void _setUniform(int32_t location, const glm::mat2 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat3 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat4 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat2x3 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat3x2 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat2x4 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat4x2 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat3x4 &value, bool transpose = false) const;

        void _setUniform(int32_t location, const glm::mat4x3 &value, bool transpose = false) const;

        void _setUniform(int32_t location, int32_t count, float *value) const;

        void _setUniform(int32_t location, int32_t count, double *value) const;

        void _setUniform(int32_t location, int32_t count, uint32_t *value) const;

        void _setUniform(int32_t location, int32_t count, int32_t *value) const;

        int32_t _getUniform(const char *name) const;
    };
}
