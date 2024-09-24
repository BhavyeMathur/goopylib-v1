#pragma once

#include "gp.h"

#include "Bitmap.h"
#include "TextureBuffer.h"
#include "TextureCoords.h"

#include "maths/gpmath.h"
#include "maths/packing/algorithms/ScoredAlgorithms.h"

namespace gp {
    struct TextureAtlasCoords;

    class GPAPI TextureAtlas {

    public:
        TextureAtlas(const TextureAtlas &) = delete;

        /**
         * Creates a TextureAtlas that can be used to efficiently pack rectangular textures into a compact atlas.
         *
         * @param channels number of color channels in the textures (3 for RGB, 4 for RGBA)
         * @param packingAlgorithm the rectangle packing algorithm to use. Defaults to BestAreaFit.
         *
         * @note Ensure the TextureAtlas class has been initialised before constructing an object.
         */
        TextureAtlas(uint32_t channels, unique_ptr<packing::ShelfPackingAlgorithm> packingAlgorithm = nullptr);

        /**
         * Adds a bitmap to the TextureAtlas
         *
         * @param allowRotation whether the bitmap can be rotated. Defaults to true.
         * @return TextureAtlasCoords containing the UV coordinates of the bitmap in the texture
         *
         * @throws std::value_error if the bitmap is larger than the TextureAtlas dimensions
         */
        void add(const shared_ptr<Bitmap> &bitmap, bool allowRotation = true);

        /**
         * Adds multiple bitmaps to the TextureAtlas.
         *
         * @param allowRotation whether the bitmaps can be rotated. Defaults to true.
         * @param sorting the function to use to sort the bitmaps before packing. Defaults to sortByShortSide, use nullptr for no sorting.
         * @return a vector of TextureAtlasCoords containing the UV coordinates of the bitmaps added to the texture
         *
         * @throws std::value_error if any bitmap is larger than the TextureAtlas dimensions
         */
        void add(const std::vector<shared_ptr<Bitmap>> &bitmaps, bool allowRotation = true,
                 const packing::SortingFunction &sorting = packing::sortByShortSide(true));

        /**
         * Initialises the TextureAtlas class. In particular, retrieves the maximum dimensions of a texture atlas
         *
         * @throws std::runtime_error: if there is no active goopylib window
         */
        static void init();

        // TODO should these should be non-static methods that return the current packed width & height?
        /**
         * @return the width (in pixels) of the atlas
         */
        [[nodiscard]] static uint32_t width();

        /**
         * @return the height (in pixels) of the atlas
         */
        [[nodiscard]] static uint32_t height();

        /**
         * @return the number of packed pages in the atlas
         */
        [[nodiscard]] uint32_t pages();

        /**
         * @return whether the TextureAtlas contains the specified texture
         */
        [[nodiscard]] bool contains(const std::string &texture) const;

        /**
         *
         * @return the TextureData (UV coords, page) for a texture in the atlas
         *
         * @throws std::out_of_range if the texture is not in the atlas
         */
        [[nodiscard]] const TextureData &getTextureData(const std::string &texture) const;

        /**
         * @return the bitmap of the ith page in the atlas
         *
         * @throws std::out_of_range if the index i exceeds the number of pages in the atlas
         */
        [[nodiscard]] const shared_ptr<Bitmap> &getBitmap(uint32_t i) const;

        /**
         * @return the bitmap of the ith page in the atlas
         *
         * @throws std::out_of_range if the index i exceeds the number of pages in the atlas
         */
        [[nodiscard]] const shared_ptr<TextureBuffer> &getTextureBuffer(uint32_t i) const;

        /**
         * @return converts a pixel coordinate (x, y) to (u, v) coordinate..
         */
        [[nodiscard]] TextureAtlasCoords toUVCoordinate(Point x, Point y, uint32_t page);

        void _updateTextureBufferData();

    private:
        unique_ptr<packing::ShelfPackingAlgorithm> m_PackingAlgorithm;

        std::vector<shared_ptr<Bitmap>> m_Bitmaps;
        std::vector<shared_ptr<TextureBuffer>> m_TextureBuffers;
        std::unordered_map<std::string, TextureData> m_TexturesCache;

        const uint32_t m_Channels;

        static uint32_t s_Width;
        static uint32_t s_Height;


    };
}
