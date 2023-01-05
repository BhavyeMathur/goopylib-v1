"""
goopylib module initialization
"""

import sys

if sys.platform == "win32":
    import os
    os.add_dll_directory(f"{sys.prefix}/goopylib")

from .core import *
from .objects import *

from .events import *
