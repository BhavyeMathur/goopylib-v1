#include "NextFit.h"


namespace gp::packing {
    NextFit::NextFit(float binWidth, float binHeight) : ShelfPackingAlgorithm(binWidth, binHeight) {
    }

    void NextFit::pack(Item &item, bool allowRotation) {
        auto &bin = m_Bins.back();
        auto &shelf = bin.getOpenShelf();

        orientItemForShelf(item, shelf, allowRotation);

        if (bin.fitsOpenShelf(item))
            return addItemToShelf(item, bin, bin.getOpenShelf());

        if (!tryAddingToNewShelf(item, bin, allowRotation))
            addItemToNewBin(item, false);  // allowRotation false since item is horizontal after tryAddingToNewShelf
    }
}
