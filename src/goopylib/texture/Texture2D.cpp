#define GP_LOGGING_LEVEL 3
#include "Texture2D.h"

namespace gp {
    int32_t Texture2D::s_TextureSlots = 0;

    int32_t Texture2D::getTextureSlots() {
        return s_TextureSlots;
    }
}
