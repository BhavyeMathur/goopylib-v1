"""
goopylib module initialization
"""

import sys

if sys.platform == "win32":
    import os
    os.add_dll_directory(f"{sys.prefix}/goopylib")

from goopylib.core.core import *
from goopylib.core.window import *
from goopylib.objects import *

from goopylib.events.keyboard import *
from goopylib.events.mouse import *
