#include "goopylib/Core/Shader.h"

namespace gp {
    Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource) {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            GP_CORE_ERROR("SHADER: Vertex Shader Compilation Failed {0}\n", infoLog);
            glDeleteShader(vertexShader);
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            GP_CORE_ERROR("SHADER: Fragment Shader Compilation Failed {0}\n", infoLog);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
            GP_CORE_ERROR("SHADER: Shader Linking Failed {0}\n", infoLog);
        }
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }
}
