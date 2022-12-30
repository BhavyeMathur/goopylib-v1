#include "goopylib/shader/Shader.h"

#if (GP_LOG_SHADER != true) and (GP_LOG_SHADER <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_SHADER
#endif

#if !GP_VALUE_CHECK_SHADER
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "goopylib/debug/LogMacros.h"
#include "goopylib/debug/Error.h"


namespace gp {
    std::string readFile(const char *filePath) {
        std::string content;
        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream.is_open()) {
            GP_CORE_ERROR("File '{0}' does not exist.", filePath);
            return "";
        }

        std::string line;
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }
}

namespace gp {
    int32_t Shader::_getLocation(const char *name) {
        if (m_Uniforms.find(name) == m_Uniforms.end()) {
            int32_t location = _getUniform(name);

            if (location == -1) {
                GP_CORE_ERROR("Uniform '{0}' not found!", name);
            }
            else {
                GP_CORE_INFO("Adding '{0}' uniform at {1} to cache", name, location);
                m_Uniforms[name] = location;
            }

            return location;
        }

        return m_Uniforms[name];
    }
}
