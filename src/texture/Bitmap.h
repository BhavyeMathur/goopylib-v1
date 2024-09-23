#pragma once

#include "gp.h"


namespace gp {
    class GPAPI Bitmap {

        friend class Image;

    public:
        /**
         * An object which controls a buffer of RGB/RGBA byte data
         *
         * @param width the width (in pixels) of the bitmap
         * @param height the height (in pixels) of the bitmap
         * @param channels the number of channels in the bitmap (3 for RGB, 4 for RGBA)
         */
        Bitmap(uint32_t width, uint32_t height, uint32_t channels);

        /**
         * An object which controls a buffer of RGB/RGBA byte data
         *
         * @param filepath valid filepath to image
         *
         * @throws std::runtime_error file not found
         * @throws std::value_error valid bitmap must have 3 or 4 channels
         */
        Bitmap(const char *filepath);

        /**
         * If the bitmap was loaded using stbi_load, frees the image data using stbi_image_free
         * Otherwise, frees the self-allocated bitmap data
         */
        ~Bitmap();

        /**
         * @return the width (in pixels) of the bitmap
         */
        [[nodiscard]] uint32_t getWidth() const;

        /**
         * @return the height (in pixels) of the bitmap
         */
        [[nodiscard]] uint32_t getHeight() const;

        /**
         * @return the number of channels in the bitmap (3 for RGB, 4 for RGBA)
         */
        [[nodiscard]] uint32_t getChannels() const;

        /**
         * @return a raw pointer to the beginning of the bitmap byte data
         */
        [[nodiscard]] uint8_t *getData() const;

        /**
         * @return sets the value of a byte at position x, y, and channel
         */
        void setValue(uint32_t x, uint32_t y, uint32_t channel, uint8_t value);

        /**
         * @return retrieves the value of a byte at position x, y, and channel
         */
        [[nodiscard]] uint8_t getValue(uint32_t x, uint32_t y, uint32_t channel) const;

        /**
         * Sets a pixel of values at position x, y
         *
         * @param value a buffer of pixel bytes (3 bytes for RGB, 4 bytes for RGBA)
         */
        void setPixel(uint32_t x, uint32_t y, uint8_t *value);

        /**
         * Gets a buffer of pixel values at position x, y
         *
         * @return 3 bytes for RGB, 4 bytes for RGBA
         */
        [[nodiscard]] uint8_t *getPixel(uint32_t x, uint32_t y) const;

        /**
         * Copies another bitmap into this bitmap, starting at position x, y
         *
         * @param bitmap the bitmap whose data to copy
         * @param x the x value of the top-left corner at which to start the copy
         * @param y the y value of the top-left corner at which to start the copy
         */
        void setSubdata(Bitmap &bitmap, uint32_t x, uint32_t y);

        /**
         * Converts a position x, y, and channel to the index of the byte in the bitmap data
         *
         * @return the index of the byte representing position x, y, and channel
         */
        [[nodiscard]] uint32_t getIndex(uint32_t x, uint32_t y, uint32_t channel) const;

        /**
         * Saves the bitmap to an image file
         *
         * @param filepath valid filepath to save the image
         */
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
