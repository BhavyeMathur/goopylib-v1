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

        [[nodiscard]] std::vector<Item *> items() const;

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

    protected:
        const float m_Width;
        const float m_Height;
        const uint32_t m_ID;

        std::vector<Item *> m_Items;

        static uint32_t s_Bins;

        Bin(float width, float height);

        void add(Item &item);
    };
}
