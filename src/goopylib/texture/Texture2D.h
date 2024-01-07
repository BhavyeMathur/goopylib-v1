#pragma once

#include "gp.h"

namespace gp {
    class Bitmap;

    class Texture2D {

        friend class Renderer;

        friend class TextureAtlas;

    public:
        GPAPI Texture2D(const Texture2D &) = delete;

        GPAPI Texture2D(Texture2D &&other) = delete;

        GPAPI ~Texture2D();

        GPAPI void bind(uint32_t slot) const;

        GPAPI void setData(uint32_t xOffset,
                           uint32_t yOffset,
                           uint32_t width,
                           uint32_t height,
                           const uint8_t *data);

        GPAPI void setData(uint32_t width, uint32_t height, uint32_t channels, const uint8_t *data = nullptr);

        GPAPI static void unbind();

        GPAPI static void init();

        [[nodiscard]] GPAPI static int32_t getTextureSlots();

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        uint32_t m_RendererID = 0;

        static int32_t s_TextureSlots;

        GPAPI Texture2D(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data = nullptr);

        GPAPI Texture2D(const Bitmap &bitmap);

        [[nodiscard]] GPAPI uint32_t _getDataFormat() const;

        [[nodiscard]] GPAPI int32_t _getInternalFormat() const;
    };
}
