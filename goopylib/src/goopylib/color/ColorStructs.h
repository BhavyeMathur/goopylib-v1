#pragma once

namespace gp {
    struct RGB {
        int red;
        int green;
        int blue;
    };

    struct CMYK {
        float cyan;
        float magenta;
        float yellow;
        float key;
    };

    struct HSV {
        int hue;
        float saturation;
        float value;
    };

    struct HSL {
        int hue;
        float saturation;
        float luminance;
    };
}
