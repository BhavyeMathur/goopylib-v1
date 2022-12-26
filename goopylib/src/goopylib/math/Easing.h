#pragma once

#include "gp.h"
#include <functional>

namespace gp {
    /**
     * @equation ease_linear(t) = t
     * @return a linear easing function
     */
    std::function<float(float)> easeLinear();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_poly(t) = t<sup>power</sup>
     */
    float easePoly(float t, float power);

    /**
     * @param power: the exponent defining the easing
     * @equation ease_poly(t) = t<sup>power</sup>
     * @return a polynomial in easing function
     */
    std::function<float(float)> easePolyIn(float power);

    /**
     * @param power: the exponent defining the easing
     * @equation ease_poly(t) = t<sup>power</sup>
     * @return a polynomial out easing function
     */
    std::function<float(float)> easePolyOut(float power);

    /**
     * @param power: the exponent defining the easing
     * @equation ease_poly(t) = t<sup>power</sup>
     * @return a polynomial in-out easing function
     */
    std::function<float(float)> easePolyInOut(float power);

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_quad(t) = t<sup>2</sup>
     */
    float easeQuad(float t);

    /**
     * @equation ease_quad(t) = t<sup>2</sup>
     * @return a quadratic in easing function
     */
    std::function<float(float)> easeQuadIn();

    /**
     * @equation ease_quad(t) = t<sup>2</sup>
     * @return a quadratic out easing function
     */
    std::function<float(float)> easeQuadOut();

    /**
     * @equation ease_quad(t) = t<sup>2</sup>
     * @return a quadratic in-out easing function
     */
    std::function<float(float)> easeQuadInOut();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_cubic(t) = t<sup>3</sup>
     */
    float easeCubic(float t);

    /**
     * @equation ease_cubic(t) = t<sup>3</sup>
     * @return a cubic in easing function
     */
    std::function<float(float)> easeCubicIn();

    /**
     * @equation ease_cubic(t) = t<sup>3</sup>
     * @return a cubic out easing function
     */
    std::function<float(float)> easeCubicOut();

    /**
     * @equation ease_cubic(t) = t<sup>3</sup>
     * @return a cubic in-out easing function
     */
    std::function<float(float)> easeCubicInOut();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_quart(t) = t<sup>4</sup>
     */
    float easeQuart(float t);

    /**
     * @equation ease_quart(t) = t<sup>4</sup>
     * @return a quartic in easing function
     */
    std::function<float(float)> easeQuartIn();

    /**
     * @equation ease_quart(t) = t<sup>4</sup>
     * @return a quartic out easing function
     */
    std::function<float(float)> easeQuartOut();

    /**
     * @equation ease_quart(t) = t<sup>4</sup>
     * @return a quartic in-out easing function
     */
    std::function<float(float)> easeQuartInOut();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_quint(t) = t<sup>5</sup>
     */
    float easeQuint(float t);

    /**
     * @equation ease_quint(t) = t<sup>5</sup>
     * @return a quintic in easing function
     */
    std::function<float(float)> easeQuintIn();

    /**
     * @equation ease_quint(t) = t<sup>5</sup>
     * @return a quintic out easing function
     */
    std::function<float(float)> easeQuintOut();

    /**
     * @equation ease_quint(t) = t<sup>5</sup>
     * @return a quintic in-out easing function
     */
    std::function<float(float)> easeQuintInOut();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_circle(t) = 1 - √(1 - t<sup>2</sup>)
     */
    float easeCircle(float t);

    /**
     * @equation ease_circle(t) = 1 - √(1 - t<sup>2</sup>)
     * @return a circle in easing function
     */
    std::function<float(float)> easeCircleIn();

    /**
     * @equation ease_circle(t) = 1 - √(1 - t<sup>2</sup>)
     * @return a circle out easing function
     */
    std::function<float(float)> easeCircleOut();

    /**
     * @equation ease_circle(t) = 1 - √(1 - t<sup>2</sup>)
     * @return a circle in-out easing function
     */
    std::function<float(float)> easeCircleInOut();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_sin(t) = 1 - cos(tπ/2)
     */
    float easeSin(float t);

    /**
     * @equation ease_sin(t) = 1 - cos(tπ/2)
     * @return a sine in easing function
     */
    std::function<float(float)> easeSinIn();

    /**
     * @equation ease_sin(t) = 1 - cos(tπ/2)
     * @return a sine out easing function
     */
    std::function<float(float)> easeSinOut();

    /**
     * @equation ease_sin(t) = 1 - cos(tπ/2)
     * @return a sine in-out easing function
     */
    std::function<float(float)> easeSinInOut();

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_exp(t) = base<sup>10(t - 1)</sup>
     */
    float easeExp(float t, float base);

    /**
     * @param base: the base of the exponential function.
     * @equation ease_exp(t) = base<sup>10(t - 1)</sup>
     * @return an exponential in easing function
     */
    std::function<float(float)> easeExpIn(float base);

    /**
     * @param base: the base of the exponential function.
     * @equation ease_exp(t) = base<sup>10(t - 1)</sup>
     * @return an exponential out easing function
     */
    std::function<float(float)> easeExpOut(float base);

    /**
     * @param base: the base of the exponential function.
     * @equation ease_exp(t) = base<sup>10(t - 1)</sup>
     * @return an exponential in-out easing function
     */
    std::function<float(float)> easeExpInOut(float base);

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_back(t) = (factor + 1) × t<sup>3</sup> - factor × t<sup>2</sup>
     */
    float easeBack(float t, float factor);

    /**
     * @param factor: the scale of the easing's stretch.
     * @equation ease_back(t) = (factor + 1) × t<sup>3</sup> - factor × t<sup>2</sup>
     * @return a back in easing function
     */
    std::function<float(float)> easeBackIn(float factor);

    /**
     * @param factor: the scale of the easing's stretch.
     * @equation ease_back(t) = (factor + 1) × t<sup>3</sup> - factor × t<sup>2</sup>
     * @return a back out easing function
     */
    std::function<float(float)> easeBackOut(float factor);

    /**
     * @param factor: the scale of the easing's stretch.
     * @equation ease_back(t) = (factor + 1) × t<sup>3</sup> - factor × t<sup>2</sup>
     * @return a back in-out easing function
     */
    std::function<float(float)> easeBackInOut(float factor);

    /**
     * @param t: the value at which to evaluate the easing function
     * @equation ease_elastic(t) = 2<sup>10(t - 1)</sup>sin(tπ/2 × (1 + 4 × factor))
     */
    float easeElastic(float t, int factor);

    /**
     * @param factor: the number of elastic oscillations.
     * @equation ease_elastic(t) = 2<sup>10(t - 1)</sup>sin(tπ/2 × (1 + 4 × factor))
     * @return an elastic in easing function
     */
    std::function<float(float)> easeElasticIn(int factor);

    /**
     * @param factor: the number of elastic oscillations.
     * @equation ease_elastic(t) = 2<sup>10(t - 1)</sup>sin(tπ/2 × (1 + 4 × factor))
     * @return an elastic out easing function
     */
    std::function<float(float)> easeElasticOut(int factor);

    /**
     * @param factor: the number of elastic oscillations.
     * @equation ease_elastic(t) = 2<sup>10(t - 1)</sup>sin(tπ/2 × (1 + 4 × factor))
     * @return an elastic in-out easing function
     */
    std::function<float(float)> easeElasticInOut(int factor);

    /**
     * @param t: the value at which to evaluate the easing function
     */
    float easeBounce(float t, float damping, int bounces, float scale, const std::vector<float> &zeroes,
                     const std::vector<float> &derivatives);

    /**
     * @param bounces: the number of bounces in the easing.
     * @param damping: the energy retained during each bounce.
     * @return a bounce in easing function
     */
    std::function<float(float)> easeBounceIn(int bounces, float damping);

    /**
     * @param bounces: the number of bounces in the easing.
     * @param damping: the energy retained during each bounce.
     * @return a bounce out easing function
     */
    std::function<float(float)> easeBounceOut(int bounces, float damping);

    /**
     * @param bounces: the number of bounces in the easing.
     * @param damping: the energy retained during each bounce.
     * @return a bounce in-out easing function
     */
    std::function<float(float)> easeBounceInOut(int bounces, float damping);

    /**
     * Combines 2 easing functions together.
     *
     * The 1st easing function is used for t values below 0.5 and the 2nd easing function is used for t values above 0.5
     *
     * @param func1: the 1st easing function for t < 0.5
     * @param func2: the 2nd easing function for t ≥ 0.5
     * @return a combined easing function
     */
    std::function<float(float)> combineEasing(const std::function<float(float)> &func1,
                                              const std::function<float(float)> &func2);
}
