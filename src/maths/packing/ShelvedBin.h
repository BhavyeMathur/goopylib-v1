#pragma once

#include "gp.h"
#include "Bin.h"

namespace gp::packing::shelf {
    class ShelfPackingAlgorithm;
}

namespace gp::packing {
    class GPAPI ShelvedBin final : public Bin {

        friend class shelf::ShelfPackingAlgorithm;

    public:
        ShelvedBin(float width, float height, uint32_t page);

        [[nodiscard]] float packingRatio() const override;

        bool fitsOpenShelf(Item &item) const;

        bool fitsShelf(Item &item, shelf::Shelf &shelf) const;

        bool fitsNewShelf(Item &item) const;

        void add(Item &item, shelf::Shelf &shelf);

        const shelf::Shelf &getOpenShelf() const;

        shelf::Shelf &getOpenShelf();

        const std::vector<shelf::Shelf> &getShelves() const;

        [[nodiscard]] std::vector<shelf::Shelf>::iterator begin();

        [[nodiscard]] std::vector<shelf::Shelf>::iterator end();

    private:
        std::vector<shelf::Shelf> m_Shelves;
        float m_AvailableHeight;
        float m_PackedHeight = 0;

        shelf::Shelf &addShelf();
    };
}
