#pragma once

#include "gp.h"


namespace gp {
    class GPAPI Bitmap {

        friend class Image;

    public:
        Bitmap(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data);

        Bitmap(const char *filepath);

        Bitmap(const Bitmap &) = delete;

        Bitmap(Bitmap &&other) = delete;

        ~Bitmap();

        [[nodiscard]] uint32_t getWidth() const;

        [[nodiscard]] uint32_t getHeight() const;

        [[nodiscard]] uint32_t getChannels() const;

        [[nodiscard]] uint8_t *getData() const;

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
