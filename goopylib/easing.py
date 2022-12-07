from typing import Callable

EASING_TYPE = Callable[[float], float]


# noinspection PyUnresolvedReferences
def ease_linear() -> EASING_TYPE:
    r"""Returns a linear easing function

    .. math::

        \text{ease\_linear}(t) = t \qquad \footnotesize{0 \leq t \leq 1}

    .. image:: ../../_static/easing/linear.png
        :width: 33%
        :align: center

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.EaseLinear()
            >>> ease(0.4)
            0.4
    """


# noinspection PyUnusedLocal, PyUnresolvedReferences
def ease_poly(power: float = 6) -> EASING_TYPE:
    r"""Returns a polynomial easing function

    .. math::

        \text{ease\_easing}(t) = t^{\text{power}} \qquad \footnotesize{0 \leq t \leq 1}

    Args:
        power (float) -> EASING_TYPE: The exponent defining the easing. Defaults to ``6``.

    Variants:

        .. function:: ease_poly_in()
        .. function:: ease_poly_out()

    .. image:: ../../_static/easing/polynomial.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_poly()
            >>> ease(0.5)
            0.015625
    """


# noinspection PyUnusedLocal
def ease_poly_in(power: float = 6) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal
def ease_poly_out(power: float = 6) -> EASING_TYPE:
    pass


# noinspection PyUnresolvedReferences
def ease_quad() -> EASING_TYPE:
    r"""Returns a quadratic easing function

    .. math::

        \text{ease\_quad}(t) = t^{2} \qquad \footnotesize{0 \leq t \leq 1}

    Variants:

        .. function:: ease_quad_in()
        .. function:: ease_quad_out()

    .. image:: ../../_static/easing/quadratic.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_quad()
            >>> ease(0.5)
            0.025
    """


def ease_quad_in() -> EASING_TYPE:
    pass


def ease_quad_out() -> EASING_TYPE:
    pass


# noinspection PyUnresolvedReferences
def ease_cubic() -> EASING_TYPE:
    r"""Returns a cubic easing function

    .. math::

        \text{ease\_cubic}(t) = t^{3} \qquad \footnotesize{0 \leq t \leq 1}

    Variants:

        .. function:: ease_cubic_in()
        .. function:: ease_cubic_out()

    .. image:: ../../_static/easing/cubic.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_cubic()
            >>> ease(0.5)
            0.0125
    """


def ease_cubic_in() -> EASING_TYPE:
    pass


def ease_cubic_out() -> EASING_TYPE:
    pass


# noinspection PyUnresolvedReferences
def ease_quart() -> EASING_TYPE:
    r"""Returns a quartic easing function

    .. math::

        \text{ease\_quart}(t) = t^{4} \qquad \footnotesize{0 \leq t \leq 1}

    Variants:

        .. function:: ease_quart_in()
        .. function:: ease_quart_out()

    .. image:: ../../_static/easing/quartic.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_quart()
            >>> ease(0.5)
            0.0625
    """


def ease_quart_in() -> EASING_TYPE:
    pass


def ease_quart_out() -> EASING_TYPE:
    pass


# noinspection PyUnresolvedReferences
def ease_quint() -> EASING_TYPE:
    r"""Returns a quintic easing function

    .. math::

        \text{ease\_quint}(t) = t^{5} \qquad \footnotesize{0 \leq t \leq 1}

    Variants:

        .. function:: ease_quint_in()
        .. function:: ease_quint_out()

    .. image:: ../../_static/easing/quintic.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_quint()
            >>> ease(0.5)
            0.03125
    """


def ease_quint_in() -> EASING_TYPE:
    pass


def ease_quint_out() -> EASING_TYPE:
    pass


# noinspection PyUnresolvedReferences
def ease_sin() -> EASING_TYPE:
    r"""Returns a sine easing function

    .. math::

        \text{ease\_sin}(t) = 1 - \text{cos}(\frac{\pi}{2}t) \qquad \footnotesize{0 \leq t \leq 1}

    Variants:

        .. function:: ease_sin_in()
        .. function:: ease_sin_out()

    .. image:: ../../_static/easing/sine.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_sin()
            >>> ease(0.5)
            0.29289381
    """


def ease_sin_in() -> EASING_TYPE:
    pass


def ease_sin_out() -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal, PyUnresolvedReferences
def ease_exp(base: float = 2.718281828459045) -> EASING_TYPE:
    r"""Returns an exponential easing function

    .. math::

        \text{ease\_exp}(t) = \text{base}^{10(t - 1)} \qquad \footnotesize{0 \leq t \leq 1}

    Args:
        base (float) -> EASING_TYPE: The base of the exponential function. Defaults to ``e``.

    Variants:

        .. function:: ease_exp_in()
        .. function:: ease_exp_out()

    .. image:: ../../_static/easing/exponential.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_exp()
            >>> ease(0.2)
            0.0012393762590363622
    """


# noinspection PyUnusedLocal
def ease_exp_in(base: float = 2.718281828459045) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal
def ease_exp_out(base: float = 2.718281828459045) -> EASING_TYPE:
    pass


# noinspection PyUnresolvedReferences
def ease_circle() -> EASING_TYPE:
    r"""Returns a circular easing function

    .. math::

        \text{ease\_circle}(t) = 1 - \sqrt{1 - t^2} \qquad \footnotesize{0 \leq t \leq 1}

    Variants:

        .. function:: ease_circle_in()
        .. function:: ease_circle_out()

    .. image:: ../../_static/easing/circle.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_circle()
            >>> ease(0.2)
            0.04174243286252022
    """


def ease_circle_in() -> EASING_TYPE:
    pass


def ease_circle_out() -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal, PyUnresolvedReferences
def ease_back(factor: float = 1.70158) -> EASING_TYPE:
    r"""Returns a back easing function

    .. math::

        \text{ease\_back}(t) = (\text{factor} + 1)\sdot t^3 - \text{factor}\sdot t^2 \qquad \footnotesize{0 \leq t
        \leq 1}

    Args:
        factor (float) -> EASING_TYPE: The scale of the easing's stretch. Defaults to ``1.70158``.

    Variants:

        .. function:: ease_back_in()
        .. function:: ease_back_out()

    .. image:: ../../_static/easing/back.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_back()
            >>> ease(0.2)
            -0.0496758408844471
    """


# noinspection PyUnusedLocal
def ease_back_in(factor: float = 1.70158) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal
def ease_back_out(factor: float = 1.70158) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal, PyUnresolvedReferences
def ease_elastic(factor: int = 3) -> EASING_TYPE:
    r"""Returns an elastic easing function

    .. math::

        \text{ease\_back}(t) = 2^{10(t - 1)}\text{sin}(\frac{t\pi}{2}(1 + 4\sdot \text{factor)}) \qquad
        \footnotesize{0 \leq t \leq 1}

    Args:
        factor (int) -> EASING_TYPE: The number of elastic oscillations. Defaults to ``3``.

    Variants:

        .. function:: ease_elastic_in()
        .. function:: ease_elastic_out()

    .. image:: ../../_static/easing/elastic.png

    ----------

    Raises:
        TypeError: easing argument must be a :obj:`float`
        ValueError: easing argument must be between 0 and 1 (inclusive)

    Examples:

        .. code-block:: python

            >>> ease = gp.ease_elastic()
            >>> ease(0.2)
            0.007430128753185272
    """


# noinspection PyUnusedLocal
def ease_elastic_in(factor: int = 3) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal
def ease_elastic_out(factor: int = 3) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal, PyUnresolvedReferences
def ease_bounce(bounces: int = 4, damping: float = 0.4) -> EASING_TYPE:
    r"""Returns a bounce easing function

        Args:
            bounces (int) -> EASING_TYPE: The number of bounces in the easing. Defaults to ``4``.
            damping (float) -> EASING_TYPE: The energy during each bounce. Defaults to ``0.4``.

        Variants:

            .. function:: ease_bounce_in()
            .. function:: ease_bounce_out()

        .. image:: ../../_static/easing/bounce.png

        ----------

        Raises:
            TypeError: easing argument must be a :obj:`float`
            ValueError: easing argument must be between 0 and 1 (inclusive)

        Examples:

            .. code-block:: python

                >>> ease = gp.ease_bounce()
                >>> ease(0.2)
                0.025422684848308563
        """


# noinspection PyUnusedLocal
def ease_bounce_in(bounces: int = 4, damping: float = 0.4) -> EASING_TYPE:
    pass


# noinspection PyUnusedLocal
def ease_bounce_out(bounces: int = 4, damping: float = 0.4) -> EASING_TYPE:
    pass


# TODO move to C++ API
# noinspection PyUnusedLocal,PyUnresolvedReferences
def combine_easing(easing1: EASING_TYPE, easing2: EASING_TYPE) -> EASING_TYPE:
    """Combines 2 easing functions together.

    Args:
        easing1: the 1st easing function for ``0 ≤ t < 0.5``
        easing2: the 2nd easing function ``0.5 ≤ t ≤ 1``

    Raises:
        TypeError: ``easing1`` and ``easing2`` must be easing functions

    Examples:

        .. code-block:: python

            >>> ease1 = gp.ease_elastic_in()
            >>> ease2 = gp.ease_bounce_out()
            >>> ease = combine_easing(ease1, ease2)

        .. image:: ../../_static/easing/combined.png
            :width: 50%
            :align: center
    """

    if callable(easing1):
        if callable(easing2):
            def closure(t: float) -> float:
                if t < 0.5:
                    return easing1(2 * t) / 2
                else:
                    return (1 + easing2(2 * t - 1)) / 2

            return closure

        raise TypeError(f"Easing function expected, got {type(easing2)}")
    raise TypeError(f"Easing function expected, got {type(easing1)}")
