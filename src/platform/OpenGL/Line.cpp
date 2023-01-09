#include "src/goopylib/objects/Line.h"

#if __APPLE__

#include <OpenGL/gl.h>

#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

#if GP_USING_OPENGL

#if (GP_LOG_LINE != true) and (GP_LOG_LINE <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_LINE
#endif

#if !GP_VALUE_CHECK_LINE
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"


namespace gp {
    void Line::init() {

        GLfloat lineWidthRange[2] = {0.0f, 0.0f};
        glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);

        s_MinWidth = lineWidthRange[0];
        s_MaxWidth = lineWidthRange[1];
    }
}

#endif
