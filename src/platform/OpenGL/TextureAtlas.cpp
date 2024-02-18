#define GP_LOGGING_LEVEL 3
#include "src/goopylib/texture/TextureAtlas.h"

#include "opengl.h"

namespace gp {
    void TextureAtlas::init() {
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &s_Width);
        s_Height = s_Width;
    }
}
