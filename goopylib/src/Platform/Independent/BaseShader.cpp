#include "BaseShader.h"

namespace gp {
    int BaseShader::_getLocation(const char *name) {
        if (m_Uniforms.find(name) == m_Uniforms.end()) {
            int location = _getUniform(name);

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
