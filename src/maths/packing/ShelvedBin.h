#pragma once

#include "gp.h"
#include "Bin.h"

namespace gp::packing {
    class Shelf;

    class GPAPI ShelvedBin final : public Bin {

        friend class ShelfPackingAlgorithm;

    public:
        ShelvedBin(float width, float height, uint32_t page);

        bool fitsOpenShelf(Item &item) const;

        bool fitsShelf(Item &item, Shelf &shelf) const;

        bool fitsNewShelf(Item &item) const;

        Shelf &getOpenShelf();

        const std::vector<Shelf> &getShelves() const;

        [[nodiscard]] std::vector<Shelf>::iterator begin();

        [[nodiscard]] std::vector<Shelf>::iterator end();

    private:
        std::vector<Shelf> m_Shelves;
        float m_AvailableHeight;
        float m_PackedHeight = 0;

        void addShelf();

        void add(Item &item, Shelf &shelf);
    };
}
