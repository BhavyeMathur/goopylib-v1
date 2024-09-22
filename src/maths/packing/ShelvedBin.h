#pragma once

#include "gp.h"
#include "Bin.h"

namespace gp::packing::shelf {
    class ShelfPackingAlgorithm;

    class NextFit;

    class FirstFit;

    class ScoredFit;
}

namespace gp::packing {
    class GPAPI ShelvedBin final : public Bin {

        friend class shelf::Shelf;

        friend class shelf::ShelfPackingAlgorithm;

        friend class shelf::NextFit;

        friend class shelf::FirstFit;

        friend class shelf::ScoredFit;

    public:
        [[nodiscard]] float packingRatio() const override;

        shelf::Shelf &getOpenShelf();

        const std::vector<shelf::Shelf> &getShelves();

        [[nodiscard]] std::vector<shelf::Shelf>::iterator begin();

        [[nodiscard]] std::vector<shelf::Shelf>::iterator end();

    private:
        std::vector<shelf::Shelf> m_Shelves;
        shelf::Shelf *m_OpenShelf;

        ShelvedBin(float width, float height);

        shelf::Shelf &addShelf();
    };
}
