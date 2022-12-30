"""
Module defining common easing functions
"""

from typing import Callable
import goopylib.ext.easing as __easing


class EasingType:
    """Generic Easing Type"""

    def __call__(self, t: float) -> float:
        """
        Raises:
            TypeError: easing argument must be a float
        """

        raise NotImplementedError()


def ease_linear() -> EasingType:
    r"""Returns a linear ease

    .. math::

        \text{ease\_linear}(t) = t

    Returns:
        a linear ease callable
    """
    return __easing.ease_linear()


def ease_poly(power: float = 6) -> EasingType:
    r"""Returns a polynomial ease

    .. math::

        \text{ease\_poly}(t) = t^{\text{power}}

    Args:
        power (float): The exponent defining the easing.

    Returns:
        a polynomial in-out ease callable
    """
    return __easing.ease_poly(power)


def ease_poly_in(power: float = 6) -> EasingType:
    r"""Returns a polynomial in ease

    .. math::

        \text{ease\_poly}(t) = t^{\text{power}}

    Args:
        power (float): The exponent defining the easing.

    Returns:
        a polynomial in ease callable
    """
    return __easing.ease_poly_in(power)


def ease_poly_out(power: float = 6) -> EasingType:
    r"""Returns a polynomial out ease

    .. math::

        \text{ease\_poly}(t) = t^{\text{power}}

    Args:
        power (float): The exponent defining the easing.

    Returns:
        a polynomial out ease callable
    """
    return __easing.ease_poly_out(power)


def ease_quad() -> EasingType:
    r"""Returns a quadratic ease

    .. math::

        \text{ease\_quad}(t) = t^{2}

    Returns:
        a quadratic in-out ease callable
    """
    return __easing.ease_quad()


def ease_quad_in() -> EasingType:
    r"""Returns a quadratic in ease

    .. math::

        \text{ease\_quad}(t) = t^{2}

    Returns:
        a quadratic in ease callable
    """
    return __easing.ease_quad_in()


def ease_quad_out() -> EasingType:
    r"""Returns a quadratic out ease

    .. math::

        \text{ease\_quad}(t) = t^{2}

    Returns:
        a quadratic out ease callable
    """
    return __easing.ease_quad_out()


def ease_cubic() -> EasingType:
    r"""Returns a cubic ease

    .. math::

        \text{ease\_cubic}(t) = t^{3}

    Returns:
        a cubic in-out ease callable
    """
    return __easing.ease_cubic()


def ease_cubic_in() -> EasingType:
    r"""Returns a cubic in ease

    .. math::

        \text{ease\_cubic}(t) = t^{3}

    Returns:
        a cubic in ease callable
    """
    return __easing.ease_cubic_in()


def ease_cubic_out() -> EasingType:
    r"""Returns a cubic out ease

    .. math::

        \text{ease\_cubic}(t) = t^{3}

    Returns:
        a cubic out ease callable
    """
    return __easing.ease_cubic_out()


def ease_quart() -> EasingType:
    r"""Returns a quartic ease

    .. math::

        \text{ease\_quart}(t) = t^{4}

    Returns:
        a quartic in-out ease callable
    """
    return __easing.ease_quart()


def ease_quart_in() -> EasingType:
    r"""Returns a quartic in ease

    .. math::

        \text{ease\_quart}(t) = t^{4}

    Returns:
        a quartic in ease callable
    """
    return __easing.ease_quart_in()


def ease_quart_out() -> EasingType:
    r"""Returns a quartic out ease

    .. math::

        \text{ease\_quart}(t) = t^{4}

    Returns:
        a quartic out ease callable
    """
    return __easing.ease_quart_out()


def ease_quint() -> EasingType:
    r"""Returns a quintic ease

    .. math::

        \text{ease\_quint}(t) = t^{5}

    Returns:
        a quintic in-out ease callable
    """
    return __easing.ease_quint()


def ease_quint_in() -> EasingType:
    r"""Returns a quintic in ease

    .. math::

        \text{ease\_quint}(t) = t^{5}

    Returns:
        a quintic in ease callable
    """
    return __easing.ease_quint_in()


def ease_quint_out() -> EasingType:
    r"""Returns a quintic out ease

    .. math::

        \text{ease\_quint}(t) = t^{5}

    Returns:
        a quintic out ease callable
    """
    return __easing.ease_quint_out()


def ease_circle() -> EasingType:
    r"""Returns a circular ease

    .. math::

        \text{ease\_circle}(t) = 1 - \sqrt{1 - t^2}

    Returns:
        an circular in-out ease callable
    """
    return __easing.ease_circle()


def ease_circle_in() -> EasingType:
    r"""Returns a circular in ease

    .. math::

        \text{ease\_circle}(t) = 1 - \sqrt{1 - t^2}

    Returns:
        an circular in ease callable
    """
    return __easing.ease_circle_in()


def ease_circle_out() -> EasingType:
    r"""Returns a circular out ease

    .. math::

        \text{ease\_circle}(t) = 1 - \sqrt{1 - t^2}

    Returns:
        an circular out ease callable
    """
    return __easing.ease_circle_out()


def ease_sin() -> EasingType:
    r"""Returns a sine ease

    .. math::

        \text{ease\_sin}(t) = 1 - \text{cos}(t\pi/2)

    Returns:
        a sine in-out ease callable
    """
    return __easing.ease_sin()


def ease_sin_in() -> EasingType:
    r"""Returns a sine in ease

    .. math::

        \text{ease\_sin}(t) = 1 - \text{cos}(t\pi/2)

    Returns:
        a sine in ease callable
    """
    return __easing.ease_sin_in()


def ease_sin_out() -> EasingType:
    r"""Returns a sine out ease

    .. math::

        \text{ease\_sin}(t) = 1 - \text{cos}(t\pi/2)

    Returns:
        a sine out ease callable
    """
    return __easing.ease_sin_out()


def ease_exp(base: float = 2.718281828459045) -> EasingType:
    r"""Returns an exponential ease

    .. math::

        \text{ease\_exp}(t) = \text{base}^{10(t - 1)}

    Args:
        base (float): The base of the exponential function.

    Returns:
        an exponential in-out ease callable
    """
    return __easing.ease_exp(base)


def ease_exp_in(base: float = 2.718281828459045) -> EasingType:
    r"""Returns an exponential in ease

    .. math::

        \text{ease\_exp}(t) = \text{base}^{10(t - 1)}

    Args:
        base (float): The base of the exponential function.

    Returns:
        an exponential in ease callable
    """
    return __easing.ease_exp_in(base)


def ease_exp_out(base: float = 2.718281828459045) -> EasingType:
    r"""Returns an exponential out ease

    .. math::

        \text{ease\_exp}(t) = \text{base}^{10(t - 1)}

    Args:
        base (float): The base of the exponential function.

    Returns:
        an exponential out ease callable
    """
    return __easing.ease_exp_out(base)


def ease_back(factor: float = 1.70158) -> EasingType:
    r"""Returns a back ease

    .. math::

        \text{ease\_back}(t) = (\text{factor} + 1)\times t^3 - \text{factor}\times t^2

    Args:
        factor (float): The scale of the easing's stretch.

    Returns:
        a back in-out ease callable
    """
    return __easing.ease_back(factor)


def ease_back_in(factor: float = 1.70158) -> EasingType:
    r"""Returns a back in ease

    .. math::

        \text{ease\_back}(t) = (\text{factor} + 1)\times t^3 - \text{factor}\times t^2

    Args:
        factor (float): The scale of the easing's stretch.

    Returns:
        a back in ease callable
    """
    return __easing.ease_back_in(factor)


def ease_back_out(factor: float = 1.70158) -> EasingType:
    r"""Returns a back out ease

    .. math::

        \text{ease\_back}(t) = (\text{factor} + 1)\times t^3 - \text{factor}\times t^2

    Args:
        factor (float): The scale of the easing's stretch.

    Returns:
        a back out ease callable
    """
    return __easing.ease_back_out(factor)


def ease_elastic(factor: int = 3) -> EasingType:
    r"""Returns an elastic ease

    .. math::

        \text{ease\_back}(t) = 2^{10(t - 1)}\text{sin}(t\pi/2\times(1 + 4\times\text{factor)})

    Args:
        factor (int): The number of elastic oscillations.

    Returns:
        an elastic in-out ease callable
    """
    return __easing.ease_elastic(factor)


def ease_elastic_in(factor: int = 3) -> EasingType:
    r"""Returns an elastic in ease

    .. math::

        \text{ease\_back}(t) = 2^{10(t - 1)}\text{sin}(t\pi/2\times(1 + 4\times\text{factor)})

    Args:
        factor (int): The number of elastic oscillations.

    Returns:
        an elastic in ease callable
    """
    return __easing.ease_elastic_in(factor)


def ease_elastic_out(factor: int = 3) -> EasingType:
    r"""Returns an elastic out ease

    .. math::

        \text{ease\_back}(t) = 2^{10(t - 1)}\text{sin}(t\pi/2\times(1 + 4\times\text{factor)})

    Args:
        factor (int): The number of elastic oscillations.

    Returns:
        an elastic out ease callable
    """
    return __easing.ease_elastic_out(factor)


def ease_bounce(bounces: int = 4, damping: float = 0.4) -> EasingType:
    r"""Returns a bounce ease

    Args:
        bounces (int): The number of bounces in the easing.
        damping (float): The energy retained during each bounce.

    Returns:
        a bounce in-out ease callable

    Raises:
        ValueError: damping must be ≥ 0, bounces must be ≥ 1
    """
    return __easing.ease_bounce(bounces, damping)


def ease_bounce_in(bounces: int = 4, damping: float = 0.4) -> EasingType:
    r"""Returns a bounce in ease

    Args:
        bounces (int): The number of bounces in the easing.
        damping (float): The energy retained during each bounce.

    Returns:
        a bounce in ease callable

    Raises:
        ValueError: damping must be ≥ 0, bounces must be ≥ 1
    """
    return __easing.ease_bounce_in(bounces, damping)


def ease_bounce_out(bounces: int = 4, damping: float = 0.4) -> EasingType:
    r"""Returns a bounce out ease

    Args:
        bounces (int): The number of bounces in the easing.
        damping (float): The energy retained during each bounce.

    Returns:
        a bounce out ease callable

    Raises:
        ValueError: damping must be ≥ 0, bounces must be ≥ 1
    """
    return __easing.ease_bounce_out(bounces, damping)


def combine_easing(easing1: EasingType, easing2: EasingType) -> callable:
    """Combines 2 easing functions together.
    
    The 1st easing function is used for t values below 0.5 and the 2nd easing function is used for t values above 0.5

    Args:
        easing1: the 1st easing function for t < 0.5
        easing2: the 2nd easing function for t ≥ 0.5

    Raises:
        TypeError: easing1 and easing2 must be easing functions

    Examples:

        .. code-block:: python

            >>> ease1 = gp.ease_elastic_in()
            >>> ease2 = gp.ease_bounce_out()
            >>> new_ease = combine_easing(ease1, ease2)
    """
    if callable(easing1) and callable(easing2):
        def closure(t: float) -> float:
            """
            Args:
                t: value to use to calculate the easing
            """
            if t < 0.5:
                return easing1(2 * t) / 2
            else:
                return (1 + easing2(2 * t - 1)) / 2

        return closure

    raise TypeError(f"Easing functions expected, got {type(easing1)} and {type(easing2)}")
