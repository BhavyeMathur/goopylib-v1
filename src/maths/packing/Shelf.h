#pragma once

#include "gp.h"


namespace gp::packing {
    class Item;

    class GPAPI Shelf {

        friend class ShelvedBin;

        friend class ShelfPackingAlgorithm;

    public:
        /**
         * @return the width of this shelf
         */
        [[nodiscard]] float width() const;

        /**
         * @return the height of this shelf
         */
        [[nodiscard]] float height() const;

        /**
         * @return the y-position of the shelf in its bin
         */
        [[nodiscard]] float y() const;

        /**
         * @return the amount of the shelf that has already been packed with rectangles
         */
        [[nodiscard]] float packedWidth() const;

        /**
         * @return the amount of the shelf that is available to be packed
         */
        [[nodiscard]] float availableWidth() const;

        /**
         * @return whether the height of this shelf is fixed (i.e. is there another shelf above this one?)
         */
        [[nodiscard]] bool isOpen() const;

        /**
         * @param item the item to check for
         *
         * @return whether this shelf fits the long-end of an item without resizing its height (i.e. item.longSide <= shelf.height)
         */
        [[nodiscard]] bool fitsItemVertically(const Item &item) const;

        /**
         * @param item the item to check for
         *
         * @return whether this shelf fits the an item horizontally (i.e. item.width <= shelf.availableWidth)
         */
        [[nodiscard]] bool fitsItemHorizontally(const Item &item) const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_Y;

        bool m_IsOpen = true;

        Shelf(float y, float width);

        /**
         *
         * @param item
         *
         * @throws std::value_error if the item does not fit horizontally into the shelf
         *
         * @note vertical fit checks must be done by the code calling this method because this method only checks horizontal fit
         */
        void add(Item &item);

        /**
         * Disables the resizing of the shelf's height (i.e. when another shelf is added above this one)
         */
        void close();
    };
}
