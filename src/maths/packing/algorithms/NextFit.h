#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"

namespace gp::packing::shelf {
    class GPAPI NextFit final : public ShelfPackingAlgorithm {

    public:
        NextFit(float binWidth, float binHeight);

        void pack(Item &item, bool allowRotation) override;

    private:
        shared_ptr<Shelf> m_Shelf;
    };
}
