#include "src/goopylib/texture/TextureAtlas.h"

#if GP_USING_OPENGL

#if __APPLE__

#include <OpenGL/gl.h>

#endif

#if GP_USING_GLAD

#include <glad/glad.h>

#endif

namespace gp {
    void TextureAtlas::init() {
        int32_t maxSize[2];
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, (GLint*) &maxSize);

        s_Width = maxSize[0];
        s_Height = maxSize[1];
    }
}

#endif
