from goopylib.constants import _root

import goopylib.constants
import goopylib.styles
import goopylib.colours
import goopylib.colors

from goopylib.Window import Window

__all__ = ['Window', 'util', 'styles', 'constants', 'colours']
__version__ = "1.1.319a25"

from platform import system as platform_system
if platform_system() == "Windows":
    import ctypes
    ctypes.windll.shcore.SetProcessDpiAwareness(True)
