#pragma once

#include "gp.h"
#include "ShelfPackingAlgorithm.h"
#include "maths/packing/Item.h"
#include "maths/packing/ShelvedBin.h"
#include "maths/packing/Shelf.h"


namespace gp::packing {
    class GPAPI NextFit final : public ShelfPackingAlgorithm {

    public:
        NextFit(float binWidth, float binHeight);

        void pack(Item &item, bool allowRotation) override;
    };
}
