#pragma once

#include "gp.h"
#include "SortingAlgorithms.h"

namespace gp::packing {
    class Item;

    class GPAPI PackingAlgorithm {

    public:
        /**
         * @return the number of pages (bins) in the rectangle packing
         */
        [[nodiscard]] uint32_t pages() const;

        /**
         * Packs an item into a bin
         *
         * @param item the item to pack
         * @param allowRotation whether the item is allowed to be rotated. Defaults to true.
         *
         * @note for multiple items, use packAll() since packing ratio is often better after sorting the items
         *
         * @throws std::value_error if an item does not fit into the dimensions of the bin
         */
        void pack(Item &item, bool allowRotation);

        /**
         * Packs a vector of items into a bin, optionally after sorting them.
         *
         * @param items the items to pack
         * @param allowRotation whether the items are allowed to be rotated. Defaults to true.
         * @param sortingFunction the function to use for sorting the items. Defaults to sortByShortSide.
         *
         * @throws std::value_error if an item does not fit into the dimensions of the bin
         */
        void pack(std::vector<Item> &items, bool allowRotation = true,
                  const SortingFunction &sortingFunction = sortByShortSide(true));

    protected:
        const float m_BinWidth;
        const float m_BinHeight;

        uint32_t m_Pages = 0;

        PackingAlgorithm(float binWidth, float binHeight);

        virtual void _pack(std::vector<Item> &items, bool allowRotation = true) = 0;
    };
}
