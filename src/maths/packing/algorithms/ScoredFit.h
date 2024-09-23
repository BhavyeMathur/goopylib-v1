#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"


namespace gp::packing {
    using ScoringFunction = std::function<float(const Shelf &, const Item &)>;

    class GPAPI ScoredFit : public ShelfPackingAlgorithm {

    public:
        ScoredFit(float binWidth, float binHeight, ScoringFunction scoringFunction);

        void pack(Item &item, bool allowRotation) override;

    private:
        ScoringFunction m_ScoringFunction;
    };
}
