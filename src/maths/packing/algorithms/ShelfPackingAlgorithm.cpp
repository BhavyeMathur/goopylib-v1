#include "ShelfPackingAlgorithm.h"
#include "maths/packing/Item.h"
#include "maths/packing/Shelf.h"
#include "maths/packing/ShelvedBin.h"
#include "ScoredFit.h"

#include "debug/Error.h"

namespace gp::packing::shelf {
    ShelfPackingAlgorithm::ShelfPackingAlgorithm(float binWidth, float binHeight)
            : PackingAlgorithm(binWidth, binHeight) {
        m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(binWidth, binHeight)));
    }

    ShelfPackingAlgorithm::ShelfPackingAlgorithm() : PackingAlgorithm(0, 0) {
    }

    void ShelfPackingAlgorithm::pack(Item &item, bool allowRotation) {
        GP_RUNTIME_ERROR("ShelfPackingAlgorithm::pack() unimplemented");
    }

    void ShelfPackingAlgorithm::packAll(std::vector<Item> &items, bool allowRotation,
                                        const SortingFunction &sortingFunction) {
        if (sortingFunction)
            items = sortingFunction(items);

        for (auto &item: items)
            pack(item, allowRotation);
    }

    void ShelfPackingAlgorithm::packOriented(Item &item, bool orientVertically) {
        if (item.isHorizontal() == orientVertically)
            item.rotate();

        pack(item, false);
    }

    void ShelfPackingAlgorithm::packAllOriented(std::vector<Item> &items, bool orientVertically,
                                                const SortingFunction &sortingFunction) {
        if (sortingFunction) {
            items = sortingFunction(items);

            for (auto &item: items)
                packOriented(item, orientVertically);
        }
    }

    std::vector<shared_ptr<ShelvedBin>> ShelfPackingAlgorithm::bins() const {
        std::vector<shared_ptr<ShelvedBin>>
                copy = m_Bins;
        return copy;
    }

    void ShelfPackingAlgorithm::addItemToShelf(Item &item, shelf::Shelf &shelf) {
        shelf.add(item);
    }

    NextFit::NextFit(float binWidth, float binHeight) : ShelfPackingAlgorithm(binWidth, binHeight),
                                                        m_Shelf(m_Bins.back()->m_OpenShelf) {
    }

    void NextFit::pack(Item &item, bool allowRotation) {
        if (allowRotation and (item.isVertical() != (item.getLongSide() <= m_Shelf->getHeight())))
            item.rotate();

        if (m_Shelf->fits(item))
            return addItemToShelf(item, *m_Shelf);

        if (m_Shelf->fitsAbove(item))
            m_Shelf = m_Bins.back()->addShelf();
        else {
            m_Bins.push_back(shared_ptr<ShelvedBin>(new ShelvedBin(m_BinWidth, m_BinHeight)));
            m_Shelf = m_Bins.back()->m_OpenShelf;
        }

        if (allowRotation and item.isVertical())
            item.rotate();

        return addItemToShelf(item, *m_Shelf);
    }

    FirstFit::FirstFit(float
                       binWidth, float
                       binHeight)
            : ShelfPackingAlgorithm(binWidth, binHeight) {
    }

    void FirstFit::pack(Item &item, bool allowRotation) {
        for (const auto &bin: m_Bins) {
            for (const auto &shelf: *bin) {
                if (allowRotation and (item.isVertical() != (item.getLongSide() <= shelf->getHeight())))
                    item.rotate();

                if (shelf->fits(item))
                    return addItemToShelf(item, *shelf);
            }

            if (bin->m_OpenShelf->fitsAbove(item)) {
                if (allowRotation and item.isVertical())
                    item.rotate();

                return addItemToShelf(item, *bin->addShelf());
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
