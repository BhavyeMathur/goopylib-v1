#pragma once

#include "gp.h"
#include "PackingAlgorithm.h"

namespace gp::packing {
    class ShelvedBin;

    class Item;

    class Bin;

    namespace shelf {
        class ShelfPackingAlgorithm;
    }
}

// Shelf Class
namespace gp::packing::shelf {
    class GPAPI Shelf {

        friend class gp::packing::ShelvedBin;

        friend class shelf::ShelfPackingAlgorithm;

    public:
        [[nodiscard]] std::string toString() const;

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

        [[nodiscard]] float getVerticalOffset() const;

        [[nodiscard]] float getPackedWidth() const;

        [[nodiscard]] float getAvailableWidth() const;

        [[nodiscard]] bool isOpen() const;

        [[nodiscard]] bool fits(const shared_ptr<Item> &item) const;

        [[nodiscard]] bool fitsAbove(const shared_ptr<Item> &item) const;

        [[nodiscard]] float packedArea() const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_VerticalOffset;

        bool m_IsOpen = true;

        Bin &m_Bin;
        std::vector<Item *> m_Items;

        Shelf(float verticalOffset, Bin &bin);

        void add(Item& item);

        void close();
    };
}
