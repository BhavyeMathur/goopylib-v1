#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"


namespace gp::packing {
    class GPAPI NextFit final : public ShelfPackingAlgorithm {

    public:
        /**
         * Uses a greedy next-fit algorithm to pack rectangles.
         */
        NextFit(float binWidth, float binHeight);

        void pack(Item &item, bool allowRotation) override;
    };
}
