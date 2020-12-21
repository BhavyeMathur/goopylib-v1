#define PY_SSIZE_T_CLEAN

#define raiseGraphicsError(x) PyErr_SetObject(GraphicsError, PyUnicode_FromFormat(x)); return NULL;

#define rgb_to_hex_error "\n\nGraphicsError: unknown error in rgb_to_hex() function. Ensure all arguments are integers."
#define rgb_to_hex_red_incorrect "\n\nGraphicsError: red value for conversion from RGB to Hex must be an integer, " \
                                 "not %O", red_object
#define rgb_to_hex_green_incorrect "\n\nGraphicsError: green value for conversion from RGB to Hex must be an integer," \
                                   " not %O", green_object
#define rgb_to_hex_blue_incorrect "\n\nGraphicsError: blue value for conversion from RGB to Hex must be an integer, " \
                                  "not %O", blue_object
#define rgb_to_hex_red_outside_range "\n\nGraphicsError: red value for RGB to Hex conversion must be between 0 & 255," \
                                     " inclusive, 0 <= red <= 255, not %i", red
#define rgb_to_hex_green_outside_range "\n\nGraphicsError: green value for RGB to Hex conversion must be between" \
                                       " 0 & 255, inclusive, 0 <= green <= 255, not %i", green
#define rgb_to_hex_blue_outside_range "\n\nGraphicsError: blue value for RGB to Hex conversion must be between " \
                                      "0 & 255, inclusive, 0 <= blue <= 255, not %i", blue
                                      
#define rgb_to_cmyk_error "\n\nGraphicsError: unknown error in rgb_to_cmyk() function. Ensure all arguments are" \
                          " integers."
#define rgb_to_cmyk_red_incorrect "\n\nGraphicsError: red value for conversion from RGB to CMYK must be an integer, " \
                                 "not %O", red_object
#define rgb_to_cmyk_green_incorrect "\n\nGraphicsError: green value for conversion from RGB to CMYK must be an " \
                                   "integer, not %O", green_object
#define rgb_to_cmyk_blue_incorrect "\n\nGraphicsError: blue value for conversion from RGB to CMYK must be an " \
                                  "integer, not %O", blue_object
#define rgb_to_cmyk_red_outside_range "\n\nGraphicsError: red value for RGB to CMYK conversion must be between " \
                                     "0 & 255, inclusive, 0 <= red <= 255, not %i", red
#define rgb_to_cmyk_green_outside_range "\n\nGraphicsError: green value for RGB to CMYK conversion must be between" \
                                       " 0 & 255, inclusive, 0 <= green <= 255, not %i", green
#define rgb_to_cmyk_blue_outside_range "\n\nGraphicsError: blue value for RGB to CMYK conversion must be between " \
                                      "0 & 255, inclusive, 0 <= blue <= 255, not %i", blue
                                      
#define rgb_to_hsv_error "\n\nGraphicsError: unknown error in rgb_to_hsv() function. Ensure all arguments are" \
                          " integers."
#define rgb_to_hsv_red_incorrect "\n\nGraphicsError: red value for conversion from RGB to HSV must be an integer, " \
                                 "not %O", red_object
#define rgb_to_hsv_green_incorrect "\n\nGraphicsError: green value for conversion from RGB to HSV must be an " \
                                   "integer, not %O", green_object
#define rgb_to_hsv_blue_incorrect "\n\nGraphicsError: blue value for conversion from RGB to HSV must be an " \
                                  "integer, not %O", blue_object
#define rgb_to_hsv_red_outside_range "\n\nGraphicsError: red value for RGB to HSV conversion must be between " \
                                     "0 & 255, inclusive, 0 <= red <= 255, not %i", red
#define rgb_to_hsv_green_outside_range "\n\nGraphicsError: green value for RGB to HSV conversion must be between" \
                                       " 0 & 255, inclusive, 0 <= green <= 255, not %i", green
#define rgb_to_hsv_blue_outside_range "\n\nGraphicsError: blue value for RGB to HSV conversion must be between " \
                                      "0 & 255, inclusive, 0 <= blue <= 255, not %i", blue
                                      
#define rgb_to_hsl_error "\n\nGraphicsError: unknown error in rgb_to_hsl() function. Ensure all arguments are" \
                          " integers."
#define rgb_to_hsl_red_incorrect "\n\nGraphicsError: red value for conversion from RGB to HSL must be an integer, " \
                                 "not %O", red_object
#define rgb_to_hsl_green_incorrect "\n\nGraphicsError: green value for conversion from RGB to HSL must be an " \
                                   "integer, not %O", green_object
#define rgb_to_hsl_blue_incorrect "\n\nGraphicsError: blue value for conversion from RGB to HSL must be an " \
                                  "integer, not %O", blue_object
#define rgb_to_hsl_red_outside_range "\n\nGraphicsError: red value for RGB to HSL conversion must be between " \
                                     "0 & 255, inclusive, 0 <= red <= 255, not %i", red
#define rgb_to_hsl_green_outside_range "\n\nGraphicsError: green value for RGB to HSL conversion must be between" \
                                       " 0 & 255, inclusive, 0 <= green <= 255, not %i", green
#define rgb_to_hsl_blue_outside_range "\n\nGraphicsError: blue value for RGB to HSL conversion must be between " \
                                      "0 & 255, inclusive, 0 <= blue <= 255, not %i", blue

#define hex_digit_to_int_incorrect_input "\n\nGraphicsError: digit value for hex_digit_to_int() function must be " \
                                         "between 0 & f (inclusive), not '%c'", letter
#define hex_to_rgb_error "\n\nGraphicsError: unknown error in hex_to_rgb() function. Ensure argument is string."
#define hex_to_rgb_failed_string_conversion "\n\nGraphicsError: failed conversion of string argument to ASCII for " \
                                            "hex_to_rgb() function. Ensure argument is a string, not %O", hexobject
#define hex_to_cmyk_error "\n\nGraphicsError: unknown error in hex_to_cmyk() function. Ensure argument is string."
#define hex_to_cmyk_failed_string_conversion "\n\nGraphicsError: failed conversion of string argument to ASCII for " \
                                            "hex_to_cmyk() function. Ensure argument is a string, not %O", hexobject
#define hex_to_hsl_error "\n\nGraphicsError: unknown error in hex_to_hsl() function. Ensure argument is string."
#define hex_to_hsl_failed_string_conversion "\n\nGraphicsError: failed conversion of string argument to ASCII for " \
                                            "hex_to_hsl() function. Ensure argument is a string, not %O", hexobject
#define hex_to_hsv_error "\n\nGraphicsError: unknown error in hex_to_hsv() function. Ensure argument is string."
#define hex_to_hsv_failed_string_conversion "\n\nGraphicsError: failed conversion of string argument to ASCII for " \
                                            "hex_to_hsv() function. Ensure argument is a string, not %O", hexobject

#define cmyk_to_rgb_error "\n\nGraphicsError: unknown error in cmyk_to_rgb() function. Ensure arguments are integers."
#define cmyk_to_rgb_cyan_outside_range "\n\nGraphicsError: cyan value for CMYK to RGB conversion must be between " \
                                       "0 & 100, inclusive, 0 <= cyan <= 100, not %i", cyan
#define cmyk_to_rgb_magenta_outside_range "\n\nGraphicsError: magenta value for CMYK to RGB conversion must be " \
                                          "between 0 & 100, inclusive, 0 <= magenta <= 100, not %i", magenta
#define cmyk_to_rgb_yellow_outside_range "\n\nGraphicsError: yellow value for CMYK to RGB conversion must be between " \
                                         "0 & 100, inclusive, 0 <= yellow <= 100, not %i", yellow
#define cmyk_to_rgb_key_outside_range "\n\nGraphicsError: key value for CMYK to RGB conversion must be between " \
                                      "0 & 100, inclusive, 0 <= key <= 100, not %i", key

#define cmyk_to_hex_error "\n\nGraphicsError: unknown error in cmyk_to_hex() function. Ensure arguments are integers."
#define cmyk_to_hex_cyan_outside_range "\n\nGraphicsError: cyan value for CMYK to Hex conversion must be between " \
                                       "0 & 100, inclusive, 0 <= cyan <= 100, not %i", cyan
#define cmyk_to_hex_magenta_outside_range "\n\nGraphicsError: magenta value for CMYK to Hex conversion must be " \
                                          "between 0 & 100, inclusive, 0 <= magenta <= 100, not %i", magenta
#define cmyk_to_hex_yellow_outside_range "\n\nGraphicsError: yellow value for CMYK to Hex conversion must be between " \
                                         "0 & 100, inclusive, 0 <= yellow <= 100, not %i", yellow
#define cmyk_to_hex_key_outside_range "\n\nGraphicsError: key value for CMYK to Hex conversion must be between " \
                                      "0 & 100, inclusive, 0 <= key <= 100, not %i", key

#define cmyk_to_hsl_error "\n\nGraphicsError: unknown error in cmyk_to_hsl() function. Ensure arguments are integers."                    
#define cmyk_to_hsl_cyan_outside_range "\n\nGraphicsError: cyan value for CMYK to HSL conversion must be between " \
                                       "0 & 100, inclusive, 0 <= cyan <= 100, not %i", cyan
#define cmyk_to_hsl_magenta_outside_range "\n\nGraphicsError: magenta value for CMYK to HSL conversion must be " \
                                          "between 0 & 100, inclusive, 0 <= magenta <= 100, not %i", magenta
#define cmyk_to_hsl_yellow_outside_range "\n\nGraphicsError: yellow value for CMYK to HSL conversion must be between " \
                                         "0 & 100, inclusive, 0 <= yellow <= 100, not %i", yellow
#define cmyk_to_hsl_key_outside_range "\n\nGraphicsError: key value for CMYK to HSL conversion must be between " \
                                      "0 & 100, inclusive, 0 <= key <= 100, not %i", key

#define cmyk_to_hsv_error "\n\nGraphicsError: unknown error in cmyk_to_hsv() function. Ensure arguments are integers."                           
#define cmyk_to_hsv_cyan_outside_range "\n\nGraphicsError: cyan value for CMYK to HSV conversion must be between " \
                                       "0 & 100, inclusive, 0 <= cyan <= 100, not %i", cyan
#define cmyk_to_hsv_magenta_outside_range "\n\nGraphicsError: magenta value for CMYK to HSV conversion must be " \
                                          "between 0 & 100, inclusive, 0 <= magenta <= 100, not %i", magenta
#define cmyk_to_hsv_yellow_outside_range "\n\nGraphicsError: yellow value for CMYK to HSV conversion must be between " \
                                         "0 & 100, inclusive, 0 <= yellow <= 100, not %i", yellow
#define cmyk_to_hsv_key_outside_range "\n\nGraphicsError: key value for CMYK to HSV conversion must be between " \
                                      "0 & 100, inclusive, 0 <= key <= 100, not %i", key

#define hsv_to_rgb_error "\n\nGraphicsError: unknown error in hsv_to_rgb() function. Ensure arguments are integers."
#define hsv_to_rgb_saturation_outside_range "\n\nGraphicsError: saturation value for HSV to RGB conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsv_to_rgb_value_outside_range "\n\nGraphicsError: value value for HSV to RGB conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", value

#define hsv_to_hex_error "\n\nGraphicsError: unknown error in hsv_to_hex() function. Ensure arguments are integers."                      
#define hsv_to_hex_saturation_outside_range "\n\nGraphicsError: saturation value for HSV to Hex conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsv_to_hex_value_outside_range "\n\nGraphicsError: value value for HSV to Hex conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", value
                                       
#define hsv_to_cmyk_error "\n\nGraphicsError: unknown error in hsv_to_cmyk() function. Ensure arguments are integers."
#define hsv_to_cmyk_saturation_outside_range "\n\nGraphicsError: saturation value for HSV to CMYK conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsv_to_cmyk_value_outside_range "\n\nGraphicsError: value value for HSV to CMYK conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", value
                                       
#define hsv_to_hsl_error "\n\nGraphicsError: unknown error in hsv_to_hsl() function. Ensure arguments are integers."
#define hsv_to_hsl_saturation_outside_range "\n\nGraphicsError: saturation value for HSV to HSL conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsv_to_hsl_value_outside_range "\n\nGraphicsError: value value for HSV to HSL conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", value
                                       
#define hsl_to_rgb_error "\n\nGraphicsError: unknown error in hsl_to_rgb() function. Ensure arguments are integers."
#define hsl_to_rgb_saturation_outside_range "\n\nGraphicsError: saturation value for HSL to RGB conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsl_to_rgb_luminance_outside_range "\n\nGraphicsError: luminance value for HSL to RGB conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", luminance
                                       
#define hsl_to_hex_error "\n\nGraphicsError: unknown error in hsl_to_hex() function. Ensure arguments are integers."
#define hsl_to_hex_saturation_outside_range "\n\nGraphicsError: saturation value for HSL to Hex conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsl_to_hex_luminance_outside_range "\n\nGraphicsError: luminance value for HSL to Hex conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", luminance
                                       
#define hsl_to_cmyk_error "\n\nGraphicsError: unknown error in hsl_to_cmyk() function. Ensure arguments are integers."
#define hsl_to_cmyk_saturation_outside_range "\n\nGraphicsError: saturation value for HSL to CMYK conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsl_to_cmyk_luminance_outside_range "\n\nGraphicsError: luminance value for HSL to CMYK conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", luminance
                                       
#define hsl_to_hsv_error "\n\nGraphicsError: unknown error in hsl_to_hsv() function. Ensure arguments are integers."
#define hsl_to_hsv_saturation_outside_range "\n\nGraphicsError: saturation value for HSL to HSV conversion must be " \
                                            "between 0 & 100, inclusive, 0 <= saturation <= 100, not %i", saturation
#define hsl_to_hsv_luminance_outside_range "\n\nGraphicsError: luminance value for HSL to HSV conversion must be " \
                                       "between 0 & 100, inclusive, 0 <= value <= 100, not %i", luminance

#include <Python.h>
#include <structmember.h>

static PyObject *GraphicsError;

static PyObject *Colour_reference;
static PyObject *ColourRGB_reference;
static PyObject *ColourCMYK_reference;
static PyObject *ColourHSL_reference;
static PyObject *ColourHSV_reference;

/*
------------------------------------------------------------------------------------------------------------------------
Internal Functions

*/

int exponentMod(int base, int power, int modulo)
{
    // base cases
    if (base == 0)
        return 0;
    if (power == 0)
        return 1;

    // If power is even
    long y;
    if (power % 2 == 0) {
        y = exponentMod(base, power / 2, modulo);
        y = (y * y) % modulo;
    }

    // If power is odd
    else {
        y = base % modulo;
        y = (y * exponentMod(base, power - 1, modulo) % modulo) % modulo;
    }

    return (int)((y + modulo) % modulo);
}

/*
------------------------------------------------------------------------------------------------------------------------
Colour Structure Definitions

*/

struct ColourRGB {
    int red, green, blue;
};

struct ColourCMYK {
    int cyan, magenta, yellow, key;
};

struct ColourHSL {
    int hue, saturation, luminance;
};

struct ColourHSV {
    int hue, saturation, value;
};

/*
------------------------------------------------------------------------------------------------------------------------
COLOUR TYPE CONVERSIONS

*/


// RGB to other format

char* rgb_to_hex(int red, int green, int blue) {
    static char hex_string[7];

    sprintf(hex_string, "#%02x%02x%02x", red, green, blue);
    return hex_string;
}

struct ColourCMYK rgb_to_cmyk(int red, int green, int blue) {
    float redf = red / 255.0f;
    float greenf = green / 255.0f;
    float bluef = blue / 255.0f;

    float maximum;
    if (redf > greenf) {
        maximum = redf;
    }
    else {
        maximum = greenf;
    }

    if (bluef > maximum) {
        maximum = bluef;
    }

    float k = 1 - maximum;
    float k_inverse = 1 - k;

    struct ColourCMYK return_value = {(int)round(100 * (k_inverse - redf) / k_inverse),
                                      (int)round(100 * (k_inverse - greenf) / k_inverse),
                                      (int)round(100 * (k_inverse - bluef) / k_inverse),
                                      (int)round(100 * k)};

    return return_value;
}

struct ColourHSL rgb_to_hsl(int red, int green, int blue) {
    float redf = red / 255.0f;
    float greenf = green / 255.0f;
    float bluef = blue / 255.0f;

    float cmax, cmin;

    if (redf > greenf) {
        cmax = redf;
        cmin = greenf;
    }
    else {
        cmax = greenf;
        cmin = redf;
    }

    if (bluef > cmax) {
        cmax = bluef;
    }
    else if (bluef < cmin) {
        cmin = bluef;
    }

    float delta = cmax - cmin;
    float L = 0.5f * (cmax + cmin);

    float h, s;

    if (delta == 0.0f) {
        h = 0;
        s = 0;
    }
    else if (cmax == redf) {
        h = 60 * (float)fmod((greenf - bluef) / delta, 6);
        s = delta / (1 - fabsf(2 * L - 1));
    }
    else if (cmax == greenf) {
        h = 60 * (((bluef - redf) / delta) + 2);
        s = delta / (1 - fabsf(2 * L - 1));
    }
    else {
        h = 60 * (((redf - greenf) / delta) + 4);
        s = delta / (1 - fabsf(2 * L - 1));
    }

    struct ColourHSL return_value = {(int)round(h),
                                     (int)round(100 * s),
                                     (int)round(100 * L)};

    return return_value;
}

struct ColourHSV rgb_to_hsv(int red, int green, int blue) {
    float redf = red / 255.0f;
    float greenf = green / 255.0f;
    float bluef = blue / 255.0f;

    float cmax, cmin;

    if (redf > greenf) {
        cmax = redf;
        cmin = greenf;
    }
    else {
        cmax = greenf;
        cmin = redf;
    }

    if (bluef > cmax) {
        cmax = bluef;
    }
    else if (bluef < cmin) {
        cmin = bluef;
    }

    float delta = cmax - cmin;

    float h, s;

    if (delta == 0.0f) {
        h = 0;
    }
    else if (cmax == redf) {
        h = 60 * (float)fmod((greenf - bluef) / delta, 6);
    }
    else if (cmax == greenf) {
        h = 60 * (((bluef - redf) / delta) + 2);
    }
    else {
        h = 60 * (((redf - greenf) / delta) + 4);
    }

    if (cmax == 0.0f) {
        s = 0.0f;
    }
    else {
        s = delta / cmax;
    }

    struct ColourHSV return_value = {(int)round(h),
                                     (int)round(100 * s),
                                     (int)round(100 * cmax)};

    return return_value;
}


// Hex to other format

int hex_digit_to_int(char digit) {

    digit = tolower(digit);

    if (isdigit(digit)) {
        return digit - '0';
    }
    else if (digit == 'a') {
        return 10;
    }
    else if (digit == 'b') {
        return 11;
    }
    else if (digit == 'c') {
        return 12;
    }
    else if (digit == 'd') {
        return 13;
    }
    else if (digit == 'e') {
        return 14;
    }
    else if (digit == 'f') {
        return 15;
    }
    return -1;
}

struct ColourRGB hex_to_rgb(char *hexstring) {
    struct ColourRGB return_value = {(16 * hex_digit_to_int(hexstring[1])) + hex_digit_to_int(hexstring[2]),
                                     (16 * hex_digit_to_int(hexstring[3])) + hex_digit_to_int(hexstring[4]),
                                     (16 * hex_digit_to_int(hexstring[5])) + hex_digit_to_int(hexstring[6])};

    return return_value;
}

struct ColourCMYK hex_to_cmyk(char *hexstring) {
    struct ColourRGB colour_rgb = hex_to_rgb(hexstring);

    float redf = colour_rgb.red / 255.0f;
    float greenf = colour_rgb.green / 255.0f;
    float bluef = colour_rgb.blue / 255.0f;

    float maximum;
    if (redf > greenf) {
        maximum = redf;
    }
    else {
        maximum = greenf;
    }

    if (bluef > maximum) {
        maximum = bluef;
    }

    float k = 1 - maximum;
    float k_inverse = 1 - k;

    struct ColourCMYK return_value = {(int)round(100 * (k_inverse - redf) / k_inverse),
                                      (int)round(100 * (k_inverse - greenf) / k_inverse),
                                      (int)round(100 * (k_inverse - bluef) / k_inverse),
                                      (int)round(100 * k)};

    return return_value;
}

struct ColourHSL hex_to_hsl(char *hexstring) {
    struct ColourRGB colour_rgb = hex_to_rgb(hexstring);

    float redf = colour_rgb.red / 255.0f;
    float greenf = colour_rgb.green / 255.0f;
    float bluef = colour_rgb.blue / 255.0f;

    float cmax, cmin;

    if (redf > greenf) {
        cmax = redf;
        cmin = greenf;
    }
    else {
        cmax = greenf;
        cmin = redf;
    }

    if (bluef > cmax) {
        cmax = bluef;
    }
    else if (bluef < cmin) {
        cmin = bluef;
    }

    float delta = cmax - cmin;
    float L = 0.5f * (cmax + cmin);

    float h, s;

    if (delta == 0.0f) {
        h = 0;
        s = 0;
    }
    else if (cmax == redf) {
        h = 60 * (float)fmod((greenf - bluef) / delta, 6);
        s = delta / (1 - fabsf(2 * L - 1));
    }
    else if (cmax == greenf) {
        h = 60 * (((bluef - redf) / delta) + 2);
        s = delta / (1 - fabsf(2 * L - 1));
    }
    else {
        h = 60 * (((redf - greenf) / delta) + 4);
        s = delta / (1 - fabsf(2 * L - 1));
    }

    struct ColourHSL return_value = {(int)round(h),
                                     (int)round(100 * s),
                                     (int)round(100 * L)};

    return return_value;
}

struct ColourHSV hex_to_hsv(char *hexstring) {
    struct ColourRGB colour_rgb = hex_to_rgb(hexstring);

    float redf = colour_rgb.red / 255.0f;
    float greenf = colour_rgb.green / 255.0f;
    float bluef = colour_rgb.blue / 255.0f;

    float cmax, cmin;

    if (redf > greenf) {
        cmax = redf;
        cmin = greenf;
    }
    else {
        cmax = greenf;
        cmin = redf;
    }

    if (bluef > cmax) {
        cmax = bluef;
    }
    else if (bluef < cmin) {
        cmin = bluef;
    }

    float delta = cmax - cmin;

    float h, s;

    if (delta == 0.0f) {
        h = 0;
    }
    else if (cmax == redf) {
        h = 60 * (float)fmod((greenf - bluef) / delta, 6);
    }
    else if (cmax == greenf) {
        h = 60 * (((bluef - redf) / delta) + 2);
    }
    else {
        h = 60 * (((redf - greenf) / delta) + 4);
    }

    if (cmax == 0.0f) {
        s = 0.0f;
    }
    else {
        s = delta / cmax;
    }

    struct ColourHSV return_value = {(int)round(h),
                                     (int)round(100 * s),
                                     (int)round(100 * cmax)};

    return return_value;
}

// CMYK to other format

struct ColourRGB cmyk_to_rgb(int cyan, int magenta, int yellow, int key) {
    struct ColourRGB return_value = {(int)round(255 * (1 - (cyan + key) / 100.0f)),
                                     (int)round(255 * (1 - (magenta + key) / 100.0f)),
                                     (int)round(255 * (1 - (yellow + key) / 100.0f))};

    return return_value;
}

char* cmyk_to_hex(int cyan, int magenta, int yellow, int key) {
    static char hex_string[7];

    sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (1 - (cyan + key) / 100.0f)),
                                         (int)round(255 * (1 - (magenta + key) / 100.0f)),
                                         (int)round(255 * (1 - (yellow + key) / 100.0f)));
    return hex_string;
}

struct ColourHSL cmyk_to_hsl(int cyan, int magenta, int yellow, int key) {
    float redf = 1 - (cyan + key) / 100.0f;
    float greenf = 1 - (magenta + key) / 100.0f;
    float bluef = 1 - (yellow + key) / 100.0f;

    float cmax, cmin;

    if (redf > greenf) {
        cmax = redf;
        cmin = greenf;
    }
    else {
        cmax = greenf;
        cmin = redf;
    }

    if (bluef > cmax) {
        cmax = bluef;
    }
    else if (bluef < cmin) {
        cmin = bluef;
    }

    float delta = cmax - cmin;
    float L = 0.5f * (cmax + cmin);

    float h, s;

    if (delta == 0.0f) {
        h = 0;
        s = 0;
    }
    else if (cmax == redf) {
        h = 60 * (float)fmod((greenf - bluef) / delta, 6);
        s = delta / (1 - fabsf(2 * L - 1));
    }
    else if (cmax == greenf) {
        h = 60 * (((bluef - redf) / delta) + 2);
        s = delta / (1 - fabsf(2 * L - 1));
    }
    else {
        h = 60 * (((redf - greenf) / delta) + 4);
        s = delta / (1 - fabsf(2 * L - 1));
    }

    struct ColourHSL return_value = {(int)round(h),
                                     (int)round(100 * s),
                                     (int)round(100 * L)};

    return return_value;
}

struct ColourHSV cmyk_to_hsv(int cyan, int magenta, int yellow, int key) {
    float redf = 1 - (cyan + key) / 100.0f;
    float greenf = 1 - (magenta + key) / 100.0f;
    float bluef = 1 - (yellow + key) / 100.0f;

    float cmax, cmin;

    if (redf > greenf) {
        cmax = redf;
        cmin = greenf;
    }
    else {
        cmax = greenf;
        cmin = redf;
    }

    if (bluef > cmax) {
        cmax = bluef;
    }
    else if (bluef < cmin) {
        cmin = bluef;
    }

    float delta = cmax - cmin;

    float h, s;

    if (delta == 0.0f) {
        h = 0;
    }
    else if (cmax == redf) {
        h = 60 * (float)fmod((greenf - bluef) / delta, 6);
    }
    else if (cmax == greenf) {
        h = 60 * (((bluef - redf) / delta) + 2);
    }
    else {
        h = 60 * (((redf - greenf) / delta) + 4);
    }

    if (cmax == 0.0f) {
        s = 0.0f;
    }
    else {
        s = delta / cmax;
    }

    struct ColourHSV return_value = {(int)round(h),
                                     (int)round(100 * s),
                                     (int)round(100 * cmax)};

    return return_value;
}

// HSV to other format

struct ColourRGB hsv_to_rgb(int hue, int saturation, int value) {
    float saturationf = saturation / 100.0f;
    float valuef = value / 100.0f;

    float c = valuef * saturationf;
    float x = c * (1 - fabsf((float)fmod(hue / 60.0f, 2) - 1));
    float m = valuef - c;

    struct ColourRGB return_value;

    if (hue < 60) {
        return_value.red = (int)round(255 * (c + m));
        return_value.green = (int)round(255 * (x + m));
        return_value.blue = (int)round(255 * (m));
    }
    else if (hue < 120) {
        return_value.red = (int)round(255 * (x + m));
        return_value.green = (int)round(255 * (c + m));
        return_value.blue = (int)round(255 * (m));
    }
    else if (hue < 180) {
        return_value.red = (int)round(255 * (m));
        return_value.green = (int)round(255 * (c + m));
        return_value.blue = (int)round(255 * (x + m));
    }
    else if (hue < 240) {
        return_value.red = (int)round(255 * (m));
        return_value.green = (int)round(255 * (x + m));
        return_value.blue = (int)round(255 * (c + m));
    }
    else if (hue < 300) {
        return_value.red = (int)round(255 * (x + m));
        return_value.green = (int)round(255 * (m));
        return_value.blue = (int)round(255 * (c + m));
    }
    else {
        return_value.red = (int)round(255 * (c + m));
        return_value.green = (int)round(255 * (m));
        return_value.blue = (int)round(255 * (x + m));
    }

    return return_value;
}

char* hsv_to_hex(int hue, int saturation, int value) {
    float saturationf = saturation / 100.0f;
    float valuef = value / 100.0f;

    float c = valuef * saturationf;
    float x = c * (1 - fabsf((float)fmod(hue / 60.0f, 2) - 1));
    float m = valuef - c;

    static char hex_string[7];

    if (hue < 60) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (c + m)),
                                             (int)round(255 * (x + m)),
                                             (int)round(255 * (m)));
    }
    else if (hue < 120) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (x + m)),
                                             (int)round(255 * (c + m)),
                                             (int)round(255 * (m)));
    }
    else if (hue < 180) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (m)),
                                             (int)round(255 * (c + m)),
                                             (int)round(255 * (x + m)));
    }
    else if (hue < 240) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (m)),
                                             (int)round(255 * (x + m)),
                                             (int)round(255 * (c + m)));
    }
    else if (hue < 300) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (x + m)),
                                             (int)round(255 * (m)),
                                             (int)round(255 * (c + m)));
    }
    else {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (c + m)),
                                             (int)round(255 * (m)),
                                             (int)round(255 * (x + m)));
    }

    return hex_string;
}

struct ColourCMYK hsv_to_cmyk(int hue, int saturation, int value) {
    float saturationf = saturation / 100.0f;
    float valuef = value / 100.0f;

    float c = valuef * saturationf;
    float x = c * (1 - fabsf((float)fmod(hue / 60.0f, 2) - 1));
    float m = valuef - c;

    float red, green, blue;

    if (hue < 60) {
        red = c + m;
        green = x + m;
        blue = m;
    }
    else if (hue < 120) {
        red = x + m;
        green = c + m;
        blue = m;
    }
    else if (hue < 180) {
        red = m;
        green = c + m;
        blue = x + m;
    }
    else if (hue < 240) {
        red = m;
        green = x + m;
        blue = c + m;
    }
    else if (hue < 300) {
        red = x + m;
        green = m;
        blue = c + m;
    }
    else {
        red = c + m;
        green = m;
        blue = x + m;
    }

    float maximum;
    if (red > green) {
        maximum = red;
    }
    else {
        maximum = green;
    }

    if (blue > maximum) {
        maximum = blue;
    }

    float k = 1 - maximum;
    float k_inverse = 1 - k;

    struct ColourCMYK return_value = {(int)round(100 * (k_inverse - red) / k_inverse),
                                      (int)round(100 * (k_inverse - green) / k_inverse),
                                      (int)round(100 * (k_inverse - blue) / k_inverse),
                                      (int)round(100 * k)};

    return return_value;
}

struct ColourHSL hsv_to_hsl(int hue, int saturation, int value) {
    float saturationf = saturation / 100.0f;
    float valuef = value / 100.0f;

    float L = valuef - (0.5f * valuef * saturationf);
    if (L == 0) {
        saturationf = 0;
    }
    else {
        float minimum;
        if (L < 1 - L) {
            minimum = L;
        }
        else {
            minimum = 1 - L;
        }
        saturationf = (valuef - L) / minimum;
    }

    struct ColourHSL return_value = {hue,
                                     (int)round(100 * saturationf),
                                     (int)round(100 * L)};

    return return_value;
}

// HSL to other format

struct ColourRGB hsl_to_rgb(int hue, int saturation, int luminance) {
    float saturationf = saturation / 100.0f;
    float luminancef = luminance / 100.0f;

    float c = (1 - fabsf(2 * luminancef - 1)) * saturationf;
    float x = c * (1 - fabsf((float)fmod(hue / 60.0f, 2) - 1));
    float m = luminancef - c / 2.0f;

    struct ColourRGB return_value;

    if (hue < 60) {
        return_value.red = (int)round(255 * (c + m));
        return_value.green = (int)round(255 * (x + m));
        return_value.blue = (int)round(255 * (m));
    }
    else if (hue < 120) {
        return_value.red = (int)round(255 * (x + m));
        return_value.green = (int)round(255 * (c + m));
        return_value.blue = (int)round(255 * (m));
    }
    else if (hue < 180) {
        return_value.red = (int)round(255 * (m));
        return_value.green = (int)round(255 * (c + m));
        return_value.blue = (int)round(255 * (x + m));
    }
    else if (hue < 240) {
        return_value.red = (int)round(255 * (m));
        return_value.green = (int)round(255 * (x + m));
        return_value.blue = (int)round(255 * (c + m));
    }
    else if (hue < 300) {
        return_value.red = (int)round(255 * (x + m));
        return_value.green = (int)round(255 * (m));
        return_value.blue = (int)round(255 * (c + m));
    }
    else {
        return_value.red = (int)round(255 * (c + m));
        return_value.green = (int)round(255 * (m));
        return_value.blue = (int)round(255 * (x + m));
    }

    return return_value;
}

char* hsl_to_hex(int hue, int saturation, int luminance) {
    float saturationf = saturation / 100.0f;
    float luminancef = luminance / 100.0f;

    float c = (1 - fabsf(2 * luminancef - 1)) * saturationf;
    float x = c * (1 - fabsf((float)fmod(hue / 60.0f, 2) - 1));
    float m = luminancef - c / 2.0f;

    static char hex_string[7];

    if (hue < 60) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (c + m)),
                                             (int)round(255 * (x + m)),
                                             (int)round(255 * (m)));
    }
    else if (hue < 120) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (x + m)),
                                             (int)round(255 * (c + m)),
                                             (int)round(255 * (m)));
    }
    else if (hue < 180) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (m)),
                                             (int)round(255 * (c + m)),
                                             (int)round(255 * (x + m)));
    }
    else if (hue < 240) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (m)),
                                             (int)round(255 * (x + m)),
                                             (int)round(255 * (c + m)));
    }
    else if (hue < 300) {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (x + m)),
                                             (int)round(255 * (m)),
                                             (int)round(255 * (c + m)));
    }
    else {
        sprintf(hex_string, "#%02x%02x%02x", (int)round(255 * (c + m)),
                                             (int)round(255 * (m)),
                                             (int)round(255 * (x + m)));
    }

    return hex_string;
}

struct ColourCMYK hsl_to_cmyk(int hue, int saturation, int luminance) {
    float saturationf = saturation / 100.0f;
    float luminancef = luminance / 100.0f;

    float c = (1 - fabsf(2 * luminancef - 1)) * saturationf;
    float x = c * (1 - fabsf((float)fmod(hue / 60.0f, 2) - 1));
    float m = luminancef - c / 2.0f;

    float red, green, blue;

    if (hue < 60) {
        red = c + m;
        green = x + m;
        blue = m;
    }
    else if (hue < 120) {
        red = x + m;
        green = c + m;
        blue = m;
    }
    else if (hue < 180) {
        red = m;
        green = c + m;
        blue = x + m;
    }
    else if (hue < 240) {
        red = m;
        green = x + m;
        blue = c + m;
    }
    else if (hue < 300) {
        red = x + m;
        green = m;
        blue = c + m;
    }
    else {
        red = c + m;
        green = m;
        blue = x + m;
    }

    float maximum;
    if (red > green) {
        maximum = red;
    }
    else {
        maximum = green;
    }

    if (blue > maximum) {
        maximum = blue;
    }

    float k = 1 - maximum;
    float k_inverse = 1 - k;

    struct ColourCMYK return_value = {(int)round(100 * (k_inverse - red) / k_inverse),
                                      (int)round(100 * (k_inverse - green) / k_inverse),
                                      (int)round(100 * (k_inverse - blue) / k_inverse),
                                      (int)round(100 * k)};

    return return_value;
}

struct ColourHSV hsl_to_hsv(int hue, int saturation, int luminance)  {
    float saturationf = saturation / 100.0f;
    float luminancef = luminance / 100.0f;

    float minimum;
    if (luminancef < 1 - luminancef) {
        minimum = luminancef;
    }
    else {
        minimum = 1 - luminancef;
    }

    float v = luminancef + saturationf * minimum;

    if (v == 0) {
        saturationf = 0;
    }
    else {
        saturationf = 2 - (2 * luminancef / v);
    }

    struct ColourHSV return_value = {hue,
                                     (int)round(100 * saturationf),
                                     (int)round(100 * v)};

    return return_value;
}

// RGB to other format
static PyObject* Colours_rgb_to_hex(PyObject *self, PyObject *args) {
    int red, green, blue;

    if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) {
        PyObject *red_object, *green_object, *blue_object;
        if (PyArg_ParseTuple(args, "OOO", &red_object, &green_object, &blue_object)) {
            if (!PyLong_Check(red_object)) {
                raiseGraphicsError(rgb_to_hex_red_incorrect)
            }
            if (!PyLong_Check(green_object)) {
                raiseGraphicsError(rgb_to_hex_green_incorrect)
            }
            if (!PyLong_Check(blue_object)) {
                raiseGraphicsError(rgb_to_hex_blue_incorrect)
            }
        }
        raiseGraphicsError(rgb_to_hex_error)
    }

    if (red < 0 || red > 255) {
        raiseGraphicsError(rgb_to_hex_red_outside_range)
    }
    if (green < 0 || green > 255) {
        raiseGraphicsError(rgb_to_hex_green_outside_range)
    }
    if (blue < 0 || blue > 255) {
        raiseGraphicsError(rgb_to_hex_blue_outside_range)
    }

    return Py_BuildValue("s", rgb_to_hex(red, green, blue));
}

static PyObject* Colours_rgb_to_cmyk(PyObject *self, PyObject *args) {
    int red, green, blue;

    if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) {
        PyObject *red_object, *green_object, *blue_object;
        if (PyArg_ParseTuple(args, "OOO", &red_object, &green_object, &blue_object)) {
            if (!PyLong_Check(red_object)) {
                raiseGraphicsError(rgb_to_cmyk_red_incorrect)
            }
            if (!PyLong_Check(green_object)) {
                raiseGraphicsError(rgb_to_cmyk_green_incorrect)
            }
            if (!PyLong_Check(blue_object)) {
                raiseGraphicsError(rgb_to_cmyk_blue_incorrect)
            }
        }
        raiseGraphicsError(rgb_to_cmyk_error)
    }

    if (red < 0 || red > 255) {
        raiseGraphicsError(rgb_to_cmyk_red_outside_range)
    }
    if (green < 0 || green > 255) {
        raiseGraphicsError(rgb_to_cmyk_green_outside_range)
    }
    if (blue < 0 || blue > 255) {
        raiseGraphicsError(rgb_to_cmyk_blue_outside_range)
    }

    struct ColourCMYK colour_cmyk = rgb_to_cmyk(red, green, blue);

    return Py_BuildValue("(i, i, i, i)", colour_cmyk.cyan, colour_cmyk.magenta, colour_cmyk.yellow, colour_cmyk.key);
}

static PyObject* Colours_rgb_to_hsv(PyObject *self, PyObject *args) {
    int red, green, blue;

    if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) {
        PyObject *red_object, *green_object, *blue_object;
        if (PyArg_ParseTuple(args, "OOO", &red_object, &green_object, &blue_object)) {
            if (!PyLong_Check(red_object)) {
                raiseGraphicsError(rgb_to_hsv_red_incorrect)
            }
            if (!PyLong_Check(green_object)) {
                raiseGraphicsError(rgb_to_hsv_green_incorrect)
            }
            if (!PyLong_Check(blue_object)) {
                raiseGraphicsError(rgb_to_hsv_blue_incorrect)
            }
        }
        raiseGraphicsError(rgb_to_hsv_error)
    }
        
    if (red < 0 || red > 255) {
        raiseGraphicsError(rgb_to_hsv_red_outside_range)
    }
    if (green < 0 || green > 255) {
        raiseGraphicsError(rgb_to_hsv_green_outside_range)
    }
    if (blue < 0 || blue > 255) {
        raiseGraphicsError(rgb_to_hsv_blue_outside_range)
    }

    struct ColourHSV colour_hsv = rgb_to_hsv(red, green, blue);

    return Py_BuildValue("(i, i, i)", colour_hsv.hue, colour_hsv.saturation, colour_hsv.value);
}

static PyObject* Colours_rgb_to_hsl(PyObject *self, PyObject *args) {
    int red, green, blue;

    if (!PyArg_ParseTuple(args, "iii", &red, &green, &blue)) {
        PyObject *red_object, *green_object, *blue_object;
        if (PyArg_ParseTuple(args, "OOO", &red_object, &green_object, &blue_object)) {
            if (!PyLong_Check(red_object)) {
                raiseGraphicsError(rgb_to_hsl_red_incorrect)
            }
            if (!PyLong_Check(green_object)) {
                raiseGraphicsError(rgb_to_hsl_green_incorrect)
            }
            if (!PyLong_Check(blue_object)) {
                raiseGraphicsError(rgb_to_hsl_blue_incorrect)
            }
        }
        raiseGraphicsError(rgb_to_hsl_error)
    }
    
    if (red < 0 || red > 255) {
        raiseGraphicsError(rgb_to_hsl_red_outside_range)
    }
    if (green < 0 || green > 255) {
        raiseGraphicsError(rgb_to_hsl_green_outside_range)
    }
    if (blue < 0 || blue > 255) {
        raiseGraphicsError(rgb_to_hsl_blue_outside_range)
    }

    struct ColourHSL colour_hsl = rgb_to_hsl(red, green, blue);

    return Py_BuildValue("(i, i, i)", colour_hsl.hue, colour_hsl.saturation, colour_hsl.luminance);
}

// Hex to other format
static PyObject* Colours_hex_to_rgb(PyObject *self, PyObject *args) {
    PyObject *hexobject;

    if (!PyArg_ParseTuple(args, "O", &hexobject)) {
        raiseGraphicsError(hex_to_rgb_error)
    }
    char *hexstring = PyBytes_AS_STRING(PyUnicode_AsEncodedString(PyObject_Str(hexobject), "utf-8", ""));

    struct ColourRGB colour_rgb = hex_to_rgb(hexstring);

    return Py_BuildValue("(i, i, i)", colour_rgb.red, colour_rgb.green, colour_rgb.blue);
}

static PyObject* Colours_hex_to_cmyk(PyObject *self, PyObject *args) {
    PyObject *hexobject;

    if (!PyArg_ParseTuple(args, "O", &hexobject)) {
        raiseGraphicsError(hex_to_cmyk_error)
    }
    char *hexstring = PyBytes_AS_STRING(PyUnicode_AsEncodedString(PyObject_Str(hexobject), "utf-8", ""));

    struct ColourCMYK colour_cmyk = hex_to_cmyk(hexstring);

    return Py_BuildValue("(i, i, i, i)", colour_cmyk.cyan, colour_cmyk.magenta, colour_cmyk.yellow, colour_cmyk.key);
}

static PyObject* Colours_hex_to_hsl(PyObject *self, PyObject *args) {
    PyObject *hexobject;

    if (!PyArg_ParseTuple(args, "O", &hexobject)) {
        raiseGraphicsError(hex_to_hsl_error)
    }
    char *hexstring = PyBytes_AS_STRING(PyUnicode_AsEncodedString(PyObject_Str(hexobject), "utf-8", ""));

    struct ColourHSL colour_hsl = hex_to_hsl(hexstring);

    return Py_BuildValue("(i, i, i)", colour_hsl.hue, colour_hsl.saturation, colour_hsl.luminance);
}

static PyObject* Colours_hex_to_hsv(PyObject *self, PyObject *args) {
    PyObject *hexobject;

    if (!PyArg_ParseTuple(args, "O", &hexobject)) {
        raiseGraphicsError(hex_to_hsv_error)
    }
    char *hexstring = PyBytes_AS_STRING(PyUnicode_AsEncodedString(PyObject_Str(hexobject), "utf-8", ""));

    struct ColourHSV colour_hsv = hex_to_hsv(hexstring);

    return Py_BuildValue("(i, i, i)", colour_hsv.hue, colour_hsv.saturation, colour_hsv.value);
}

static PyObject* Colours_hex_digit_to_int(PyObject *self, PyObject *args){
    char letter;

    if (!PyArg_ParseTuple(args, "C", &letter)) {
        return NULL;
    }

    int value = hex_digit_to_int(letter);
    if (value == -1) {
        raiseGraphicsError(hex_digit_to_int_incorrect_input)
    }
    return Py_BuildValue("i", value);
}

// CMYK to other format
static PyObject* Colours_cmyk_to_rgb(PyObject *self, PyObject *args) {
    int cyan, magenta, yellow, key;

    if (!PyArg_ParseTuple(args, "iiii", &cyan, &magenta, &yellow, &key)) {
        raiseGraphicsError(cmyk_to_rgb_error)
    }
    
    if (cyan < 0 || cyan > 100) {
        raiseGraphicsError(cmyk_to_rgb_cyan_outside_range)
    }
    if (magenta < 0 || magenta > 100) {
        raiseGraphicsError(cmyk_to_rgb_magenta_outside_range)
    }
    if (yellow < 0 || yellow > 100) {
        raiseGraphicsError(cmyk_to_rgb_yellow_outside_range)
    }
    if (key < 0 || key > 100) {
        raiseGraphicsError(cmyk_to_rgb_key_outside_range)
    }

    struct ColourRGB colour_rgb = cmyk_to_rgb(cyan, magenta, yellow, key);

    return Py_BuildValue("(i, i, i)", colour_rgb.red, colour_rgb.green, colour_rgb.blue);
}

static PyObject* Colours_cmyk_to_hex(PyObject *self, PyObject *args) {
    int cyan, magenta, yellow, key;

    if (!PyArg_ParseTuple(args, "iiii", &cyan, &magenta, &yellow, &key)) {
        raiseGraphicsError(cmyk_to_hex_error)
    }
    
    if (cyan < 0 || cyan > 100) {
        raiseGraphicsError(cmyk_to_hex_cyan_outside_range)
    }
    if (magenta < 0 || magenta > 100) {
        raiseGraphicsError(cmyk_to_hex_magenta_outside_range)
    }
    if (yellow < 0 || yellow > 100) {
        raiseGraphicsError(cmyk_to_hex_yellow_outside_range)
    }
    if (key < 0 || key > 100) {
        raiseGraphicsError(cmyk_to_hex_key_outside_range)
    }

    return Py_BuildValue("s", cmyk_to_hex(cyan, magenta, yellow, key));
}

static PyObject* Colours_cmyk_to_hsv(PyObject *self, PyObject *args) {
    int cyan, magenta, yellow, key;

    if (!PyArg_ParseTuple(args, "iiii", &cyan, &magenta, &yellow, &key)) {
        raiseGraphicsError(cmyk_to_hsv_error)
    }
    
    if (cyan < 0 || cyan > 100) {
        raiseGraphicsError(cmyk_to_hsv_cyan_outside_range)
    }
    if (magenta < 0 || magenta > 100) {
        raiseGraphicsError(cmyk_to_hsv_magenta_outside_range)
    }
    if (yellow < 0 || yellow > 100) {
        raiseGraphicsError(cmyk_to_hsv_yellow_outside_range)
    }
    if (key < 0 || key > 100) {
        raiseGraphicsError(cmyk_to_hsv_key_outside_range)
    }

    struct ColourHSV colour_hsv = cmyk_to_hsv(cyan, magenta, yellow, key);

    return Py_BuildValue("(i, i, i)", colour_hsv.hue, colour_hsv.saturation, colour_hsv.value);
}

static PyObject* Colours_cmyk_to_hsl(PyObject *self, PyObject *args) {
    int cyan, magenta, yellow, key;

    if (!PyArg_ParseTuple(args, "iiii", &cyan, &magenta, &yellow, &key)) {
        raiseGraphicsError(cmyk_to_hsl_error)
    }
    
    if (cyan < 0 || cyan > 100) {
        raiseGraphicsError(cmyk_to_hsl_cyan_outside_range)
    }
    if (magenta < 0 || magenta > 100) {
        raiseGraphicsError(cmyk_to_hsl_magenta_outside_range)
    }
    if (yellow < 0 || yellow > 100) {
        raiseGraphicsError(cmyk_to_hsl_yellow_outside_range)
    }
    if (key < 0 || key > 100) {
        raiseGraphicsError(cmyk_to_hsl_key_outside_range)
    }

    struct ColourHSL colour_hsl = cmyk_to_hsl(cyan, magenta, yellow, key);

    return Py_BuildValue("(i, i, i)", colour_hsl.hue, colour_hsl.saturation, colour_hsl.luminance);
}

// HSV to other format
static PyObject* Colours_hsv_to_rgb(PyObject *self, PyObject *args) {
    int hue, saturation, value;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &value)) {
        raiseGraphicsError(hsv_to_rgb_error)
    }

    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsv_to_rgb_saturation_outside_range)
    }
    if (value < 0 || value > 100) {
        raiseGraphicsError(hsv_to_rgb_value_outside_range)
    }

    struct ColourRGB colour_rgb = hsv_to_rgb(hue, saturation, value);

    return Py_BuildValue("(i, i, i)", colour_rgb.red, colour_rgb.green, colour_rgb.blue);
}

static PyObject* Colours_hsv_to_hex(PyObject *self, PyObject *args) {
    int hue, saturation, value;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &value)) {
        raiseGraphicsError(hsv_to_hex_error)
    }
        
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsv_to_hex_saturation_outside_range)
    }
    if (value < 0 || value > 100) {
        raiseGraphicsError(hsv_to_hex_value_outside_range)
    }

    return Py_BuildValue("s", hsv_to_hex(hue, saturation, value));
}

static PyObject* Colours_hsv_to_cmyk(PyObject *self, PyObject *args) {
    int hue, saturation, value;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &value)) {
        raiseGraphicsError(hsv_to_cmyk_error)
    }
        
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsv_to_cmyk_saturation_outside_range)
    }
    if (value < 0 || value > 100) {
        raiseGraphicsError(hsv_to_cmyk_value_outside_range)
    }

    struct ColourCMYK colour_cmyk = hsv_to_cmyk(hue, saturation, value);

    return Py_BuildValue("(i, i, i, i)", colour_cmyk.cyan, colour_cmyk.magenta, colour_cmyk.yellow, colour_cmyk.key);
}

static PyObject* Colours_hsv_to_hsl(PyObject *self, PyObject *args) {
    int hue, saturation, value;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &value)) {
        raiseGraphicsError(hsv_to_hsl_error)
    }
    
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsv_to_hsl_saturation_outside_range)
    }
    if (value < 0 || value > 100) {
        raiseGraphicsError(hsv_to_hsl_value_outside_range)
    }

    struct ColourHSL colour_hsl = hsv_to_hsl(hue, saturation, value);

    return Py_BuildValue("(i, i, i)", colour_hsl.hue, colour_hsl.saturation, colour_hsl.luminance);
}

// HSL to other format
static PyObject* Colours_hsl_to_rgb(PyObject *self, PyObject *args) {
    int hue, saturation, luminance;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &luminance)) {
        raiseGraphicsError(hsl_to_rgb_error)
    }
     
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsl_to_rgb_saturation_outside_range)
    }
    if (luminance < 0 || luminance > 100) {
        raiseGraphicsError(hsl_to_rgb_luminance_outside_range)
    }

    struct ColourRGB colour_rgb = hsl_to_rgb(hue, saturation, luminance);

    return Py_BuildValue("(i, i, i)", colour_rgb.red, colour_rgb.green, colour_rgb.blue);
}

static PyObject* Colours_hsl_to_hex(PyObject *self, PyObject *args) {
    int hue, saturation, luminance;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &luminance)) {
        raiseGraphicsError(hsl_to_hex_error)
    }
        
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsl_to_hex_saturation_outside_range)
    }
    if (luminance < 0 || luminance > 100) {
        raiseGraphicsError(hsl_to_hex_luminance_outside_range)
    }

    return Py_BuildValue("s", hsl_to_hex(hue, saturation, luminance));
}

static PyObject* Colours_hsl_to_cmyk(PyObject *self, PyObject *args) {
    int hue, saturation, luminance;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &luminance)) {
        raiseGraphicsError(hsl_to_cmyk_error)
    }
        
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsl_to_cmyk_saturation_outside_range)
    }
    if (luminance < 0 || luminance > 100) {
        raiseGraphicsError(hsl_to_cmyk_luminance_outside_range)
    }

    struct ColourCMYK colour_cmyk = hsl_to_cmyk(hue, saturation, luminance);

    return Py_BuildValue("(i, i, i, i)", colour_cmyk.cyan, colour_cmyk.magenta, colour_cmyk.yellow, colour_cmyk.key);
}

static PyObject* Colours_hsl_to_hsv(PyObject *self, PyObject *args) {
    int hue, saturation, luminance;

    if (!PyArg_ParseTuple(args, "iii", &hue, &saturation, &luminance)) {
        raiseGraphicsError(hsl_to_hsv_error)
    }
    
    if (hue < 0 || hue > 360) {
        hue = hue % 360;
    }
    if (saturation < 0 || saturation > 100) {
        raiseGraphicsError(hsl_to_hsv_saturation_outside_range)
    }
    if (luminance < 0 || luminance > 100) {
        raiseGraphicsError(hsl_to_hsv_luminance_outside_range)
    }

    struct ColourHSV colour_hsv = hsl_to_hsv(hue, saturation, luminance);

    return Py_BuildValue("(i, i, i)", colour_hsv.hue, colour_hsv.saturation, colour_hsv.value);
}

/*
------------------------------------------------------------------------------------------------------------------------
COLOUR CLASSES

*/

/* This structure defines what all attributes a Colour class contains */
typedef struct {
    PyObject_HEAD
    int red, green, blue;  /* RGB values for the colour */
    PyObject *colour;  /* A Hexadecimal value for the colour string */
    PyObject *string;
} Colour;

/* This is a function which deallocates memory for a Colour object*/
static void Colour_dealloc(Colour * self) {
    Py_XDECREF(self->string);
    Py_XDECREF(self->colour);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

/* The _new function creates a new instance of the Colour class*/
static PyObject* Colour_new(PyTypeObject *type, PyObject *args, PyObject*kwds) {
    Colour *self;
    self = (Colour *) type->tp_alloc(type, 0); /* allocates memory for the object */

    if (self != NULL) { /* This ensures that there was no error allocating memory */
        self->string = PyUnicode_FromString("");
        if (self->string == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->red = 0;
        self->green = 0; /* Puts 0 as the default value for each RGB value */
        self->blue = 0;
    }
    return (PyObject *) self;
}

static int Colour_init(Colour *self, PyObject *args, PyObject *kwds) {
    return 0;
}

static PyMemberDef Colour_members[] = {
    {"red", T_INT, offsetof(Colour, red), 0,
     "RGB red value of Colour"},

    {"green", T_INT, offsetof(Colour, green), 0,
     "RGB green value of Colour"},

    {"blue", T_INT, offsetof(Colour, blue), 0,
     "RGB blue value of Colour"},

    {"colour", T_OBJECT_EX, offsetof(Colour, colour), 0,
     "Hexadecimal colour value of Colour"},

     {"string", T_OBJECT_EX, offsetof(Colour, string), 0,
     "Reprent string value of Colour"},

    {NULL}
};

static PyObject *Colour_rgb_string(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromFormat("rgb %i, %i, %i", self->red, self->green, self->blue);
}

static PyObject *Colour_hex_string(Colour *self, PyObject *Py_UNUSED(ignored)) {
    return self->colour;
}

static Colour *Colour_update_values(Colour *self) {
    self->string = PyUnicode_FromFormat("rgb %c, %c, %c", self->red, self->green, self->blue);
    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);
    return self;
}

static PyMethodDef Colour_methods[] = {
    {"rgb_string", (PyCFunction) Colour_rgb_string, METH_NOARGS,
     "Return the rgb value of the colour"},

     {"hex_string", (PyCFunction) Colour_hex_string, METH_NOARGS,
     "Return the hex value of the colour"},

    {NULL}  /* Sentinel */
};

static PyObject *Colour_repr(Colour *self) {
    Py_INCREF(self->string);
    return self->string;
}

static PyObject *Colour_str(Colour *self) {
    Py_INCREF(self->colour);
    return self->colour;
}

static PyObject *Colour_iter(Colour *self) {

}

static PyTypeObject ColourType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.Colour",
    .tp_doc = "The superclass of all goopylib colour classes",
    .tp_basicsize = sizeof(Colour),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = (newfunc) Colour_new,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) Colour_init,

    .tp_members = Colour_members,
    .tp_methods = Colour_methods,

    .tp_repr = (reprfunc) Colour_repr,
    .tp_str = (reprfunc) Colour_str,
};

#include "colours_Colour_NumberMethods.h"

/* ColourRGB class*/

typedef struct {
    Colour superclass;
    int red, green, blue;  /* RGB values for the colour */
    PyObject *colour;  /* A Hexadecimal value for the colour string */
    PyObject *string;
} ColourRGB;

static int ColourRGB_init(Colour *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"red", "green", "blue", NULL};

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    int red = 0, green = 0, blue = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &red, &green, &blue))
        return -1;

    self->string = PyUnicode_FromFormat("rgb %c, %c, %c", red, green, blue);

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourRGBType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourRGB",
    .tp_doc = "An object to represent goopylib colours using RGB values",
    .tp_basicsize = sizeof(ColourRGB),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourRGB_init,
    .tp_members = Colour_members,
};

/* ColourCMYK class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourCMYK;

static int ColourCMYK_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"c", "m", "y", "k", NULL};

    int c = 0, m = 0, y = 0, k = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist, &c, &m, &y, &k))
        return -1;

    int red = 255 * (1 - (c + k) / 100);
    int green = 255 * (1 - (m + k) / 100);
    int blue = 255 * (1 - (y + k) / 100);

    self->string = PyUnicode_FromFormat("cmyk %c%%, %c%%, %c%%", c, m, y, k);

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourCMYKType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourCMYK",
    .tp_doc = "An object to represent goopylib colours using CMYK values",
    .tp_basicsize = sizeof(ColourCMYK),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourCMYK_init,
    .tp_members = Colour_members,
};

/* ColourHex class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourHex;

static int ColourHex_init(Colour *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"colour", NULL};

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    PyObject* colour_obj;
    char colour[8];

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|U", kwlist, &colour_obj))
        return -1;

    strncpy(colour, PyBytes_AS_STRING(PyUnicode_AsEncodedString(PyObject_Repr(colour_obj), "utf-8", "~E~")) + 1, 7);
    colour[7] = '\0';

    self->red = (16 * hex_digit_to_int(colour[1])) + hex_digit_to_int(colour[2]);
    self->green = (16 * hex_digit_to_int(colour[3])) + hex_digit_to_int(colour[4]);
    self->blue = (16 * hex_digit_to_int(colour[5])) + hex_digit_to_int(colour[6]);

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);
    self->string = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourHexType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourHex",
    .tp_doc = "An object to represent goopylib colours using Hexadecimal values",
    .tp_basicsize = sizeof(ColourHex),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourHex_init,
    .tp_members = Colour_members,
};

/* ColourHSL class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourHSL;

static int ColourHSL_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"h", "s", "l", NULL};

    int h = 0, s = 0, l_input = 0;
    float l = 0.0f;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &h, &s, &l_input))
        return -1;

    l = l_input / 100.0f;

    /* Conversion from HSL to RGB */

    float c = (1 - fabsf(2*l - 1)) * (s/100.0f);
    float x = c * (1 - fabsf((float)fmod(h / 60.0f, 2) - 1));
    float m = l - c/2;

    int red = 0, green = 0, blue = 0;

    if (h < 60) {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * m);
    }
    else if (h < 120) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * m);
    }
    else if (h < 180) {
        red = (int)round(255 * m);
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * (x + m));
    }
    else if (h < 240) {
        red = (int)round(255 * m);
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * (c + m));
    }
    else if (h < 300) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (c + m));
    }
    else {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (x + m));
    }

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourHSLType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourHSL",
    .tp_doc = "An object to represent goopylib colours using HSL values",
    .tp_basicsize = sizeof(ColourHSL),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourHSL_init,
    .tp_members = Colour_members,
};

/* ColourHSV class*/

typedef struct {
    Colour superclass;
    int red, green, blue;
    PyObject *colour;
    PyObject *string;
} ColourHSV;

static int ColourHSV_init(Colour *self, PyObject *args, PyObject *kwds) {

    if (ColourType.tp_init((PyObject *) self, args, kwds) < 0)
        return -1;

    static char *kwlist[] = {"h", "s", "v", NULL};

    int h = 0, s = 0, v_input = 0;
    float v = 0.0f;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &h, &s, &v_input))
        return -1;

    /* Conversion from HSV to RGB */

    v = v_input / 100.0f;

    float c = v * (s / 100.0f);
    float x = c * (1 - fabsf((float)fmod(h / 60.0f, 2) - 1));
    float m = v - c;

    int red = 0, green = 0, blue = 0;

    if (h < 60) {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * m);
    }
    else if (h < 120) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * m);
    }
    else if (h < 180) {
        red = (int)round(255 * m);
        green = (int)round(255 * (c + m));
        blue = (int)round(255 * (x + m));
    }
    else if (h < 240) {
        red = (int)round(255 * m);
        green = (int)round(255 * (x + m));
        blue = (int)round(255 * (c + m));
    }
    else if (h < 300) {
        red = (int)round(255 * (x + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (c + m));
    }
    else {
        red = (int)round(255 * (c + m));
        green = (int)round(255 * m);
        blue = (int)round(255 * (x + m));
    }

    self->red = red;
    self->green = green;
    self->blue = blue;

    self->colour = PyUnicode_FromFormat("#%02x%02x%02x", self->red, self->green, self->blue);

    return 0;
}

static PyTypeObject ColourHSVType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "goopylib.ColourHSV",
    .tp_doc = "An object to represent goopylib colours using HSV values",
    .tp_basicsize = sizeof(ColourHSV),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = (destructor) Colour_dealloc,
    .tp_init = (initproc) ColourHSV_init,
    .tp_members = Colour_members,
};

/* CPython API & Module Related Functions */

static PyMethodDef c_colours_funcs[] = {

    // RGB to other format functions
    {"rgb_to_hex", (PyCFunction)Colours_rgb_to_hex, METH_VARARGS,
    "rgb_to_hex(int r, int g, int b) -> string '#rrggbb'\nConverts RGB values to a hex string"},

    {"rgb_to_cmyk", (PyCFunction)Colours_rgb_to_cmyk, METH_VARARGS,
    "rgb_to_cmyk(int r, int g, int b) -> tuple (int c, int m, int y, int k)\nConverts RGB values to CMYK represented "
    "as a PyTuple"},

    {"rgb_to_hsl", (PyCFunction)Colours_rgb_to_hsl, METH_VARARGS,
    "rgb_to_hsl(int r, int g, int b) -> tuple (int h, int s, int l)\nConverts RGB values to HSL represented as a "
    "PyTuple"},

    {"rgb_to_hsv", (PyCFunction)Colours_rgb_to_hsv, METH_VARARGS,
    "rgb_to_hsv(int r, int g, int b) -> tuple (int h, int s, int v)\nConverts RGB values to HSV represented as a "
    "PyTuple"},

    // Hex to other format functions
    {"hex_to_rgb", (PyCFunction)Colours_hex_to_rgb, METH_VARARGS,
    "hex_to_rgb(string hexstring) -> tuple (int r, int g, int b)\nConverts Hex colour values to RGB represented as a "
    "PyTuple"},
    
    {"hex_to_cmyk", (PyCFunction)Colours_hex_to_cmyk, METH_VARARGS,
    "hex_to_cmyk(string hexstring) -> tuple (int c, int m, int y, int k)\nConverts Hex colour values to CMYK "
    "represented as a PyTuple"},
    

    {"hex_to_hsl", (PyCFunction)Colours_hex_to_hsl, METH_VARARGS,
    "hex_to_hsl(string hexstring) -> tuple (int h, int s, int l)\nConverts Hex colour values to HSL represented as a "
    "PyTuple"},
    
    {"hex_to_hsv", (PyCFunction)Colours_hex_to_hsv, METH_VARARGS,
    "hex_to_hsv(string hexstring) -> tuple (int h, int s, int v)\nConverts Hex colour values to HSV represented as a "
    "PyTuple"},

    {"hex_digit_to_int", (PyCFunction)Colours_hex_digit_to_int, METH_VARARGS,
    "hex_digit_to_int(char digit) -> int\nConverts a hexadecimal digit to an integer"},
    
    // CMYK to other format functions
    {"cmyk_to_rgb", (PyCFunction)Colours_cmyk_to_rgb, METH_VARARGS,
    "cmyk_to_rgb(int c, int m, int y, int k) -> tuple (int r, int g, int b)\nConverts CMYK values to RGB represented "
    "as a PyTuple"},
    
    {"cmyk_to_hex", (PyCFunction)Colours_cmyk_to_hex, METH_VARARGS,
    "cmyk_to_hex(int c, int m, int y, int k) -> string '#rrggbb'\nConverts CMYK values to a hex string"},

    {"cmyk_to_hsl", (PyCFunction)Colours_cmyk_to_hsl, METH_VARARGS,
    "cmyk_to_hsl(int c, int m, int y, int k) -> tuple (int h, int s, int l)\nConverts CMYK values to HSL represented "
    "as a PyTuple"},
    
    {"cmyk_to_hsv", (PyCFunction)Colours_cmyk_to_hsv, METH_VARARGS,
    "cmyk_to_hsv(int c, int m, int y, int k) -> tuple (int h, int s, int v)\nConverts CMYK values to HSV represented "
    "as a PyTuple"},
    
    // HSV to other format functions
    {"hsv_to_rgb", (PyCFunction)Colours_hsv_to_rgb, METH_VARARGS,
    "hsv_to_rgb(int h, int s, int v) -> tuple (int r, int g, int b)\nConverts HSV values to RGB represented "
    "as a PyTuple"},
    
    {"hsv_to_hex", (PyCFunction)Colours_hsv_to_hex, METH_VARARGS,
    "hsv_to_hex(int h, int s, int v) -> string '#rrggbb'\nConverts HSV values to a hex string"},
    
    {"hsv_to_cmyk", (PyCFunction)Colours_hsv_to_cmyk, METH_VARARGS,
    "hsv_to_cmyk(int h, int s, int v) -> tuple (int c, int m, int y, int k)\nConverts HSV values to CMYK represented "
    "as a PyTuple"},
    
    {"hsv_to_hsl", (PyCFunction)Colours_hsv_to_hsl, METH_VARARGS,
    "hsv_to_hsl(int h, int s, int v) -> tuple (int h, int s, int l)\nConverts HSV values to HSL represented "
    "as a PyTuple"},
    
    // HSL to other format functions
    {"hsl_to_rgb", (PyCFunction)Colours_hsl_to_rgb, METH_VARARGS,
    "hsl_to_rgb(int h, int s, int l) -> tuple (int r, int g, int b)\nConverts HSL values to RGB represented "
    "as a PyTuple"},
    
    {"hsl_to_hex", (PyCFunction)Colours_hsl_to_hex, METH_VARARGS,
    "hsl_to_hex(int h, int s, int l) -> string '#rrggbb'\nConverts HSL values to a hex string"},
    
    {"hsl_to_cmyk", (PyCFunction)Colours_hsl_to_cmyk, METH_VARARGS,
    "hsl_to_cmyk(int h, int s, int l) -> tuple (int c, int m, int y, int k)\nConverts HSL values to CMYK represented "
    "as a PyTuple"},
    
    {"hsl_to_hsv", (PyCFunction)Colours_hsl_to_hsv, METH_VARARGS,
    "hsl_to_hsv(int h, int s, int l) -> tuple (int h, int s, int v)\nConverts HSL values to HSV represented "
    "as a PyTuple"},

    {NULL, NULL, 0, NULL}};

static PyModuleDef c_colours_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "c_colours_module",
    .m_doc = "C implementation of a module to work with colours!",
    .m_size = -1, c_colours_funcs};


PyMODINIT_FUNC PyInit_c_colours(void){

    PyObject *m;

    ColourType.tp_as_number = &Colour_number_methods;
    ColourType.tp_as_sequence = &Colour_sequence_methods;
    ColourType.tp_richcompare = (richcmpfunc)&Colour_richcompare;

    ColourRGBType.tp_base = &ColourType;
    ColourHexType.tp_base = &ColourType;
    ColourCMYKType.tp_base = &ColourType;
    ColourHSLType.tp_base = &ColourType;
    ColourHSVType.tp_base = &ColourType;

    if (PyType_Ready(&ColourType) < 0)
        return NULL;
    if (PyType_Ready(&ColourRGBType) < 0)
        return NULL;
    if (PyType_Ready(&ColourCMYKType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHexType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHSLType) < 0)
        return NULL;
    if (PyType_Ready(&ColourHSVType) < 0)
        return NULL;

    m = PyModule_Create(&c_colours_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&ColourType);
    Py_INCREF(&ColourRGBType);
    Py_INCREF(&ColourCMYKType);
    Py_INCREF(&ColourHexType);
    Py_INCREF(&ColourHSLType);
    Py_INCREF(&ColourHSVType);

    if (PyModule_AddObject(m, "Colour", (PyObject *) &ColourType) < 0) {
        Py_DECREF(&ColourType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourRGB", (PyObject *) &ColourRGBType) < 0) {
        Py_DECREF(&ColourRGBType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourCMYK", (PyObject *) &ColourCMYKType) < 0) {
        Py_DECREF(&ColourCMYKType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourHex", (PyObject *) &ColourHexType) < 0) {
        Py_DECREF(&ColourHexType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourHSL", (PyObject *) &ColourHSLType) < 0) {
        Py_DECREF(&ColourHSLType);
        Py_DECREF(m);
        return NULL;}

    if (PyModule_AddObject(m, "ColourHSV", (PyObject *) &ColourHSVType) < 0) {
        Py_DECREF(&ColourHSVType);
        Py_DECREF(m);
        return NULL;}

    GraphicsError = PyErr_NewException("goopylib.colours.GraphicsError", NULL, NULL);
    Py_XINCREF(GraphicsError);

    Colour_reference = (PyObject *) &ColourType;
    ColourRGB_reference = (PyObject *) &ColourRGBType;
    ColourCMYK_reference = (PyObject *) &ColourCMYKType;
    ColourHSL_reference = (PyObject *) &ColourHSLType;
    ColourHSV_reference = (PyObject *) &ColourHSVType;

    if (PyModule_AddObject(m, "GraphicsError", GraphicsError) < 0) {
        Py_XDECREF(GraphicsError);
		Py_CLEAR(GraphicsError);
		Py_DECREF(m);
		return NULL;}

    return m;
}
