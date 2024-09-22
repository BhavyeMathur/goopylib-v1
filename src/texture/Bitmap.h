#pragma once

#include "gp.h"


namespace gp {
    class GPAPI Bitmap {

        friend class Image;

    public:
        Bitmap(uint32_t width, uint32_t height, uint32_t channels);

        Bitmap(const char *filepath);

        ~Bitmap();

        [[nodiscard]] uint32_t getWidth() const;

        [[nodiscard]] uint32_t getHeight() const;

        [[nodiscard]] uint32_t getChannels() const;

        [[nodiscard]] uint8_t *getData() const;

        void setValue(uint32_t x, uint32_t y, uint32_t channel, uint8_t value);

        [[nodiscard]] uint8_t getValue(uint32_t x, uint32_t y, uint32_t channel) const;

        void setPixel(uint32_t x, uint32_t y, uint8_t *value);

        [[nodiscard]] uint8_t *getPixel(uint32_t x, uint32_t y) const;

        void setSubdata(Bitmap &bitmap, uint32_t x, uint32_t y);

        [[nodiscard]] uint32_t getIndex(uint32_t x, uint32_t y, uint32_t channel) const;

        void saveBitmap(const std::string &filepath) const;

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        bool m_IsImage = false;
        uint8_t *m_Data = nullptr;

        Bitmap() = default;
    };
}
