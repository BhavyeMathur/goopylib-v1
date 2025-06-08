#pragma once

#include "gp.h"
#include "Bin.h"

namespace gp::packing {
    class Shelf;

    class GPAPI ShelvedBin final : public Bin {

        friend class ShelfPackingAlgorithm;

    public:
        /**
         * An item is said to fit the top-most shelf if:
         *      1. The shelf has enough horizontal space (shelf.availableWidth >= item.width)
         *      2. Adding the item to the shelf would keep the item in this bin (shelf.y + item.height <= bin.height)
         *
         * @return whether the item fits the top-most shelf of this bin
         */
        bool fitsOpenShelf(Item &item) const;

        /**
         * If the given shelf is the top-most shelf (i.e. the shelf is open), see ShelvedBin::fitsOpenShelf()
         *
         * If the given shelf is closed (i.e. its height is fixed), an item is said to fit in it if:
         *      1. The shelf has enough horizontal space (shelf.availableWidth >= item.width)
         *      2. The shelf has enough vertical space (item.height <= shelf.height)
         *
         * @return whether the item fits the given shelf in this bin
         */
        bool fitsShelf(Item &item, Shelf &shelf) const;

        /**
         * An item is said to fit a new shelf if item.height <= bin.availableHeight
         *
         * @return whether the item would fit a new shelf above the current top-most one
         */
        bool fitsNewShelf(Item &item) const;

        /**
         * @return the top-most shelf of this bin
         */
        Shelf &getOpenShelf();

        /**
         * @return a vector of Shelves contained in this ShelvedBin
         */
        const std::vector<Shelf> &getShelves() const;

        [[nodiscard]] std::vector<Shelf>::iterator begin();

        [[nodiscard]] std::vector<Shelf>::iterator end();

    private:
        std::vector<Shelf> m_Shelves;
        float m_AvailableHeight;
        float m_PackedHeight = 0;

        ShelvedBin(float width, float height, uint32_t page);

        /**
         * Closes the top-most shelf of this bin and adds a new, open shelf to the top
         */
        void addShelf();

        /**
         * Adds the item to a shelf in this bin & updates the shelf that contains it
         *
         * @throws std::value_error if the item does not fit vertically into the bin
         */
        void add(Item &item, Shelf &shelf);
    };
}
