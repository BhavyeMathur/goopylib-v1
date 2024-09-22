#pragma once

#include "gp.h"

namespace gp::packing {
    class ShelvedBin;

    class Item;

    class Bin;

    namespace shelf {
        class ShelfPackingAlgorithm;
    }
}

namespace gp::packing::shelf {
    class GPAPI Shelf {

        friend class gp::packing::ShelvedBin;

        friend class shelf::ShelfPackingAlgorithm;

    public:
        [[nodiscard]] std::string toString() const;

        [[nodiscard]] float width() const;

        [[nodiscard]] float height() const;

        [[nodiscard]] float area() const;

        [[nodiscard]] float getVerticalOffset() const;

        [[nodiscard]] float getPackedWidth() const;

        [[nodiscard]] float getAvailableWidth() const;

        [[nodiscard]] bool isOpen() const;

        [[nodiscard]] bool fits(const Item &item) const;

        [[nodiscard]] bool fitsShelfAbove(const Item &item) const;

        [[nodiscard]] bool fitsItemVertically(const Item &item) const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_VerticalOffset;

        bool m_IsOpen = true;

        ShelvedBin &m_Bin;

        Shelf(float verticalOffset, ShelvedBin &bin);

        void add(Item &item);

        void close();
    };
}
