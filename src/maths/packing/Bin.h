#pragma once

#include "gp.h"

namespace gp::packing::shelf {
    class Shelf;
}

namespace gp::packing {
    class Item;

    class GPAPI Bin {

        friend class shelf::Shelf;

    public:
        Bin(const Bin &) = delete;

        [[nodiscard]] virtual float packingRatio() const;

        [[nodiscard]] const std::vector<Item> &items() const;

        [[nodiscard]] float width() const;

        [[nodiscard]] float height() const;

    protected:
        const float m_Width;
        const float m_Height;

        std::vector<Item> m_Items;

        Bin(float width, float height);

        void add(Item &item);
    };
}
