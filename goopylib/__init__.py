"""
goopylib module initialization
"""

import os
import shutil

os.makedirs("goopylib", exist_ok=True)
shutil.copy(f"{os.path.dirname(__file__)}/goopylib.dylib", os.getcwd() + "/goopylib")

from goopylib.core.core import *
from goopylib.core.window import *
from goopylib.objects import *

from goopylib.events.keyboard import *
from goopylib.events.mouse import *
