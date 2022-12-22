#pragma once

#include "pch.h"
#include "ColorStructs.h"

namespace gp {
    class ColorRGB;

    class ColorHex;

    class ColorCMYK;

    class ColorHSV;

    class ColorHSL;
}


namespace gp {
    class Color {
    public:
        Color();

        Color(Color const &color);

        explicit Color(ColorHSV const &color);

        explicit Color(ColorHSL const &color);

        Color(const RGB &color, float alpha);

        ~Color() {
            GP_CORE_TRACE_ALL("Deallocating Color");
        }

        Color(int red, int green, int blue);

        Color(int red, int green, int blue, float alpha);

        virtual std::string toString() const;

        int getRed() const;

        void setRed(int red);

        int getGreen() const;

        void setGreen(int red);

        int getBlue() const;

        void setBlue(int red);

        float getRedf() const;

        float getGreenf() const;

        float getBluef() const;

        float getAlpha() const;

        void setAlpha(float alpha);

        // Operator Overloads

        Color operator+(int value) const;

        Color operator+(const Color &value) const;

        Color operator-(int value) const;

        Color operator-(const Color &value) const;

        Color &operator+=(int value);

        Color &operator+=(const Color &value);

        Color &operator-=(int value);

        Color &operator-=(const Color &value);

    protected:
        int m_Red;
        int m_Green;
        int m_Blue;
        float m_Alpha;

        void fromRGB(int red, int green, int blue, float alpha);

        void fromRGB(const RGB &color, float alpha);

        void fromColor(const Color &color);

        void update();

        void clampRGBA();

        void clampRGB();

        void clampUpperRGB();

        void clampLowerRGB();

    private:
        mutable float m_Redf;
        mutable float m_Greenf;
        mutable float m_Bluef;
    };
}

namespace gp {
    class ColorRGB final : public Color {
    public:
        explicit ColorRGB(Color const &color);

        ColorRGB(int red, int green, int blue);

        ColorRGB(int red, int green, int blue, float alpha);

        ~ColorRGB() {
            GP_CORE_TRACE_ALL("Deallocating ColorRGB");
        }

    protected:

    private:

    };
}

namespace gp {
    class ColorHex final : public Color {
    public:
        explicit ColorHex(Color const &color);

        explicit ColorHex(const char *hexstring);

        ColorHex(const char *hexstring, float alpha);

        ~ColorHex() {
            GP_CORE_TRACE_ALL("Deallocating ColorHex");
        }

        std::string toString() const override;

    protected:

    private:
        const char *m_String;
    };
}

namespace gp {
    class ColorCMYK final : public Color {
    public:
        explicit ColorCMYK(Color const &color);

        ColorCMYK(float cyan, float magenta, float yellow, float key);

        ColorCMYK(float cyan, float magenta, float yellow, float key, float alpha);

        ~ColorCMYK() {
            GP_CORE_TRACE_ALL("Deallocating ColorCMYK");
        }

        std::string toString() const override;

        float getCyan() const;

        void setCyan(float value);

        float getMagenta() const;

        void setMagenta(float value);

        float getYellow() const;

        void setYellow(float value);

        float getKey() const;

        void setKey(float value);

    protected:

    private:
        float m_Cyan;
        float m_Magenta;
        float m_Yellow;
        float m_Key;
    };
}

namespace gp {
    class ColorHSV final : public Color {
    public:
        explicit ColorHSV(Color const &color);

        explicit ColorHSV(ColorHSL const &color);

        ColorHSV(int hue, float saturation, float value);

        ColorHSV(int hue, float saturation, float value, float alpha);

        ~ColorHSV() {
            GP_CORE_TRACE_ALL("Deallocating ColorHSV");
        }

        std::string toString() const override;

        int getHue() const;

        void setHue(int value);

        float getSaturation() const;

        void setSaturation(float value);

        float getValue() const;

        void setValue(float value);

    protected:

    private:
        int m_Hue;
        float m_Saturation;
        float m_Value;
    };
}

namespace gp {
    class ColorHSL final : public Color {
    public:
        explicit ColorHSL(Color const &color);

        explicit ColorHSL(ColorHSV const &color);

        ColorHSL(int hue, float saturation, float luminance);

        ColorHSL(int hue, float saturation, float luminance, float alpha);

        ~ColorHSL() {
            GP_CORE_TRACE_ALL("Deallocating ColorHSL");
        }

        std::string toString() const override;

        int getHue() const;

        void setHue(int value);

        float getSaturation() const;

        void setSaturation(float value);

        float getLuminance() const;

        void setLuminance(float value);

    protected:

    private:
        int m_Hue;
        float m_Saturation;
        float m_Luminance;
    };
}

namespace gp {
    std::ostream &operator<<(std::ostream &os, const Color &color);
}
