#pragma once

#include "gp.h"
#include "Item.h"


namespace gp::packing {
    class GPAPI Bin {

    public:
        [[nodiscard]] const std::vector<Item> &items() const;

        [[nodiscard]] float width() const;

        [[nodiscard]] float height() const;

        [[nodiscard]] uint32_t page() const;

    protected:
        const float m_Width;
        const float m_Height;
        const uint32_t m_Page;

        std::vector<Item> m_Items;  // TODO m_Items should reserve space when packAll() is called

        Bin(float width, float height, uint32_t page);
    };
}
