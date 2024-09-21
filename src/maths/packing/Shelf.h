#pragma once

#include "gp.h"
#include "PackingAlgorithm.h"

namespace gp::packing {
    class ShelvedBin;

    class Item;

    class Bin;

    namespace shelf {
        class NextFit;

        class FirstFit;

        class ScoredFit;
    }
}

// Shelf Class
namespace gp::packing::shelf {
    class GPAPI Shelf {

        friend class gp::packing::ShelvedBin;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        [[nodiscard]] std::string toString() const;

        [[nodiscard]] float getWidth() const;

        [[nodiscard]] float getHeight() const;

        [[nodiscard]] float getVerticalOffset() const;

        [[nodiscard]] float getPackedWidth() const;

        [[nodiscard]] float getAvailableWidth() const;

        [[nodiscard]] bool isOpen() const;

    private:
        const float m_Width;
        float m_Height = 0;

        float m_PackedWidth = 0;
        float m_AvailableWidth;
        const float m_VerticalOffset;

        bool m_IsOpen = true;

        Bin &m_Bin;
        std::vector<shared_ptr<Item>> m_Items;

        Shelf(float verticalOffset, Bin &bin);

        [[nodiscard]] bool fits(const shared_ptr<Item> &item) const;

        [[nodiscard]] bool fitsAbove(const shared_ptr<Item> &item) const;

        void add(const shared_ptr<Item>& item);

        void close();

        [[nodiscard]] float packedArea() const;
    };
}
