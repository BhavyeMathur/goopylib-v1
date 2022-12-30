"""
goopylib module initialization
"""

import os
import shutil

shutil.copy(f"{os.path.dirname(__file__)}/goopylib.dylib", os.getcwd())

from goopylib.core.core import *
from goopylib.core.window import *
from goopylib.objects import *

from goopylib.events.keyboard import *
from goopylib.events.mouse import *
