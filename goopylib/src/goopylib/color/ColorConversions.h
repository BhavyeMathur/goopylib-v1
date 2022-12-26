#pragma once

#include "gp.h"
#include "ColorStructs.h"

namespace gp {
    
    // RGB to other format

    namespace rgb {
        /**
         * Converts a color from RGB to a Hexadecimal string
         *
         * @param red between 0 and 255
         * @param green between 0 and 255
         * @param blue between 0 and 255
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a hexstring in the format "#rrggbb"
         */
        const char *toHex(int red, int green, int blue);

        /**
         * Converts a color from RGB to CMYK
         *
         * @param red between 0 and 255
         * @param green between 0 and 255
         * @param blue between 0 and 255
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of CMYK values between 0 and 1
         */
        CMYK toCMYK(int red, int green, int blue);

        /**
         * Converts a color from RGB to HSL
         *
         * @param red between 0 and 255
         * @param green between 0 and 255
         * @param blue between 0 and 255
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of HSL values
         */
        HSL toHSL(int red, int green, int blue);

        /**
         * Converts a color from RGB to HSV
         *
         * @param red between 0 and 255
         * @param green between 0 and 255
         * @param blue between 0 and 255
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of HSV values
         */
        HSV toHSV(int red, int green, int blue);
    }

    // Hex to other format

    namespace hex {
        /**
         * Converts a color hexstring to RGB
         *
         * @param hexstring a valid color hexadecimal string
         *
         * @throws std::invalid_argument if the hexstring is invalid
         *
         * @return a struct of RGB values between 0 and 255
         */
        RGB toRGB(const char *hexstring);

        /**
         * Converts a color hexstring to CMYK
         *
         * @param hexstring a valid color hexadecimal string
         *
         * @throws std::invalid_argument if the hexstring is invalid
         *
         * @return a struct of CMYK values between 0 and 1
         */
        CMYK toCMYK(const char *hexstring);

        /**
         * Converts a color hexstring to HSL
         *
         * @param hexstring a valid color hexadecimal string
         *
         * @throws std::invalid_argument if the hexstring is invalid
         *
         * @return a struct of HSL values
         */
        HSL toHSL(const char *hexstring);

        /**
         * Converts a color hexstring to HSV
         *
         * @param hexstring a valid color hexadecimal string
         *
         * @throws std::invalid_argument if the hexstring is invalid
         *
         * @return a struct of HSV values
         */
        HSV toHSV(const char *hexstring);
    }

    // CMYK to other format

    namespace cmyk {
        /**
         * Converts a color from CMYK to RGB
         *
         * @param cyan between 0 and 1
         * @param magenta between 0 and 1
         * @param yellow between 0 and 1
         * @param key between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of RGB values between 0 and 255
         */
        RGB toRGB(float cyan, float magenta, float yellow, float key);

        /**
         * Converts a color from CMYK to a Hexadecimal string
         *
         * @param cyan between 0 and 1
         * @param magenta between 0 and 1
         * @param yellow between 0 and 1
         * @param key between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a hexstring in the format "#rrggbb"
         */
        const char *toHex(float cyan, float magenta, float yellow, float key);

        /**
         * Converts a color from CMYK to HSL
         *
         * @param cyan between 0 and 1
         * @param magenta between 0 and 1
         * @param yellow between 0 and 1
         * @param key between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of HSL values
         */
        HSL toHSL(float cyan, float magenta, float yellow, float key);

        /**
         * Converts a color from CMYK to HSV
         *
         * @param cyan between 0 and 1
         * @param magenta between 0 and 1
         * @param yellow between 0 and 1
         * @param key between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of HSV values
         */
        HSV toHSV(float cyan, float magenta, float yellow, float key);
    }

    // HSV to other format

    namespace hsv {
        /**
         * Converts a color from HSV to RGB
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param value between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of RGB values between 0 and 255
         */
        RGB toRGB(int hue, float saturation, float value);

        /**
         * Converts a color from HSV to a Hexadecimal string
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param value between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a hexstring in the format "#rrggbb"
         */
        const char *toHex(int hue, float saturation, float value);

        /**
         * Converts a color from HSV to CMYK
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param value between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of CMYK values between 0 and 1
         */
        CMYK toCMYK(int hue, float saturation, float value);

        /**
         * Converts a color from HSV to HSL
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param value between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of HSL values
         */
        HSL toHSL(int hue, float saturation, float value);
    }

    // HSL to other format

    namespace hsl {
        /**
         * Converts a color from HSL to RGB
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param luminance between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of RGB values between 0 and 255
         */
        RGB toRGB(int hue, float saturation, float luminance);

        /**
        * Converts a color from HSL to a Hexadecimal string
        *
        * @param hue between 0 and 360
        * @param saturation between 0 and 1
        * @param luminance between 0 and 1
        *
        * @throws std::invalid_argument if the inputs are outside their bounds
        *
        * @return a hexstring in the format "#rrggbb"
        */
        const char *toHex(int hue, float saturation, float luminance);

        /**
         * Converts a color from HSL to CMYK
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param luminance between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of CMYK values between 0 and 1
         */
        CMYK toCMYK(int hue, float saturation, float luminance);

        /**
         * Converts a color from HSL to HSV
         *
         * @param hue between 0 and 360
         * @param saturation between 0 and 1
         * @param luminance between 0 and 1
         *
         * @throws std::invalid_argument if the inputs are outside their bounds
         *
         * @return a struct of HSV values
         */
        HSV toHSV(int hue, float saturation, float luminance);
    }
}
