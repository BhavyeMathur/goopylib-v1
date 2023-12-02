#include "W3CX11.h"

#include <memory>

#if !GP_LOG_W3CX11
#undef GP_LOGGING_LEVEL
#endif

#include "src/goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_W3CX11
#undef GP_VALUE_CHECKING
#endif

#include "src/goopylib/debug/Error.h"

namespace gp {
    GPAPI std::unordered_map<std::string, std::unique_ptr<ColorHex>> colors;

    void initW3CX11() {
        GP_CORE_DEBUG("gp::initW3CX11()");

        colors["aliceblue"] = std::make_unique<ColorHex>("f0f8ff");
        colors["antiquewhite"] = std::make_unique<ColorHex>("faebd7");
        colors["aqua"] = std::make_unique<ColorHex>("00ffff");
        colors["aquamarine"] = std::make_unique<ColorHex>("7fffd4");
        colors["azure"] = std::make_unique<ColorHex>("f0ffff");
        colors["beige"] = std::make_unique<ColorHex>("f5f5dc");
        colors["bisque"] = std::make_unique<ColorHex>("ffe4c4");
        colors["black"] = std::make_unique<ColorHex>("000000");
        colors["blanchedalmond"] = std::make_unique<ColorHex>("ffebcd");
        colors["blue"] = std::make_unique<ColorHex>("0000ff");
        colors["blueviolet"] = std::make_unique<ColorHex>("8a2be2");
        colors["brown"] = std::make_unique<ColorHex>("a52a2a");
        colors["burlywood"] = std::make_unique<ColorHex>("deb887");
        colors["cadetblue"] = std::make_unique<ColorHex>("5f9ea0");
        colors["chartreuse"] = std::make_unique<ColorHex>("7fff00");
        colors["chocolate"] = std::make_unique<ColorHex>("d2691e");
        colors["coral"] = std::make_unique<ColorHex>("ff7f50");
        colors["cornflower"] = std::make_unique<ColorHex>("6495ed");
        colors["cornflowerblue"] = std::make_unique<ColorHex>("6495ed");
        colors["cornsilk"] = std::make_unique<ColorHex>("fff8dc");
        colors["crimson"] = std::make_unique<ColorHex>("dc143c");
        colors["cyan"] = std::make_unique<ColorHex>("00ffff");
        colors["darkblue"] = std::make_unique<ColorHex>("00008b");
        colors["darkcyan"] = std::make_unique<ColorHex>("008b8b");
        colors["darkgoldenrod"] = std::make_unique<ColorHex>("b8860b");
        colors["darkgray"] = std::make_unique<ColorHex>("a9a9a9");
        colors["darkgreen"] = std::make_unique<ColorHex>("006400");
        colors["darkgrey"] = std::make_unique<ColorHex>("a9a9a9");
        colors["darkkhaki"] = std::make_unique<ColorHex>("bdb76b");
        colors["darkmagenta"] = std::make_unique<ColorHex>("8b008b");
        colors["darkolivegreen"] = std::make_unique<ColorHex>("556b2f");
        colors["darkorange"] = std::make_unique<ColorHex>("ff8c00");
        colors["darkorchid"] = std::make_unique<ColorHex>("9932cc");
        colors["darkred"] = std::make_unique<ColorHex>("8b0000");
        colors["darksalmon"] = std::make_unique<ColorHex>("e9967a");
        colors["darkseagreen"] = std::make_unique<ColorHex>("8fbc8f");
        colors["darkslateblue"] = std::make_unique<ColorHex>("483d8b");
        colors["darkslategray"] = std::make_unique<ColorHex>("2f4f4f");
        colors["darkslategrey"] = std::make_unique<ColorHex>("2f4f4f");
        colors["darkturquoise"] = std::make_unique<ColorHex>("00ced1");
        colors["darkviolet"] = std::make_unique<ColorHex>("9400d3");
        colors["deeppink"] = std::make_unique<ColorHex>("ff1493");
        colors["deepskyblue"] = std::make_unique<ColorHex>("00bfff");
        colors["dimgray"] = std::make_unique<ColorHex>("696969");
        colors["dimgrey"] = std::make_unique<ColorHex>("696969");
        colors["dodgerblue"] = std::make_unique<ColorHex>("1e90ff");
        colors["firebrick"] = std::make_unique<ColorHex>("b22222");
        colors["floralwhite"] = std::make_unique<ColorHex>("fffaf0");
        colors["forestgreen"] = std::make_unique<ColorHex>("228b22");
        colors["fuchsia"] = std::make_unique<ColorHex>("ff00ff");
        colors["gainsboro"] = std::make_unique<ColorHex>("dcdcdc");
        colors["ghostwhite"] = std::make_unique<ColorHex>("f8f8ff");
        colors["gold"] = std::make_unique<ColorHex>("ffd700");
        colors["goldenrod"] = std::make_unique<ColorHex>("daa520");
        colors["gray"] = std::make_unique<ColorHex>("808080");
        colors["green"] = std::make_unique<ColorHex>("008000");
        colors["greenyellow"] = std::make_unique<ColorHex>("adff2f");
        colors["grey"] = std::make_unique<ColorHex>("808080");
        colors["honeydew"] = std::make_unique<ColorHex>("f0fff0");
        colors["hotpink"] = std::make_unique<ColorHex>("ff69b4");
        colors["indianred"] = std::make_unique<ColorHex>("cd5c5c");
        colors["indigo"] = std::make_unique<ColorHex>("4b0082");
        colors["ivory"] = std::make_unique<ColorHex>("fffff0");
        colors["khaki"] = std::make_unique<ColorHex>("f0e68c");
        colors["laserlemon"] = std::make_unique<ColorHex>("ffff54");
        colors["lavender"] = std::make_unique<ColorHex>("e6e6fa");
        colors["lavenderblush"] = std::make_unique<ColorHex>("fff0f5");
        colors["lawngreen"] = std::make_unique<ColorHex>("7cfc00");
        colors["lemonchiffon"] = std::make_unique<ColorHex>("fffacd");
        colors["lightblue"] = std::make_unique<ColorHex>("add8e6");
        colors["lightcoral"] = std::make_unique<ColorHex>("f08080");
        colors["lightcyan"] = std::make_unique<ColorHex>("e0ffff");
        colors["lightgoldenrod"] = std::make_unique<ColorHex>("fafad2");
        colors["lightgoldenrodyellow"] = std::make_unique<ColorHex>("fafad2");
        colors["lightgray"] = std::make_unique<ColorHex>("d3d3d3");
        colors["lightgreen"] = std::make_unique<ColorHex>("90ee90");
        colors["lightgrey"] = std::make_unique<ColorHex>("d3d3d3");
        colors["lightpink"] = std::make_unique<ColorHex>("ffb6c1");
        colors["lightsalmon"] = std::make_unique<ColorHex>("ffa07a");
        colors["lightseagreen"] = std::make_unique<ColorHex>("20b2aa");
        colors["lightskyblue"] = std::make_unique<ColorHex>("87cefa");
        colors["lightslategray"] = std::make_unique<ColorHex>("778899");
        colors["lightslategrey"] = std::make_unique<ColorHex>("778899");
        colors["lightsteelblue"] = std::make_unique<ColorHex>("b0c4de");
        colors["lightyellow"] = std::make_unique<ColorHex>("ffffe0");
        colors["lime"] = std::make_unique<ColorHex>("00ff00");
        colors["limegreen"] = std::make_unique<ColorHex>("32cd32");
        colors["linen"] = std::make_unique<ColorHex>("faf0e6");
        colors["magenta"] = std::make_unique<ColorHex>("ff00ff");
        colors["maroon"] = std::make_unique<ColorHex>("800000");
        colors["maroon2"] = std::make_unique<ColorHex>("7f0000");
        colors["maroon3"] = std::make_unique<ColorHex>("b03060");
        colors["mediumaquamarine"] = std::make_unique<ColorHex>("66cdaa");
        colors["mediumblue"] = std::make_unique<ColorHex>("0000cd");
        colors["mediumorchid"] = std::make_unique<ColorHex>("ba55d3");
        colors["mediumpurple"] = std::make_unique<ColorHex>("9370db");
        colors["mediumseagreen"] = std::make_unique<ColorHex>("3cb371");
        colors["mediumslateblue"] = std::make_unique<ColorHex>("7b68ee");
        colors["mediumspringgreen"] = std::make_unique<ColorHex>("00fa9a");
        colors["mediumturquoise"] = std::make_unique<ColorHex>("48d1cc");
        colors["mediumvioletred"] = std::make_unique<ColorHex>("c71585");
        colors["midnightblue"] = std::make_unique<ColorHex>("191970");
        colors["mintcream"] = std::make_unique<ColorHex>("f5fffa");
        colors["mistyrose"] = std::make_unique<ColorHex>("ffe4e1");
        colors["moccasin"] = std::make_unique<ColorHex>("ffe4b5");
        colors["navajowhite"] = std::make_unique<ColorHex>("ffdead");
        colors["navy"] = std::make_unique<ColorHex>("000080");
        colors["oldlace"] = std::make_unique<ColorHex>("fdf5e6");
        colors["olive"] = std::make_unique<ColorHex>("808000");
        colors["olivedrab"] = std::make_unique<ColorHex>("6b8e23");
        colors["orange"] = std::make_unique<ColorHex>("ffa500");
        colors["orangered"] = std::make_unique<ColorHex>("ff4500");
        colors["orchid"] = std::make_unique<ColorHex>("da70d6");
        colors["palegoldenrod"] = std::make_unique<ColorHex>("eee8aa");
        colors["palegreen"] = std::make_unique<ColorHex>("98fb98");
        colors["paleturquoise"] = std::make_unique<ColorHex>("afeeee");
        colors["palevioletred"] = std::make_unique<ColorHex>("db7093");
        colors["papayawhip"] = std::make_unique<ColorHex>("ffefd5");
        colors["peachpuff"] = std::make_unique<ColorHex>("ffdab9");
        colors["peru"] = std::make_unique<ColorHex>("cd853f");
        colors["pink"] = std::make_unique<ColorHex>("ffc0cb");
        colors["plum"] = std::make_unique<ColorHex>("dda0dd");
        colors["powderblue"] = std::make_unique<ColorHex>("b0e0e6");
        colors["purple"] = std::make_unique<ColorHex>("800080");
        colors["purple2"] = std::make_unique<ColorHex>("7f007f");
        colors["purple3"] = std::make_unique<ColorHex>("a020f0");
        colors["rebeccapurple"] = std::make_unique<ColorHex>("663399");
        colors["red"] = std::make_unique<ColorHex>("ff0000");
        colors["rosybrown"] = std::make_unique<ColorHex>("bc8f8f");
        colors["royalblue"] = std::make_unique<ColorHex>("4169e1");
        colors["saddlebrown"] = std::make_unique<ColorHex>("8b4513");
        colors["salmon"] = std::make_unique<ColorHex>("fa8072");
        colors["sandybrown"] = std::make_unique<ColorHex>("f4a460");
        colors["seagreen"] = std::make_unique<ColorHex>("2e8b57");
        colors["seashell"] = std::make_unique<ColorHex>("fff5ee");
        colors["sienna"] = std::make_unique<ColorHex>("a0522d");
        colors["silver"] = std::make_unique<ColorHex>("c0c0c0");
        colors["skyblue"] = std::make_unique<ColorHex>("87ceeb");
        colors["slateblue"] = std::make_unique<ColorHex>("6a5acd");
        colors["slategray"] = std::make_unique<ColorHex>("708090");
        colors["slategrey"] = std::make_unique<ColorHex>("708090");
        colors["snow"] = std::make_unique<ColorHex>("fffafa");
        colors["springgreen"] = std::make_unique<ColorHex>("00ff7f");
        colors["steelblue"] = std::make_unique<ColorHex>("4682b4");
        colors["tan"] = std::make_unique<ColorHex>("d2b48c");
        colors["teal"] = std::make_unique<ColorHex>("008080");
        colors["thistle"] = std::make_unique<ColorHex>("d8bfd8");
        colors["tomato"] = std::make_unique<ColorHex>("ff6347");
        colors["turquoise"] = std::make_unique<ColorHex>("40e0d0");
        colors["violet"] = std::make_unique<ColorHex>("ee82ee");
        colors["wheat"] = std::make_unique<ColorHex>("f5deb3");
        colors["white"] = std::make_unique<ColorHex>("ffffff");
        colors["whitesmoke"] = std::make_unique<ColorHex>("f5f5f5");
        colors["yellow"] = std::make_unique<ColorHex>("ffff00");
        colors["yellowgreen"] = std::make_unique<ColorHex>("9acd32");
    }
}
