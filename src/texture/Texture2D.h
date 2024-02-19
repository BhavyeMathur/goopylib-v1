#pragma once

#include "gp.h"

namespace gp {
    class Bitmap;

    class GPAPI Texture2D {

        friend class Renderer;

        friend class TextureAtlas;

    public:
        Texture2D(const Texture2D &) = delete;

        Texture2D(Texture2D &&other) = delete;

        ~Texture2D();

        void bind(uint32_t slot) const;

        void setData(uint32_t xOffset,
                           uint32_t yOffset,
                           uint32_t width,
                           uint32_t height,
                           const uint8_t *data);

        void setData(uint32_t width, uint32_t height, uint32_t channels, const uint8_t *data = nullptr);

        static void unbind();

        static void init();

        [[nodiscard]] static int32_t getTextureSlots();

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        uint32_t m_RendererID = 0;

        static int32_t s_TextureSlots;

        Texture2D(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data = nullptr);

        Texture2D(const Bitmap &bitmap);

        [[nodiscard]] uint32_t _getDataFormat() const;

        [[nodiscard]] int32_t _getInternalFormat() const;
    };
}
