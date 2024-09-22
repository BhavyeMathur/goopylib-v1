#pragma once

#include "gp.h"
#include "maths/packing/Item.h"

namespace gp::packing::shelf {
    class Shelf;
}

namespace gp::packing {
    class Item;

    class GPAPI Bin {

        friend class shelf::Shelf;

    public:
        [[nodiscard]] virtual float packingRatio() const;

        [[nodiscard]] const std::vector<Item> &items() const;

        [[nodiscard]] float width() const;

        [[nodiscard]] float height() const;

        [[nodiscard]] uint32_t page() const;

    protected:
        const float m_Width;
        const float m_Height;
        const uint32_t m_Page;

        std::vector<Item> m_Items;

        Bin(float width, float height, uint32_t page);

        void add(Item &item);
    };
}
