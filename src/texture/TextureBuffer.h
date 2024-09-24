#pragma once

#include "gp.h"

namespace gp {
    class Bitmap;

    class GPAPI TextureBuffer {

        friend class Renderer;

        friend class TextureAtlas;

    public:
        TextureBuffer(const TextureBuffer &) = delete;

        TextureBuffer(TextureBuffer &&other) = delete;

        /**
         * Initializes the texture buffer
         *
         * @param width width (in pixels) of the texture
         * @param height height (in pixels) of the texture
         * @param channels number of color channels
         * @param data optional pointer to the texture byte data
         *
         * @throws std::runtime_error: if there is no active goopylib window
         */
        TextureBuffer(uint32_t width, uint32_t height, uint32_t channels, uint8_t *data = nullptr);

        /**
         * Initializes the texture buffer from bitmap data.
         *
         * @throws std::runtime_error: if there is no active goopylib window
         */
        TextureBuffer(const Bitmap &bitmap);

        ~TextureBuffer();

        /**
         * Binds the TextureBuffer to the texture slot specified
         *
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void bind(uint32_t slot) const;

        /**
         * Sets a subset of the data in the buffer, without resizing
         *
         * @param xOffset the x-coordinate (in pixels) of the top-left corner to begin setting data
         * @param yOffset the y-coordinate (in pixels) of the top-left corner to begin setting data
         * @param width the width (in pixels) of the texture data
         * @param height the height (in pixels) of the texture data
         * @param data pointer to texture byte data
         * @param format OpenGL data format corresponding to the format of the byte data
         *
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height,
                     const uint8_t *data, uint32_t format);

        /**
         * Sets a subset of the data in the buffer from a bitmap, without resizing
         *
         * @param xOffset the x-coordinate (in pixels) of the top-left corner to begin setting data
         * @param yOffset the y-coordinate (in pixels) of the top-left corner to begin setting data
         * @param bitmap the bitmap to copy the data from
         *
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(uint32_t xOffset, uint32_t yOffset, const shared_ptr<Bitmap> &bitmap);

        /**
         * Sets the data in the buffer and resizes it
         *
         * @param width the width (in pixels) of the texture data
         * @param height the height (in pixels) of the texture data
         * @param channels the number of color channels in the texture
         * @param data pointer to texture byte data
         *
         * @throws std::runtime_error: if there is no active goopylib window
         * @throws std::runtime_error: if the buffer is uninitialized
         */
        void setData(uint32_t width, uint32_t height, uint32_t channels, const uint8_t *data = nullptr);

        /**
         * Unbinds all TextureBuffers
         *
         * @throws std::runtime_error: if there is no active goopylib window
         */
        static void unbind();

        /**
         * Initialises the TextureBuffer class. In particular, this retrieves the number of available Texture slots.
         */
        static void init();

        /**
         * Gets the number of available Texture slots on the device
         *
         * @warning TextureBuffer must be initialised before this method is called. Otherwise, it will return 0.
         * @throws std::runtime_error: if there is no active goopylib window
         */
        [[nodiscard]] static int32_t getTextureSlots();

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;

        uint32_t m_RendererID = 0;

        static int32_t s_TextureSlots;

        [[nodiscard]] uint32_t _getDataFormat() const;

        [[nodiscard]] int32_t _getInternalFormat() const;
    };
}
