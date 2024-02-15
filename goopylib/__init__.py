"""
goopylib module initialization
"""

import sys

if sys.platform == "win32":
    import os
    os.add_dll_directory(f"{sys.prefix}/goopylib")


__version__ = "2.0.0"

# pylint: disable=wrong-import-position

from .core import *
from .objects import *
from .maths import *
from .events import *
from .scene import *

# pylint: enable=wrong-import-position
