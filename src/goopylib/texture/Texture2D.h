#pragma once

#include "gp.h"

namespace gp {
    class Bitmap;

    class Texture2D {

        friend class Renderer;

        friend class TextureAtlas;

    public:
        ~Texture2D();

        GPAPI void bind(uint32_t slot) const;

        GPAPI void setData(uint32_t xOffset,
                           uint32_t yOffset,
                           uint32_t width,
                           uint32_t height,
                           const uint8_t *data);

        GPAPI void setData(uint32_t width, uint32_t height, uint32_t channels, const uint8_t *data = nullptr);

        GPAPI uint32_t getWidth() const;

        GPAPI uint32_t getHeight() const;

        GPAPI uint32_t getChannels() const;

        GPAPI static void unbind();

        GPAPI static void init();

        GPAPI static int32_t getTextureSlots();

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        uint32_t m_RendererID = 0;

        static int32_t s_TextureSlots;

        Texture2D(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data = nullptr);

        Texture2D(const Ref<Bitmap> &bitmap);

        uint32_t _getDataFormat() const;

        int32_t _getInternalFormat() const;
    };
}
