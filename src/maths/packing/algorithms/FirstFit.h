#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"
#include "maths/packing/ShelvedBin.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/Item.h"


namespace gp::packing::shelf {
    class GPAPI FirstFit final : public ShelfPackingAlgorithm {

    public:
        FirstFit(float binWidth, float binHeight);

        void pack(Item &item, bool allowRotation) override;
    };
}
