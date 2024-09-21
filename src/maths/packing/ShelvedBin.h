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

        shared_ptr<shelf::Shelf> getOpenShelf();

        std::vector<shared_ptr<shelf::Shelf>> getShelves();

        [[nodiscard]] std::vector<shared_ptr<shelf::Shelf>>::const_iterator begin() const;

        [[nodiscard]] std::vector<shared_ptr<shelf::Shelf>>::const_iterator end() const;

    private:
        shared_ptr<shelf::Shelf> m_OpenShelf;
        std::vector<shared_ptr<shelf::Shelf>> m_Shelves;

        ShelvedBin(float width, float height);

        shared_ptr<shelf::Shelf> addShelf();
    };
}
