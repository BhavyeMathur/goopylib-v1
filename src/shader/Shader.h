#pragma once

#include "gp.h"

#include "core/UniformBuffer.h"
#include <glm/fwd.hpp>
#include <unordered_map>

namespace gp {
    class GPAPI Shader final {

        friend class Renderer;

    public:
        Shader() = delete;

        Shader(const Shader &) = delete;

        Shader(Shader &&other) = delete;

        Shader(const char *vertexShaderSource, const char *fragmentShaderSource);

        ~Shader();

        void compile();

        void setUniformBlock(const UniformBuffer &uniform, const char *name, uint32_t binding) const;

        template<typename... T>
            void set(const char *name, T &&... args) {
                bind();
                _setUniform(_getLocation(name), std::forward<T>(args)...);
            }

        [[nodiscard]] static shared_ptr<Shader> load(const char *vertShaderPath, const char *fragShaderPath);

    private:
        uint32_t m_RendererID = 0;

        std::unordered_map<std::string, int32_t> m_Uniforms;

        const char *m_VertexShaderSource;
        const char *m_FragmentShaderSource;

        void bind() const;

        static void unbind();

        [[nodiscard]] int32_t _getLocation(const char *name);

        static void _setUniform(int32_t location, float value) ;

        static void _setUniform(int32_t location, float v1, float v2) ;

        static void _setUniform(int32_t location, float v1, float v2, float v3) ;

        static void _setUniform(int32_t location, float v1, float v2, float v3, float v4) ;

        static void _setUniform(int32_t location, double value) ;

        static void _setUniform(int32_t location, double v1, double v2) ;

        static void _setUniform(int32_t location, double v1, double v2, double v3) ;

        static void _setUniform(int32_t location, double v1, double v2, double v3, double v4) ;

        static void _setUniform(int32_t location, int32_t value) ;

        static void _setUniform(int32_t location, int32_t v1, int32_t v2) ;

        static void _setUniform(int32_t location, int32_t v1, int32_t v2, int32_t v3) ;

        static void _setUniform(int32_t location, int32_t v1, int32_t v2, int32_t v3, int32_t v4) ;

        static void _setUniform(int32_t location, uint32_t value) ;

        static void _setUniform(int32_t location, uint32_t v1, uint32_t v2) ;

        static void _setUniform(int32_t location, uint32_t v1, uint32_t v2, uint32_t v3) ;

        static void _setUniform(int32_t location, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) ;

        static void _setUniform(int32_t location, const glm::mat2 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat3 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat4 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat2x3 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat3x2 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat2x4 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat4x2 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat3x4 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, const glm::mat4x3 &value, bool transpose = false) ;

        static void _setUniform(int32_t location, int32_t count, float *value) ;

        static void _setUniform(int32_t location, int32_t count, double *value) ;

        static void _setUniform(int32_t location, int32_t count, uint32_t *value) ;

        static void _setUniform(int32_t location, int32_t count, int32_t *value) ;

        [[nodiscard]] int32_t _getUniform(const char *name) const;
    };
}
