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
from python.easing import *
# noinspection PyUnresolvedReferences
from python.color import *

try:
    # noinspection PyUnresolvedReferences
    from goopylib.core import *
    init()
except ModuleNotFoundError:  # Exception is raised when building the goopylib documentation with sphinx
    print("Building Documentation")
