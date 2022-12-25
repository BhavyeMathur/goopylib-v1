#include "gp.h"

#define EASE_IN(func, ...) func(t, ##__VA_ARGS__)
#define EASE_OUT(func, ...) 1 - func(1 - t, ##__VA_ARGS__)
#define EASE_INOUT(func, ...) t < 0.5 ? func(2 * t, ##__VA_ARGS__) / 2 : 1 - func(2 * (1 - t), ##__VA_ARGS__) / 2

namespace {
    void processEaseBounce(int bounces, float *damping, float *scale, std::vector<float> &zeroes,
                           std::vector<float> &derivatives) {
        *damping = -sqrt(*damping);
        zeroes.push_back(1);
        derivatives.push_back(-2);

        zeroes.push_back(-2 * *damping + 1);
        derivatives.push_back(2 * (zeroes[0] - zeroes[1]) + *damping * derivatives[0]);

        for (int i = 2; i < bounces; i++) {
            zeroes.push_back(*damping * (zeroes[i - 2] - zeroes[i - 1]) + zeroes[i - 1]);
            derivatives.push_back(2 * (zeroes[i - 1] - zeroes[i]) + *damping * derivatives[i - 1]);
        }

        *scale = zeroes[bounces - 1];
    }
}

namespace gp {
    std::function<float(float)> easeLinear() {
        return [](float t) {
            return t;
        };
    }

    float inline easePoly(float t, float power) {
        return pow(t, power);
    }

    std::function<float(float)> easePolyIn(float power) {
        return [power](float t) {
            return EASE_IN(easePoly, power);
        };
    }

    std::function<float(float)> easePolyOut(float power) {
        return [power](float t) {
            return EASE_OUT(easePoly, power);
        };
    }

    std::function<float(float)> easePolyInOut(float power) {
        return [power](float t) {
            return EASE_INOUT(easePoly, power);
        };
    }

    float inline easeQuad(float t) {
        return t * t;
    }

    std::function<float(float)> easeQuadIn() {
        return [](float t) {
            return EASE_IN(easeQuad);
        };
    }

    std::function<float(float)> easeQuadOut() {
        return [](float t) {
            return EASE_OUT(easeQuad);
        };
    }

    std::function<float(float)> easeQuadInOut() {
        return [](float t) {
            return EASE_INOUT(easeQuad);
        };
    }

    float inline easeCubic(float t) {
        return t * t * t;
    }

    std::function<float(float)> easeCubicIn() {
        return [](float t) {
            return EASE_IN(easeCubic);
        };
    }

    std::function<float(float)> easeCubicOut() {
        return [](float t) {
            return EASE_OUT(easeCubic);
        };
    }

    std::function<float(float)> easeCubicInOut() {
        return [](float t) {
            return EASE_INOUT(easeCubic);
        };
    }

    float inline easeQuart(float t) {
        return t * t * t * t;
    }

    std::function<float(float)> easeQuartIn() {
        return [](float t) {
            return EASE_IN(easeQuart);
        };
    }

    std::function<float(float)> easeQuartOut() {
        return [](float t) {
            return EASE_OUT(easeQuart);
        };
    }

    std::function<float(float)> easeQuartInOut() {
        return [](float t) {
            return EASE_INOUT(easeQuart);
        };
    }

    float inline easeQuint(float t) {
        return t * t * t * t * t;
    }

    std::function<float(float)> easeQuintIn() {
        return [](float t) {
            return EASE_IN(easeQuint);
        };
    }

    std::function<float(float)> easeQuintOut() {
        return [](float t) {
            return EASE_OUT(easeQuint);
        };
    }

    std::function<float(float)> easeQuintInOut() {
        return [](float t) {
            return EASE_INOUT(easeQuint);
        };
    }

    float inline easeCircle(float t) {
        return 1 - sqrt(1 - (float) pow(t, 2));
    }

    std::function<float(float)> easeCircleIn() {
        return [](float t) {
            return EASE_IN(easeCircle);
        };
    }

    std::function<float(float)> easeCircleOut() {
        return [](float t) {
            return EASE_OUT(easeCircle);
        };
    }

    std::function<float(float)> easeCircleInOut() {
        return [](float t) {
            return EASE_INOUT(easeCircle);
        };
    }

    float inline easeSin(float t) {
        return 1 - (float) cos(t * 1.57079632679);
    }

    std::function<float(float)> easeSinIn() {
        return [](float t) {
            return EASE_IN(easeSin);
        };
    }

    std::function<float(float)> easeSinOut() {
        return [](float t) {
            return EASE_OUT(easeSin);
        };
    }

    std::function<float(float)> easeSinInOut() {
        return [](float t) {
            return EASE_INOUT(easeSin);
        };
    }

    float inline easeExp(float t, float base) {
        return pow(base, 10 * t - 10);
    }

    std::function<float(float)> easeExpIn(float base) {
        return [base](float t) {
            return EASE_IN(easeExp, base);
        };
    }

    std::function<float(float)> easeExpOut(float base) {
        return [base](float t) {
            return EASE_OUT(easeExp, base);
        };
    }

    std::function<float(float)> easeExpInOut(float base) {
        return [base](float t) {
            return EASE_INOUT(easeExp, base);
        };
    }

    float inline easeBack(float t, float factor) {
        return ((factor + 1) * t * t * t - factor * t * t);
    }

    std::function<float(float)> easeBackIn(float factor) {
        return [factor](float t) {
            return EASE_IN(easeBack, factor);
        };
    }

    std::function<float(float)> easeBackOut(float factor) {
        return [factor](float t) {
            return EASE_OUT(easeBack, factor);
        };
    }

    std::function<float(float)> easeBackInOut(float factor) {
        return [factor](float t) {
            return EASE_INOUT(easeBack, factor);
        };
    }

    float inline easeElastic(float t, int factor) {
        return (float) pow(2, 10 * (t - 1)) * (float) std::sin(1.5707963267 * t * (1 + 4 * factor));
    }

    std::function<float(float)> easeElasticIn(int factor) {
        return [factor](float t) {
            return EASE_IN(easeElastic, factor);
        };
    }

    std::function<float(float)> easeElasticOut(int factor) {
        return [factor](float t) {
            return EASE_OUT(easeElastic, factor);
        };
    }

    std::function<float(float)> easeElasticInOut(int factor) {
        return [factor](float t) {
            return EASE_INOUT(easeElastic, factor);
        };
    }

    float inline easeBounce(float t, float damping, int bounces, float scale, const std::vector<float> &zeroes,
                            const std::vector<float> &derivatives) {
        t = scale * (1 - t);
        for (int i = 0; i < bounces; i++) {
            if (zeroes[i] >= t) {
                if (i == 0) {
                    return -t * t + 1;
                }
                else {
                    t -= zeroes[i - 1];
                    return -t * t + damping * t * derivatives[i - 1];
                }
            }
        }
        return 1;
    }

    std::function<float(float)> easeBounceIn(int bounces, float damping) {
        std::vector<float> zeroes, derivatives;
        float scale;
        processEaseBounce(bounces, &damping, &scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_IN(easeBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> easeBounceOut(int bounces, float damping) {
        std::vector<float> zeroes, derivatives;
        float scale;
        processEaseBounce(bounces, &damping, &scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_OUT(easeBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> easeBounceInOut(int bounces, float damping) {
        std::vector<float> zeroes, derivatives;
        float scale;
        processEaseBounce(bounces, &damping, &scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_INOUT(easeBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }
}
