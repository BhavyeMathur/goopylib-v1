#include "FirstFit.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing::shelf {
    FirstFit::FirstFit(float binWidth, float binHeight) : ShelfPackingAlgorithm(binWidth, binHeight) {
    }

    void FirstFit::pack(Item &item, bool allowRotation) {
        for (const auto &bin: m_Bins) {
            for (auto &shelf: *bin) {
                orientItemForShelf(item, shelf, allowRotation);
                if (shelf.fits(item))
                    return addItemToShelf(item, shelf);
            }

            if (tryAddingToNewShelf(item, *bin->m_OpenShelf, *bin, allowRotation))
                return;
        }
        addItemToNewBin(item, allowRotation);
    }
}
