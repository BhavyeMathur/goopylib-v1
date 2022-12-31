"""
goopylib module initialization
"""

import os
import shutil

os.makedirs("goopylib", exist_ok=True)
for file in os.listdir(os.path.dirname(__file__)):
    if file.startswith("goopylib") and file.endswith(".so"):
        shutil.copy(f"{os.path.dirname(__file__)}/{file}", os.getcwd() + "/goopylib")

from goopylib.core.core import *
from goopylib.core.window import *
from goopylib.objects import *

from goopylib.events.keyboard import *
from goopylib.events.mouse import *
