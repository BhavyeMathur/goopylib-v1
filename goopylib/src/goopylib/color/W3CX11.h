#pragma once

#include "gp.h"
#include "Color.h"
#include <unordered_map>

namespace gp {
    static std::unordered_map<const char *, ColorHex *> colors;

    void initW3CX11();

    void deallocateW3CX11();
}
