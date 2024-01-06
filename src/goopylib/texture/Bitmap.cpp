#define GP_LOGGING_LEVEL 3
#include "Bitmap.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>


namespace gp {
    Bitmap::Bitmap(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data)
            : m_Width(width),
              m_Height(height),
              m_Channels(channels),
              m_Data(data) {
        GP_CORE_INFO("gp::Bitmap::Bitmap({0}x{1}x{2})", width, height, channels);
    }

    Bitmap::Bitmap(const char *filepath)
            : m_IsImage(true),
            m_Data(stbi_load(filepath, (int32_t *) &m_Width, (int32_t *) &m_Height, (int32_t *) &m_Channels, 0)) {
        GP_CORE_INFO("gp::Bitmap::Bitmap({0})", filepath);

        #if GP_ERROR_CHECKING
        if (m_Width == 0 and m_Height == 0 and m_Channels == 0) {
            GP_FILENOTFOUND_ERROR("gp::Bitmap::Bitmap() file '{0}' not found", filepath);
        }
        #endif
    }

    Bitmap::~Bitmap() {
        if (m_IsImage) {
            stbi_image_free(m_Data);
        }
    }

    uint32_t Bitmap::getWidth() const {
        return m_Width;
    }

    uint32_t Bitmap::getHeight() const {
        return m_Height;
    }

    uint32_t Bitmap::getChannels() const {
        return m_Channels;
    }

    uint8_t *Bitmap::getData() const {
        return m_Data;
    }

    void Bitmap::saveBitmap(const std::string &filepath) const {
        stbi_write_bmp(filepath.c_str(), (int32_t) m_Width, (int32_t) m_Height, 1, m_Data);
    }
}
