#include "SortingAlgorithms.h"
#include "Item.h"

#define RETURN_SORTING_FUNC return [compare](std::vector<shared_ptr<Item>> items) {std::sort(items.begin(), items.end(), compare); return items;}

namespace gp::packing {
    SortingFunction sortByWidth(bool descending) {

        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getWidth() > item2->getWidth();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getWidth() < item2->getWidth();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByHeight(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getHeight() > item2->getHeight();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getHeight() < item2->getHeight();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByPerimeter(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() + item1->getHeight()) >
                       (item2->getWidth() + item2->getHeight());
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() + item1->getHeight()) <
                       (item2->getWidth() + item2->getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByArea(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() * item1->getHeight()) >
                       (item2->getWidth() * item2->getHeight());
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() * item1->getHeight()) <
                       (item2->getWidth() * item2->getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortBySideRatio(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() / item1->getHeight()) >
                       (item2->getWidth() / item2->getHeight());
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return (item1->getWidth() / item1->getHeight()) <
                       (item2->getWidth() / item2->getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByLongSide(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getLongSide() > item2->getLongSide();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getLongSide() < item2->getLongSide();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByShortSide(bool descending) {
        std::function<bool(const shared_ptr<Item>, const shared_ptr<Item>)> compare;

        if (descending)
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getShortSide() > item2->getShortSide();
            };
        else
            compare = [](const shared_ptr<Item> &item1, const shared_ptr<Item> &item2) {
                return item1->getShortSide() < item2->getShortSide();
            };

        RETURN_SORTING_FUNC;
    }
}
