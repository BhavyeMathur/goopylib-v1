import math

# Interpolation Functions

def ease_linear(t):
    return t


def ease_poly_in(t, power=2):
    return t ** power


def ease_poly_out(t, power=2):
    return 1 - (t ** power)


def ease_poly(t, power=2):
    t *= 2
    if t < 1:
        return t ** power
    else:
        return 2 - ((2 - t) ** power)


def ease_sin_in(t):
    return 1 - math.cos(t * math.pi * 0.5)


def ease_sin_out(t):
    return math.sin(t * math.pi * 0.5)


def ease_sin(t):
    return 1 - math.cos(math.pi * t) / 2


def ease_circle_in(t, factor=0.5):
    return 1 - (1 - t * t) ** factor


def ease_circle_out(t, factor=0.5):
    return 1 - ease_circle_in(1 - t, factor)


def ease_circle(t, factor_in=0.5, factor_out=0.5):
    t *= 2
    if t <= 1:
        return (1 - (1 - t * t) ** factor_in) / 2
    else:
        return ((1 - (t - 2) * (t - 2)) ** factor_out + 1) / 2


def ease_back_in(t, factor=1.70158):
    return t * t * ((factor + 1) * t - factor)


def ease_back_out(t, factor=1.70158):
    return 1 - (1 - t) ** 2 * ((factor + 1) * (1 - t) - factor)


def ease_back(t, factor_in=1.70158, factor_out=1.70158):
    t *= 2
    if t < 1:
        return (t * t * ((factor_in + 1) * t - factor_in)) / 2
    else:
        return ((t - 2) ** 2 * ((factor_out + 1) * (t - 2) + factor_out) + 2) / 2


def ease_bounce_in(t, bounces=None):
    return 1 - ease_bounce_out(1 - t, bounces)


def ease_bounce_out(t, bounces=None):
    if bounces is None:
        bounces = [4 / 11, 6 / 11, 8 / 11, 3 / 4, 9 / 11, 10 / 11, 15 / 16, 21 / 22, 63 / 64]

    bounces.insert(0, 1 / bounces[0] / bounces[0])
    if t < bounces[1]:
        return bounces[0] * t * t
    else:
        for i in range(3, len(bounces) - 2, 3):
            if t < bounces[i]:
                t -= bounces[i - 1]
                return bounces[0] * t * t + bounces[i + 1]

    t -= bounces[len(bounces) - 2]
    return bounces[0] * t * t + bounces[len(bounces) - 1]


def ease_bounce(t, bounces_in=None, bounces_out=None):
    t *= 2
    if t <= 1:
        return (1 - ease_bounce_out(1 - t, bounces_in)) / 2
    else:
        return (ease_bounce_out(t - 1, bounces_out) + 1) / 2


def ease_elastic_in(t, period=0.2, amplitude=1):
    period = period / math.tau

    a = max([amplitude, 1])
    s = math.asin(1 / (a)) * (period)

    return a * (2 ** (10 * (t - 1))) * math.sin((s - t) / period)


def ease_elastic_out(t, period=0.2, amplitude=1):
    return 1 - ease_elastic_in(1 - t, period, amplitude)


def ease_elastic(t, period_in=0.2, amplitude_in=1, period_out=0.2, amplitude_out=1):
    t = t * 2 - 1

    if t < 0:
        p = period_in / math.tau
        a = max([amplitude_in, 1])
        s = math.asin(1 / a) * p

        return a * 2 ** (10 * t) * math.sin((s - t) / p)

    else:
        p = period_out / math.tau
        a = max([amplitude_out, 1])
        s = math.asin(1 / a) * p

        return 2 - a * 2 ** (-10 * t) * math.sin((s + t) / p) / 2


def ease_exponential_in(t, base=2):
    return base ** (10 * t - 10)


def ease_exponential_out(t, base=2):
    return 1 - (base ** (-10 * t))


def ease_exponential(t, base_in=2, base_out=2):
    t *= 2
    if t <= 1:
        return (base_in ** (10 * t - 10)) / 2
    else:
        return (2 - base_out ** (10 - 10 * t)) / 2
