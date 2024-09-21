#include "SortingAlgorithms.h"
#include "maths/packing/Item.h"

#define RETURN_SORTING_FUNC return [compare](std::vector<Item> items) {std::sort(items.begin(), items.end(), compare); return items;}

using CompareFunction = std::function<bool(const gp::packing::Item, const gp::packing::Item)>;

namespace gp::packing {
    SortingFunction sortByWidth(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return item1.getWidth() > item2.getWidth();
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return item1.getWidth() < item2.getWidth();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByHeight(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return item1.getHeight() > item2.getHeight();
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return item1.getHeight() < item2.getHeight();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByPerimeter(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return (item1.getWidth() + item1.getHeight()) >
                       (item2.getWidth() + item2.getHeight());
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return (item1.getWidth() + item1.getHeight()) <
                       (item2.getWidth() + item2.getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByArea(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return (item1.getWidth() * item1.getHeight()) >
                       (item2.getWidth() * item2.getHeight());
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return (item1.getWidth() * item1.getHeight()) <
                       (item2.getWidth() * item2.getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortBySideRatio(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return (item1.getWidth() / item1.getHeight()) >
                       (item2.getWidth() / item2.getHeight());
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return (item1.getWidth() / item1.getHeight()) <
                       (item2.getWidth() / item2.getHeight());
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByLongSide(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return item1.getLongSide() > item2.getLongSide();
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return item1.getLongSide() < item2.getLongSide();
            };

        RETURN_SORTING_FUNC;
    }

    SortingFunction sortByShortSide(bool descending) {
        CompareFunction compare;

        if (descending)
            compare = [](const Item &item1, const Item &item2) {
                return item1.getShortSide() > item2.getShortSide();
            };
        else
            compare = [](const Item &item1, const Item &item2) {
                return item1.getShortSide() < item2.getShortSide();
            };

        RETURN_SORTING_FUNC;
    }
}
