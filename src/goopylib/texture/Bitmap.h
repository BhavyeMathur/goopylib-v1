#pragma once

#include "gp.h"


namespace gp {
    class Bitmap {

        friend class Text;

        friend class Image;

    public:
        GPAPI ~Bitmap();

        GPAPI uint32_t getWidth() const;

        GPAPI uint32_t getHeight() const;

        GPAPI uint32_t getChannels() const;

        GPAPI uint8_t* getData() const;

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        uint8_t *m_Data = nullptr;
        bool m_IsImage = false;

        Bitmap();

        Bitmap(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data);

        Bitmap(const char* filepath);
    };
}
