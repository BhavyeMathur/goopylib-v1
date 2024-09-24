#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"


namespace gp::packing {
    class GPAPI FirstFit final : public ShelfPackingAlgorithm {

    public:
        /**
         * Uses a greedy first-fit algorithm to pack rectangles.
         */
        FirstFit(float binWidth, float binHeight);

    protected:
        void _packItem(Item &item, bool allowRotation) override;
    };
}
