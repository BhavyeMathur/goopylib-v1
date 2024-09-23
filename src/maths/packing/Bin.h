#pragma once

#include "gp.h"
#include "Item.h"


namespace gp::packing {
    class GPAPI Bin {

    public:
        /**
         * @return a vector of items held by this bin
         */
        [[nodiscard]] const std::vector<Item> &items() const;

        /**
         * @return the width of this bin
         */
        [[nodiscard]] float width() const;

        /**
         * @return the height of this bin
         */
        [[nodiscard]] float height() const;

        /**
         * @return the index of this bin in the rectangle packing
         */
        [[nodiscard]] uint32_t page() const;

    protected:
        const float m_Width;
        const float m_Height;
        const uint32_t m_Page;

        std::vector<Item> m_Items;  // TODO m_Items should reserve space when packAll() is called

        Bin(float width, float height, uint32_t page);

        /**
         * @return adds a copy of item to this bin and sets its position to (x, y)
         *
         * @note this method copies item, further changes to item will not be reflected in the bin's copy
         */
        void add(Item &item, float x, float y);
    };
}
