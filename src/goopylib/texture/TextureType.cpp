#include "TextureType.h"


namespace gp {
    TextureType getTextureTypeFromChannels(uint32_t channels) {
        switch (channels) {
            case 1:
                return TextureType::Greyscale;
            case 3:
                return TextureType::RGB;
            case 4:
                return TextureType::RGBA;
            default:
                return TextureType::None;
        }
    }
}
