#include "Bitmap.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include "src/config.h"

#if (GP_LOG_BITMAP != true) and (GP_LOG_BITMAP <= GP_LOGGING_LEVEL)
#undef GP_LOGGING_LEVEL
#define GP_LOGGING_LEVEL GP_LOG_BITMAP
#endif

#if !GP_VALUE_CHECK_BITMAP
#undef GP_VALUE_CHECKING
#undef GP_TYPE_CHECKING
#undef GP_ERROR_CHECKING
#endif

#include "src/goopylib/debug/LogMacros.h"
#include "src/goopylib/debug/Error.h"


namespace gp {
    Bitmap::Bitmap(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data)
            : m_Width(width),
              m_Height(height),
              m_Channels(channels),
              m_Data(data) {

    }

    Bitmap::Bitmap(const char *filepath)
            : m_IsImage(true) {
        GP_CORE_INFO("gp::Bitmap::Bitmap({0})", filepath);

        m_Data = stbi_load(filepath, (int32_t *) &m_Width, (int32_t *) &m_Height, (int32_t *) &m_Channels, 0);

        #if GP_ERROR_CHECKING
        if (m_Width == 0 and m_Height == 0 and m_Channels == 0) {
            GP_FILENOTFOUND_ERROR("gp::Bitmap::Bitmap() file '{0}' not found", filepath);
        }
        #endif
    }

    Bitmap::~Bitmap() {
        GP_CORE_INFO("Bitmap::~Bitmap()");
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

    Ref<Bitmap> Bitmap::create(const char *filepath) {
        return Ref<Bitmap>(new Bitmap(filepath));
    }

    Ref<Bitmap> Bitmap::create(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data) {
        return Ref<Bitmap>(new Bitmap(width, height, channels, data));
    }
}
