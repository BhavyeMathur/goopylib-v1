#pragma once

#include "gp.h"


namespace gp {
    enum class TextureType {
        None = 0,
        Greyscale,
        RGB,
        RGBA,
        FontSDF,
    };

    TextureType getTextureTypeFromChannels(uint32_t channels);
}
