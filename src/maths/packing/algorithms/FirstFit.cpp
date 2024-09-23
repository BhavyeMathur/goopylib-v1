#include "FirstFit.h"


namespace gp::packing {
    FirstFit::FirstFit(float binWidth, float binHeight) : ShelfPackingAlgorithm(binWidth, binHeight) {
    }

    void FirstFit::pack(Item &item, bool allowRotation) {
        for (auto &bin: m_Bins) {
            for (auto &shelf: bin) {
                orientItemForShelf(item, shelf, allowRotation);
                if (bin.fitsShelf(item, shelf))
                    return bin.add(item, shelf);
            }

            if (tryAddingToNewShelf(item, bin, allowRotation))
                return;
        }
        addItemToNewBin(item, allowRotation);
    }
}
