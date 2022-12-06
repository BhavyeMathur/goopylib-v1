"""
goopylib module initialization
"""

# noinspection PyUnresolvedReferences
from python.core import *
# noinspection PyUnresolvedReferences
from python.window import *
# noinspection PyUnresolvedReferences
from python.keyboard import *

# noinspection PyUnresolvedReferences
from python.triangle import *

# noinspection PyUnresolvedReferences
import python.easing as easing
# noinspection PyUnresolvedReferences
import python.color as color

try:
    # noinspection PyUnresolvedReferences
    import goopylib.easing as easing
    # noinspection PyUnresolvedReferences
    import goopylib.color as color
    # noinspection PyUnresolvedReferences
    from goopylib.core import *
    # noinspection PyUnresolvedReferences
    from goopylib.window import *
    init()
except ModuleNotFoundError:  # Exception is raised when building the goopylib documentation with sphinx
    print("Building Documentation")
