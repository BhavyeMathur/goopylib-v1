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
        [[nodiscard]] float packingRatio() const override;

        shelf::Shelf &getOpenShelf();

        const std::vector<shelf::Shelf> &getShelves();

        [[nodiscard]] std::vector<shelf::Shelf>::iterator begin();

        [[nodiscard]] std::vector<shelf::Shelf>::iterator end();

    private:
        std::vector<shelf::Shelf> m_Shelves;

        ShelvedBin(float width, float height);

        shelf::Shelf &addShelf();
    };
}
