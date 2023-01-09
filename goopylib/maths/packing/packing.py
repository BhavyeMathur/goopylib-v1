"""
Module defining rectangle packing algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

try:
    from .cpp_packing import *
except ImportError:
    from .py_packing import *
