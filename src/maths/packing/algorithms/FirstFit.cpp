#include "FirstFit.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"


namespace gp::packing::shelf {
    FirstFit::FirstFit(float
                       binWidth, float
                       binHeight)
            : ShelfPackingAlgorithm(binWidth, binHeight) {
    }

    void FirstFit::pack(Item &item, bool allowRotation) {
        for (const auto &bin: m_Bins) {
            for (auto &shelf: *bin) {
                if (allowRotation and (item.isVertical() != (item.getLongSide() <= shelf.getHeight())))
                    item.rotate();

                if (shelf.fits(item))
                    return addItemToShelf(item, shelf);
            }

            if (bin->m_OpenShelf->fitsAbove(item)) {
                if (allowRotation and item.isVertical())
                    item.rotate();

                return addItemToShelf(item, bin->addShelf());
            }
        }
        // code only reaches here if item has not been added to a shelf
        m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));

        if (allowRotation and item.isVertical())
            item.rotate();

        const auto &newBin = m_Bins.back();
        const auto &newShelf = newBin->m_OpenShelf;
        addItemToShelf(item, *newShelf);
    }
}
