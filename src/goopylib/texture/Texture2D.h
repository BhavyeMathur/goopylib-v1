#pragma once

#include "gp.h"

namespace gp {

    class Texture2D {

        friend class Renderer;

        friend class TextureAtlas;

    public:
        ~Texture2D();

        GPAPI void bind(uint32_t slot) const;

        GPAPI void setData(const uint8_t *data,
                           uint32_t xOffset,
                           uint32_t yOffset,
                           uint32_t width,
                           uint32_t height);

        GPAPI void setData(const uint8_t *data, uint32_t width, uint32_t height, uint32_t channels);

        GPAPI static void unbind();

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        uint32_t m_RendererID = 0;

        explicit Texture2D(const char *path);

        Texture2D(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data = nullptr);

        uint32_t getDataFormat() const;

        int32_t getInternalFormat() const;
    };
}
