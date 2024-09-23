#pragma once

#include "gp.h"
#include "Bin.h"

namespace gp::packing {
    class ShelfPackingAlgorithm;

    class Shelf;

    class GPAPI ShelvedBin final : public Bin {

        friend class ShelfPackingAlgorithm;

    public:
        ShelvedBin(float width, float height, uint32_t page);

        [[nodiscard]] float packingRatio() const override;

        bool fitsOpenShelf(Item &item) const;

        bool fitsShelf(Item &item, Shelf &shelf) const;

        bool fitsNewShelf(Item &item) const;

        void add(Item &item, Shelf &shelf);

        const Shelf &getOpenShelf() const;

        Shelf &getOpenShelf();

        const std::vector<Shelf> &getShelves() const;

        [[nodiscard]] std::vector<Shelf>::iterator begin();

        [[nodiscard]] std::vector<Shelf>::iterator end();

    private:
        std::vector<Shelf> m_Shelves;
        float m_AvailableHeight;
        float m_PackedHeight = 0;

        Shelf &addShelf();
    };
}
