import math

# Interpolation Easing Functions

def py_ease_linear(t=None):
    if t is None:
        def closure(time):
            return time
        return closure
    else:
        return t


def _py_ease_poly_in(t, power):
    return t ** power

def py_ease_poly_in(t=None, power=2):
    if t is None:
        def closure(time):
            return _py_ease_poly_in(time, power)
        return closure
    else:
        return t ** power


def _py_ease_poly_out(t, power):
    return 1 - (t ** power)

def py_ease_poly_out(t=None, power=2):
    if t is None:
        def closure(time):
            return _py_ease_poly_out(time, power)
        return closure
    else:
        return 1 - (t ** power)


def _py_ease_poly(t, power_in, power_out):
    t *= 2
    if t < 1:
        return t ** power_in
    else:
        return 2 - ((2 - t) ** power_out)

def py_ease_poly(t=None, power_in=2, power_out=2):
    if t is None:
        def closure(time):
            return _py_ease_poly(time, power_in, power_out)
        return closure
    else:
        t *= 2
        if t < 1:
            return t ** power_in
        else:
            return 2 - ((2 - t) ** power_out)


def _py_ease_sin_in(t):
    return 1 - math.cos(t * 1.570796327)

def py_ease_sin_in(t=None):
    if t is None:
        def closure(time):
            return _py_ease_sin_in(time)
        return closure
    else:
        return 1 - math.cos(t * 1.570796327)


def _py_ease_sin_out(t):
    return math.sin(t * 1.570796327)

def py_ease_sin_out(t=None):
    if t is None:
        def closure(time):
            return _py_ease_sin_out(time)
        return closure
    else:
        return math.sin(t * 1.570796327)


def _py_ease_sin(t):
    return 1 - math.cos(math.pi * t) / 2

def py_ease_sin(t=None):
    if t is None:
        def closure(time):
            return _py_ease_sin(time)
        return closure
    else:
        return 1 - math.cos(3.1415926535 * t) / 2


def _py_ease_circle_in(t, factor):
    return 1 - (1 - t ** 2) ** factor

def py_ease_circle_in(t=None, factor=0.5):
    if t is None:
        def closure(time):
            return _py_ease_circle_in(time, factor)
        return closure
    else:
        return 1 - (1 - t ** 2) ** factor


def _py_ease_circle_out(t, factor):
    return 1 - _py_ease_circle_in(1 - t, factor)

def py_ease_circle_out(t=None, factor=0.5):
    if t is None:
        def closure(time):
            return _py_ease_circle_out(time, factor)
        return closure
    else:
        return (1 - t ** 2) ** factor


def _py_ease_circle(t, factor_in, factor_out):
    t *= 2
    if t <= 1:
        return (1 - (1 - t * t) ** factor_in) / 2
    else:
        return ((1 - (t - 2) * (t - 2)) ** factor_out + 1) / 2

def py_ease_circle(t=None, factor_in=0.5, factor_out=0.5):
    if t is None:
        def closure(time):
            return _py_ease_circle(time, factor_in, factor_out)
        return closure
    else:
        return _py_ease_circle(t, factor_in, factor_out)


def _py_ease_back_in(t, factor):
    return t ** 2 * ((factor + 1) * t - factor)

def py_ease_back_in(t=None, factor=1.70158):
    if t is None:
        def closure(time):
            return _py_ease_back_in(time, factor)
        return closure
    else:
        return _py_ease_back_in(t, factor)


def _py_ease_back_out(t, factor):
    return 1 - (1 - t) ** 2 * ((factor + 1) * (1 - t) - factor)

def py_ease_back_out(t=None, factor=1.70158):
    if t is None:
        def closure(time):
            return _py_ease_back_out(time, factor)
        return closure
    else:
        return 1 - (1 - t) ** 2 * ((factor + 1) * (1 - t) - factor)


def _py_ease_back(t, factor_in, factor_out):
    t *= 2
    if t < 1:
        return (t * t * ((factor_in + 1) * t - factor_in)) / 2
    else:
        return ((t - 2) ** 2 * ((factor_out + 1) * (t - 2) + factor_out) + 2) / 2

def py_ease_back(t=None, factor_in=1.70158, factor_out=1.70158):
    if t is None:
        def closure(time):
            return _py_ease_back(time, factor_in, factor_out)
        return closure
    else:
        t *= 2
        if t < 1:
            return (t * t * ((factor_in + 1) * t - factor_in)) / 2
        else:
            return ((t - 2) ** 2 * ((factor_out + 1) * (t - 2) + factor_out) + 2) / 2


def _py_ease_bounce_in(t, bounces):
    return 1 - _py_ease_bounce_out(1 - t, bounces)

def py_ease_bounce_in(t=None, bounces=None):
    if t is None:
        def closure(time):
            return _py_ease_bounce_in(time, bounces)
        return closure
    else:
        return 1 - _py_ease_bounce_out(1 - t, bounces)


def _py_ease_bounce_out(t, bounces):
    if bounces is None:
        bounces = [4 / 11, 6 / 11, 8 / 11, 3 / 4, 9 / 11, 10 / 11, 15 / 16, 21 / 22, 63 / 64]
    if t < bounces[1]:
        return bounces[0] * t ** 2
    else:
        for i in range(3, len(bounces) - 2, 3):
            if t < bounces[i]:
                t -= bounces[i - 1]
                return bounces[0] * t * t + bounces[i + 1]
    t -= bounces[-2]
    return bounces[0] * t ** 2 + bounces[-1]

def py_ease_bounce_out(t=None, bounces=None):
    if bounces is None:
        bounces = [4 / 11, 6 / 11, 8 / 11, 3 / 4, 9 / 11, 10 / 11, 15 / 16, 21 / 22, 63 / 64]
    bounces.insert(0, 1 / bounces[0] / bounces[0])

    if t is None:
        def closure(time):
            return _py_ease_bounce_out(time, bounces)
        return closure
    else:
        return _py_ease_bounce_out(t, bounces)


def _py_ease_bounce(t, bounces_in, bounces_out):
    t *= 2
    if t <= 1:
        return (1 - _py_ease_bounce_in(1 - t, bounces=bounces_in)) / 2
    else:
        return (_py_ease_bounce_out(t - 1, bounces_out) + 1) / 2

def py_ease_bounce(t=None, bounces_in=None, bounces_out=None):
    if t is None:
        def closure(time):
            return _py_ease_bounce(time, bounces_in, bounces_out)
        return closure
    else:
        t *= 2
        if t <= 1:
            return (1 - _py_ease_bounce_in(1 - t, bounces=bounces_in)) / 2
        else:
            return (_py_ease_bounce_out(t - 1, bounces_out) + 1) / 2


def _py_ease_elastic_in(t, period, amplitude):
    period = period / math.tau

    a = max([amplitude, 1])
    s = math.asin(1 / a) * period

    return a * (2 ** (10 * (t - 1))) * math.sin((s - t) / period)

def py_ease_elastic_in(t=None, period=0.2, amplitude=1):
    if t is None:
        def closure(time):
            return _py_ease_elastic_in(time, period, amplitude)
        return closure
    else:
        period = period / math.tau

        a = max([amplitude, 1])
        s = math.asin(1 / a) * period

        return a * (2 ** (10 * (t - 1))) * math.sin((s - t) / period)

def _py_ease_elastic_out(t, period, amplitude):
    return 1 - _py_ease_elastic_in(1 - t, period, amplitude)

def py_ease_elastic_out(t=None, period=0.2, amplitude=1):
    if t is None:
        def closure(time):
            return _py_ease_elastic_out(time, period, amplitude)
        return closure
    else:
        return 1 - _py_ease_elastic_in(1 - t, period, amplitude)


def _py_ease_elastic(t, period_in, amplitude_in, period_out, amplitude_out):
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

def py_ease_elastic(t=None, period_in=0.2, amplitude_in=1, period_out=0.2, amplitude_out=1):
    if t is None:
        def closure(time):
            return _py_ease_elastic(time, period_in, amplitude_in, period_out, amplitude_out)
        return closure

    else:
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


def _py_ease_exponential_in(t, base):
    return base ** (10 * t - 10)

def py_ease_exponential_in(t=None, base=2):
    if t is None:
        def closure(time):
            return _py_ease_exponential_in(time, base)
        return closure
    else:
        return base ** (10 * t - 10)


def _py_ease_exponential_out(t, base):
    return 1 - (base ** (-10 * t))

def py_ease_exponential_out(t=None, base=2):
    if t is None:
        def closure(time):
            return _py_ease_exponential_out(time, base)
        return closure
    else:
        return 1 - (base ** (-10 * t))

def _py_ease_exponential(t, base_in, base_out):
    t *= 2
    if t <= 1:
        return (base_in ** (10 * t - 10)) / 2
    else:
        return (2 - base_out ** (10 - 10 * t)) / 2

def py_ease_exponential(t=None, base_in=2, base_out=2):
    if t is None:
        def closure(time):
            return _py_ease_exponential(time, base_in, base_out)
        return closure
    else:
        t *= 2
        if t <= 1:
            return (base_in ** (10 * t - 10)) / 2
        else:
            return (2 - base_out ** (10 - 10 * t)) / 2
