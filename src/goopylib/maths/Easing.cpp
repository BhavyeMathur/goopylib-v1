#include "Easing.h"

#if !GP_LOG_EASING
#undef GP_LOGGING_LEVEL
#endif

#include "goopylib/debug/LogMacros.h"

#if !GP_VALUE_CHECK_EASING
#undef GP_VALUE_CHECKING
#endif

#include "goopylib/debug/Error.h"

#define EASE_IN(func, ...) func(t, ##__VA_ARGS__)
#define EASE_OUT(func, ...) (1 - func(1 - t, ##__VA_ARGS__))
#define EASE_INOUT(func, ...) (t < 0.5 ? func(2 * t, ##__VA_ARGS__) / 2 : 1 - func(2 * (1 - t), ##__VA_ARGS__) / 2)

namespace {
    void processEaseBounce(int bounces, float &damping, float &scale, std::vector<float> &zeroes,
                           std::vector<float> &derivatives) {

        GP_CHECK_GE(damping, 0, "damping value for easing must be greater than or equal to 0");
        GP_CHECK_GE(bounces, 1, "bounces value for easing must be greater than or equal to 1");

        damping = -sqrt(damping);
        zeroes.push_back(1);
        derivatives.push_back(-2);

        zeroes.push_back(-2 * damping + 1);
        derivatives.push_back(2 * (zeroes[0] - zeroes[1]) + damping * derivatives[0]);

        for (int i = 2; i < bounces; i++) {
            zeroes.push_back(damping * (zeroes[i - 2] - zeroes[i - 1]) + zeroes[i - 1]);
            derivatives.push_back(2 * (zeroes[i - 1] - zeroes[i]) + damping * derivatives[i - 1]);
        }

        scale = zeroes[bounces - 1];
    }
}

namespace gp {
    std::function<float(float)> easeLinear() {
        GP_CORE_INFO("gp::easeLinear()");

        return [](float t) {
            return t;
        };
    }

    float easePoly(float t, float power) {
        GP_CORE_TRACE("gp::easePoly(t={0}, power={1})", t, power);

        return pow(t, power);
    }

    std::function<float(float)> easePolyIn(float power) {
        GP_CORE_INFO("gp::easePolyIn(power={0})", power);

        return [power](float t) {
            return EASE_IN(easePoly, power);
        };
    }

    std::function<float(float)> easePolyOut(float power) {
        GP_CORE_INFO("gp::easePolyOut(power={0})", power);

        return [power](float t) {
            return EASE_OUT(easePoly, power);
        };
    }

    std::function<float(float)> easePolyInOut(float power) {
        GP_CORE_INFO("gp::easePolyInOut(power={0})", power);

        return [power](float t) {
            return EASE_INOUT(easePoly, power);
        };
    }

    float easeQuad(float t) {
        GP_CORE_TRACE("gp::easeQuad(t={0})", t);

        return t * t;
    }

    std::function<float(float)> easeQuadIn() {
        GP_CORE_INFO("gp::easeQuadIn()");

        return [](float t) {
            return EASE_IN(easeQuad);
        };
    }

    std::function<float(float)> easeQuadOut() {
        GP_CORE_INFO("gp::easeQuadOut()");

        return [](float t) {
            return EASE_OUT(easeQuad);
        };
    }

    std::function<float(float)> easeQuadInOut() {
        GP_CORE_INFO("gp::easeQuadInOut()");

        return [](float t) {
            return EASE_INOUT(easeQuad);
        };
    }

    float easeCubic(float t) {
        GP_CORE_TRACE("gp::easeCubic(t={0})", t);

        return t * t * t;
    }

    std::function<float(float)> easeCubicIn() {
        GP_CORE_INFO("gp::easeCubicIn()");

        return [](float t) {
            return EASE_IN(easeCubic);
        };
    }

    std::function<float(float)> easeCubicOut() {
        GP_CORE_INFO("gp::easeCubicOut()");

        return [](float t) {
            return EASE_OUT(easeCubic);
        };
    }

    std::function<float(float)> easeCubicInOut() {
        GP_CORE_INFO("gp::easeCubicInOut()");

        return [](float t) {
            return EASE_INOUT(easeCubic);
        };
    }

    float easeQuart(float t) {
        GP_CORE_TRACE("gp::easeQuart(t={0})", t);

        return t * t * t * t;
    }

    std::function<float(float)> easeQuartIn() {
        GP_CORE_INFO("gp::easeQuartIn()");

        return [](float t) {
            return EASE_IN(easeQuart);
        };
    }

    std::function<float(float)> easeQuartOut() {
        GP_CORE_INFO("gp::easeQuartOut()");

        return [](float t) {
            return EASE_OUT(easeQuart);
        };
    }

    std::function<float(float)> easeQuartInOut() {
        GP_CORE_INFO("gp::easeQuartInOut()");

        return [](float t) {
            return EASE_INOUT(easeQuart);
        };
    }

    float easeQuint(float t) {
        GP_CORE_TRACE("gp::easeQuint(t={0})", t);

        return t * t * t * t * t;
    }

    std::function<float(float)> easeQuintIn() {
        GP_CORE_INFO("gp::easeQuintIn()");

        return [](float t) {
            return EASE_IN(easeQuint);
        };
    }

    std::function<float(float)> easeQuintOut() {
        GP_CORE_INFO("gp::easeQuintOut()");

        return [](float t) {
            return EASE_OUT(easeQuint);
        };
    }

    std::function<float(float)> easeQuintInOut() {
        GP_CORE_INFO("gp::easeQuintInOut()");

        return [](float t) {
            return EASE_INOUT(easeQuint);
        };
    }

    float easeCircle(float t) {
        GP_CORE_TRACE("gp::easeCircle(t={0})", t);

        return 1 - sqrt(1 - (float) pow(t, 2));
    }

    std::function<float(float)> easeCircleIn() {
        GP_CORE_INFO("gp::easeCircleIn()");

        return [](float t) {
            return EASE_IN(easeCircle);
        };
    }

    std::function<float(float)> easeCircleOut() {
        GP_CORE_INFO("gp::easeCircleOut()");

        return [](float t) {
            return EASE_OUT(easeCircle);
        };
    }

    std::function<float(float)> easeCircleInOut() {
        GP_CORE_INFO("gp::easeCircleInOut()");

        return [](float t) {
            return EASE_INOUT(easeCircle);
        };
    }

    float easeSin(float t) {
        GP_CORE_TRACE("gp::easeSin(t={0})", t);

        return 1 - (float) cos(t * 1.57079632679);
    }

    std::function<float(float)> easeSinIn() {
        GP_CORE_INFO("gp::easeSinIn()");

        return [](float t) {
            return EASE_IN(easeSin);
        };
    }

    std::function<float(float)> easeSinOut() {
        GP_CORE_INFO("gp::easeSinOut()");

        return [](float t) {
            return EASE_OUT(easeSin);
        };
    }

    std::function<float(float)> easeSinInOut() {
        GP_CORE_INFO("gp::easeSinInOut()");

        return [](float t) {
            return EASE_INOUT(easeSin);
        };
    }

    float easeExp(float t, float base) {
        GP_CORE_TRACE("gp::easeExp(t={0}, base={1})", t, base);

        return pow(base, 10 * t - 10);
    }

    std::function<float(float)> easeExpIn(float base) {
        GP_CORE_INFO("gp::easeExpIn(base={0})", base);

        return [base](float t) {
            return EASE_IN(easeExp, base);
        };
    }

    std::function<float(float)> easeExpOut(float base) {
        GP_CORE_INFO("gp::easeExpOut(base={0})", base);

        return [base](float t) {
            return EASE_OUT(easeExp, base);
        };
    }

    std::function<float(float)> easeExpInOut(float base) {
        GP_CORE_INFO("gp::easeExpInOut(base={0})", base);

        return [base](float t) {
            return EASE_INOUT(easeExp, base);
        };
    }

    float easeBack(float t, float factor) {
        GP_CORE_TRACE("gp::easeBack(t={0}, factor={1})", t, factor);

        return ((factor + 1) * t * t * t - factor * t * t);
    }

    std::function<float(float)> easeBackIn(float factor) {
        GP_CORE_INFO("gp::easeBackIn(factor={0})", factor);

        return [factor](float t) {
            return EASE_IN(easeBack, factor);
        };
    }

    std::function<float(float)> easeBackOut(float factor) {
        GP_CORE_INFO("gp::easeBackOut(factor={0})", factor);

        return [factor](float t) {
            return EASE_OUT(easeBack, factor);
        };
    }

    std::function<float(float)> easeBackInOut(float factor) {
        GP_CORE_INFO("gp::easeBackInOut(factor={0})", factor);

        return [factor](float t) {
            return EASE_INOUT(easeBack, factor);
        };
    }

    float easeElastic(float t, int factor) {
        GP_CORE_TRACE("gp::easeElastic(t={0}, factor={1})", t, factor);

        return (float) pow(2, 10 * (t - 1)) * (float) std::sin(1.5707963267 * t * (1 + 4 * factor));
    }

    std::function<float(float)> easeElasticIn(int factor) {
        GP_CORE_INFO("gp::easeElasticIn(factor={0})", factor);

        return [factor](float t) {
            return EASE_IN(easeElastic, factor);
        };
    }

    std::function<float(float)> easeElasticOut(int factor) {
        GP_CORE_INFO("gp::easeElasticOut(factor={0})", factor);

        return [factor](float t) {
            return EASE_OUT(easeElastic, factor);
        };
    }

    std::function<float(float)> easeElasticInOut(int factor) {
        GP_CORE_INFO("gp::easeElasticInOut(factor={0})", factor);

        return [factor](float t) {
            return EASE_INOUT(easeElastic, factor);
        };
    }

    float easeBounce(float t, float damping, int bounces, float scale, const std::vector<float> &zeroes,
                     const std::vector<float> &derivatives) {
        GP_CORE_TRACE("gp::easeBounce(t={0}, bounces={1}, damping={2}, scale={3})", t, bounces, damping, scale);

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
        GP_CORE_INFO("gp::easeBounceIn(bounces={0}, damping={1})", bounces, damping);

        std::vector<float> zeroes, derivatives;
        float scale;
        processEaseBounce(bounces, damping, scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_IN(easeBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> easeBounceOut(int bounces, float damping) {
        GP_CORE_INFO("gp::easeBounceOut(bounces={0}, damping={1})", bounces, damping);

        std::vector<float> zeroes, derivatives;
        float scale;
        processEaseBounce(bounces, damping, scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_OUT(easeBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> easeBounceInOut(int bounces, float damping) {
        GP_CORE_INFO("gp::easeBounceInOut(bounces={0}, damping={1})", bounces, damping);

        std::vector<float> zeroes, derivatives;
        float scale;
        processEaseBounce(bounces, damping, scale, zeroes, derivatives);

        return [damping, bounces, scale, zeroes, derivatives](float t) {
            return EASE_INOUT(easeBounce, damping, bounces, scale, zeroes, derivatives);
        };
    }

    std::function<float(float)> combineEasing(const std::function<float(float)> &func1,
                                              const std::function<float(float)> &func2) {
        GP_CORE_INFO("gp::combineEasing()");

        return [func1, func2](float t) {
            if (t < 0.5) {
                return func1(2 * t) / 2;
            }
            return (1 - func2(2 * t - 1)) / 2;
        };
    }
}
