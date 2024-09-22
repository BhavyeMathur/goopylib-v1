#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"

namespace gp::packing {
    class Item;
}

namespace gp::packing::shelf {
    class Shelf;

    using ScoringFunction = std::function<float(const Shelf &, const Item &)>;

    class GPAPI ScoredFit : public ShelfPackingAlgorithm {

        void updateScore(float &bestScore, bool &bestOrientation, Shelf *&bestShelf, Shelf &shelf, Item &item);



    public:
        ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction);

        void pack(Item &item, bool allowRotation) override;

    private:
        ScoringFunction m_ScoringFunction;
    };
}
