#define GP_LOGGING_LEVEL 3
#include "src/goopylib/objects/Line.h"

#if __APPLE__

#include <OpenGL/gl.h>

#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

#if GP_USING_OPENGL


namespace gp {
    void Line::init() {

        GLfloat lineWidthRange[2] = {0.0f, 0.0f};
        glGetFloatv(GL_LINE_WIDTH_RANGE, (GLfloat *) lineWidthRange);

        s_MinWidth = lineWidthRange[0];
        s_MaxWidth = lineWidthRange[1];
    }
}

#endif
