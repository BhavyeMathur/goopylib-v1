#pragma once

#include "gp.h"

namespace gp::packing {
    class Item;

    using SortingFunction = std::function<std::vector<Item>(std::vector<Item>)>;

    SortingFunction sortByWidth(bool descending = false);

    SortingFunction sortByHeight(bool descending = false);

    SortingFunction sortByPerimeter(bool descending = false);

    SortingFunction sortByArea(bool descending = false);

    SortingFunction sortBySideRatio(bool descending = false);

    SortingFunction sortByLongSide(bool descending = false);

    SortingFunction sortByShortSide(bool descending = false);
}
