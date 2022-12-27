#include "W3CX11.h"

#if !GP_LOG_W3CX11
#undef GP_LOGGING_LEVEL
#endif

#include "goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_W3CX11
#undef GP_VALUE_CHECKING
#endif

#include "goopylib/debug/Error.h"

namespace gp {
    void initW3CX11() {
        GP_CORE_DEBUG("gp::initW3CX11()");

        colors["aliceblue"] = new ColorHex("f0f8ff");
        colors["antiquewhite"] = new ColorHex("faebd7");
        colors["aqua"] = new ColorHex("00ffff");
        colors["aquamarine"] = new ColorHex("7fffd4");
        colors["azure"] = new ColorHex("f0ffff");
        colors["beige"] = new ColorHex("f5f5dc");
        colors["bisque"] = new ColorHex("ffe4c4");
        colors["black"] = new ColorHex("000000");
        colors["blanchedalmond"] = new ColorHex("ffebcd");
        colors["blue"] = new ColorHex("0000ff");
        colors["blueviolet"] = new ColorHex("8a2be2");
        colors["brown"] = new ColorHex("a52a2a");
        colors["burlywood"] = new ColorHex("deb887");
        colors["cadetblue"] = new ColorHex("5f9ea0");
        colors["chartreuse"] = new ColorHex("7fff00");
        colors["chocolate"] = new ColorHex("d2691e");
        colors["coral"] = new ColorHex("ff7f50");
        colors["cornflower"] = new ColorHex("6495ed");
        colors["cornflowerblue"] = new ColorHex("6495ed");
        colors["cornsilk"] = new ColorHex("fff8dc");
        colors["crimson"] = new ColorHex("dc143c");
        colors["cyan"] = new ColorHex("00ffff");
        colors["darkblue"] = new ColorHex("00008b");
        colors["darkcyan"] = new ColorHex("008b8b");
        colors["darkgoldenrod"] = new ColorHex("b8860b");
        colors["darkgray"] = new ColorHex("a9a9a9");
        colors["darkgreen"] = new ColorHex("006400");
        colors["darkgrey"] = new ColorHex("a9a9a9");
        colors["darkkhaki"] = new ColorHex("bdb76b");
        colors["darkmagenta"] = new ColorHex("8b008b");
        colors["darkolivegreen"] = new ColorHex("556b2f");
        colors["darkorange"] = new ColorHex("ff8c00");
        colors["darkorchid"] = new ColorHex("9932cc");
        colors["darkred"] = new ColorHex("8b0000");
        colors["darksalmon"] = new ColorHex("e9967a");
        colors["darkseagreen"] = new ColorHex("8fbc8f");
        colors["darkslateblue"] = new ColorHex("483d8b");
        colors["darkslategray"] = new ColorHex("2f4f4f");
        colors["darkslategrey"] = new ColorHex("2f4f4f");
        colors["darkturquoise"] = new ColorHex("00ced1");
        colors["darkviolet"] = new ColorHex("9400d3");
        colors["deeppink"] = new ColorHex("ff1493");
        colors["deepskyblue"] = new ColorHex("00bfff");
        colors["dimgray"] = new ColorHex("696969");
        colors["dimgrey"] = new ColorHex("696969");
        colors["dodgerblue"] = new ColorHex("1e90ff");
        colors["firebrick"] = new ColorHex("b22222");
        colors["floralwhite"] = new ColorHex("fffaf0");
        colors["forestgreen"] = new ColorHex("228b22");
        colors["fuchsia"] = new ColorHex("ff00ff");
        colors["gainsboro"] = new ColorHex("dcdcdc");
        colors["ghostwhite"] = new ColorHex("f8f8ff");
        colors["gold"] = new ColorHex("ffd700");
        colors["goldenrod"] = new ColorHex("daa520");
        colors["gray"] = new ColorHex("808080");
        colors["green"] = new ColorHex("008000");
        colors["greenyellow"] = new ColorHex("adff2f");
        colors["grey"] = new ColorHex("808080");
        colors["honeydew"] = new ColorHex("f0fff0");
        colors["hotpink"] = new ColorHex("ff69b4");
        colors["indianred"] = new ColorHex("cd5c5c");
        colors["indigo"] = new ColorHex("4b0082");
        colors["ivory"] = new ColorHex("fffff0");
        colors["khaki"] = new ColorHex("f0e68c");
        colors["laserlemon"] = new ColorHex("ffff54");
        colors["lavender"] = new ColorHex("e6e6fa");
        colors["lavenderblush"] = new ColorHex("fff0f5");
        colors["lawngreen"] = new ColorHex("7cfc00");
        colors["lemonchiffon"] = new ColorHex("fffacd");
        colors["lightblue"] = new ColorHex("add8e6");
        colors["lightcoral"] = new ColorHex("f08080");
        colors["lightcyan"] = new ColorHex("e0ffff");
        colors["lightgoldenrod"] = new ColorHex("fafad2");
        colors["lightgoldenrodyellow"] = new ColorHex("fafad2");
        colors["lightgray"] = new ColorHex("d3d3d3");
        colors["lightgreen"] = new ColorHex("90ee90");
        colors["lightgrey"] = new ColorHex("d3d3d3");
        colors["lightpink"] = new ColorHex("ffb6c1");
        colors["lightsalmon"] = new ColorHex("ffa07a");
        colors["lightseagreen"] = new ColorHex("20b2aa");
        colors["lightskyblue"] = new ColorHex("87cefa");
        colors["lightslategray"] = new ColorHex("778899");
        colors["lightslategrey"] = new ColorHex("778899");
        colors["lightsteelblue"] = new ColorHex("b0c4de");
        colors["lightyellow"] = new ColorHex("ffffe0");
        colors["lime"] = new ColorHex("00ff00");
        colors["limegreen"] = new ColorHex("32cd32");
        colors["linen"] = new ColorHex("faf0e6");
        colors["magenta"] = new ColorHex("ff00ff");
        colors["maroon"] = new ColorHex("800000");
        colors["maroon2"] = new ColorHex("7f0000");
        colors["maroon3"] = new ColorHex("b03060");
        colors["mediumaquamarine"] = new ColorHex("66cdaa");
        colors["mediumblue"] = new ColorHex("0000cd");
        colors["mediumorchid"] = new ColorHex("ba55d3");
        colors["mediumpurple"] = new ColorHex("9370db");
        colors["mediumseagreen"] = new ColorHex("3cb371");
        colors["mediumslateblue"] = new ColorHex("7b68ee");
        colors["mediumspringgreen"] = new ColorHex("00fa9a");
        colors["mediumturquoise"] = new ColorHex("48d1cc");
        colors["mediumvioletred"] = new ColorHex("c71585");
        colors["midnightblue"] = new ColorHex("191970");
        colors["mintcream"] = new ColorHex("f5fffa");
        colors["mistyrose"] = new ColorHex("ffe4e1");
        colors["moccasin"] = new ColorHex("ffe4b5");
        colors["navajowhite"] = new ColorHex("ffdead");
        colors["navy"] = new ColorHex("000080");
        colors["oldlace"] = new ColorHex("fdf5e6");
        colors["olive"] = new ColorHex("808000");
        colors["olivedrab"] = new ColorHex("6b8e23");
        colors["orange"] = new ColorHex("ffa500");
        colors["orangered"] = new ColorHex("ff4500");
        colors["orchid"] = new ColorHex("da70d6");
        colors["palegoldenrod"] = new ColorHex("eee8aa");
        colors["palegreen"] = new ColorHex("98fb98");
        colors["paleturquoise"] = new ColorHex("afeeee");
        colors["palevioletred"] = new ColorHex("db7093");
        colors["papayawhip"] = new ColorHex("ffefd5");
        colors["peachpuff"] = new ColorHex("ffdab9");
        colors["peru"] = new ColorHex("cd853f");
        colors["pink"] = new ColorHex("ffc0cb");
        colors["plum"] = new ColorHex("dda0dd");
        colors["powderblue"] = new ColorHex("b0e0e6");
        colors["purple"] = new ColorHex("800080");
        colors["purple2"] = new ColorHex("7f007f");
        colors["purple3"] = new ColorHex("a020f0");
        colors["rebeccapurple"] = new ColorHex("663399");
        colors["red"] = new ColorHex("ff0000");
        colors["rosybrown"] = new ColorHex("bc8f8f");
        colors["royalblue"] = new ColorHex("4169e1");
        colors["saddlebrown"] = new ColorHex("8b4513");
        colors["salmon"] = new ColorHex("fa8072");
        colors["sandybrown"] = new ColorHex("f4a460");
        colors["seagreen"] = new ColorHex("2e8b57");
        colors["seashell"] = new ColorHex("fff5ee");
        colors["sienna"] = new ColorHex("a0522d");
        colors["silver"] = new ColorHex("c0c0c0");
        colors["skyblue"] = new ColorHex("87ceeb");
        colors["slateblue"] = new ColorHex("6a5acd");
        colors["slategray"] = new ColorHex("708090");
        colors["slategrey"] = new ColorHex("708090");
        colors["snow"] = new ColorHex("fffafa");
        colors["springgreen"] = new ColorHex("00ff7f");
        colors["steelblue"] = new ColorHex("4682b4");
        colors["tan"] = new ColorHex("d2b48c");
        colors["teal"] = new ColorHex("008080");
        colors["thistle"] = new ColorHex("d8bfd8");
        colors["tomato"] = new ColorHex("ff6347");
        colors["turquoise"] = new ColorHex("40e0d0");
        colors["violet"] = new ColorHex("ee82ee");
        colors["wheat"] = new ColorHex("f5deb3");
        colors["white"] = new ColorHex("ffffff");
        colors["whitesmoke"] = new ColorHex("f5f5f5");
        colors["yellow"] = new ColorHex("ffff00");
        colors["yellowgreen"] = new ColorHex("9acd32");
    }

    void deallocateW3CX11() {
        GP_CORE_DEBUG("gp::deallocateW3CX11()");

        for (auto & color : colors) {
            delete color.second;
        }
        colors.clear();
    }
}
