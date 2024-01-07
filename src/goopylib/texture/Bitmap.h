#pragma once

#include "gp.h"


namespace gp {
    class Bitmap {

        friend class Image;

    public:
        GPAPI Bitmap(const Bitmap &) = delete;

        GPAPI Bitmap(Bitmap &&other) = delete;

        GPAPI ~Bitmap();

        [[nodiscard]] GPAPI uint32_t getWidth() const;

        [[nodiscard]] GPAPI uint32_t getHeight() const;

        [[nodiscard]] GPAPI uint32_t getChannels() const;

        [[nodiscard]] GPAPI uint8_t *getData() const;

        GPAPI void saveBitmap(const std::string &filepath) const;

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        bool m_IsImage = false;
        uint8_t *m_Data = nullptr;

        GPAPI Bitmap() = default;

        GPAPI Bitmap(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data);

        GPAPI Bitmap(const char *filepath);
    };
}
