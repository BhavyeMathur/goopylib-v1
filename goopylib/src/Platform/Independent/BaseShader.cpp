#include "BaseShader.h"

namespace gp {
    BaseShader::BaseShader() {
        GP_CORE_INFO("Initializing BaseShader");
    }

    BaseShader::~BaseShader() {
        GP_CORE_INFO("Deallocating BaseShader");
    }

    int32_t BaseShader::_getLocation(const char *name) {
        if (m_Uniforms.find(name) == m_Uniforms.end()) {
            int32_t location = _getUniform(name);

            if (location == -1) {
                GP_CORE_ERROR("Uniform '{0}' not found!", name);
            }
            else {
                m_Uniforms[name] = location;
            }

            return location;
        }

        return m_Uniforms[name];
    }
}
