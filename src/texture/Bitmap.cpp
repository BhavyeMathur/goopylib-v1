#define GP_LOGGING_LEVEL 3

#include "Bitmap.h"

#include "debug/Error.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include <opengl.h>


namespace gp {
    Bitmap::Bitmap(uint32_t width, uint32_t height, uint32_t channels)
            : m_Width(width),
              m_Height(height),
              m_Channels(channels),
              m_Data(new uint8_t[width * height * channels]) {
        GP_CORE_INFO("gp::Bitmap::Bitmap({0}x{1}x{2})", width, height, channels);
    }

    Bitmap::Bitmap(const char *filepath)
            : m_IsImage(true),
              m_Data(stbi_load(filepath, (int32_t *) &m_Width, (int32_t *) &m_Height, (int32_t *) &m_Channels, 0)),
              m_Name(filepath) {
        GP_CORE_INFO("gp::Bitmap::Bitmap({0})", filepath);

        #if GP_ERROR_CHECKING
        if (m_Width == 0 and m_Height == 0 and m_Channels == 0) {
            GP_FILENOTFOUND_ERROR("gp::Bitmap::Bitmap() file '%s' not found", filepath);
        }
                #endif

        GP_CHECK_INCLUSIVE_RANGE(m_Channels, 3, 4, "gp::Bitmap::Bitmap() no current support for non-RGBA/RGB images")
    }

    Bitmap::~Bitmap() {
        if (m_IsImage)
            stbi_image_free(m_Data);
        else
            delete[] m_Data;
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

    const std::string &Bitmap::name() const {
        return m_Name;
    }

    uint32_t Bitmap::getDataFormat() const {
        switch (m_Channels) {
            case 4:
                return GL_RGBA;
            case 3:
                return GL_RGB;
            case 1:
                return GL_RED;
            default:
                GP_VALUE_ERROR("gp::Bitmap::getDataFormat() invalid bitmap format");
        }
        return -1;
    }

    void Bitmap::setValue(uint32_t x, uint32_t y, uint32_t channel, uint8_t value) {
        m_Data[getIndex(x, y, channel)] = value;
    }

    uint8_t Bitmap::getValue(uint32_t x, uint32_t y, uint32_t channel) const {
        return m_Data[getIndex(x, y, channel)];
    }

    void Bitmap::setPixel(uint32_t x, uint32_t y, uint8_t *value) {
        auto index = getIndex(x, y, 0);

        for (uint32_t i = 0; i < m_Channels; i++)
            m_Data[index + i] = value[i];
    }

    uint8_t *Bitmap::getPixel(uint32_t x, uint32_t y) const {
        return &m_Data[getIndex(x, y, 0)];
    }

    void Bitmap::setSubdata(gp::Bitmap &bitmap, uint32_t x, uint32_t y) {
        GP_CHECK_LE(bitmap.m_Channels, m_Channels, "gp::Bitmap::setSubdata() number of channels must be equal")

        uint32_t other_index = 0;
        auto index = getIndex(x, y, 0);

        for (uint32_t r = 0; r < bitmap.getHeight(); r++) {
            for (uint32_t c = 0; c < bitmap.getWidth(); c++) {
                for (uint32_t i = 0; i < bitmap.m_Channels; i++) {
                    m_Data[index + m_Channels * (c + r * m_Width) + i] = bitmap.m_Data[other_index];
                    other_index++;
                }
            }
        }

        if (bitmap.m_Channels == 4 or m_Channels == 3)
            return;

        // For RGB images, set the alpha channel to 100%
        index = getIndex(x, y, 3);
        for (uint32_t r = 0; r < bitmap.getHeight(); r++) {
            for (uint32_t i = 0; i < bitmap.getWidth(); i++) {
                m_Data[index + 4 * (i + r * m_Width)] = 255;
            }
        }

    }

    uint32_t Bitmap::getIndex(uint32_t x, uint32_t y, uint32_t channel) const {
        GP_CHECK_INCLUSIVE_RANGE(x, 0, m_Width - 1, "gp::Bitmap::getValue() x must be between 0 and bitmap width");
        GP_CHECK_INCLUSIVE_RANGE(y, 0, m_Height - 1, "gp::Bitmap::getValue() y must be between 0 and bitmap height");
        GP_CHECK_INCLUSIVE_RANGE(channel, 0, m_Channels - 1,
                                 "gp::Bitmap::getValue() channel must be between 0 and bitmap channels");

        return (x + y * m_Width) * m_Channels + channel;
    }

    void Bitmap::saveBitmap(const std::string &filepath) const {
        stbi_write_bmp(filepath.c_str(), (int32_t) m_Width, (int32_t) m_Height, m_Channels, m_Data);
    }
}
