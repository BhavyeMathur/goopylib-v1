"""
Module defining rectangle packing using shelf-based algorithms.

See https://pds25.egloos.com/pds/201504/21/98/RectangleBinPack.pdf

"""

try:
    from .cpp_shelf import *
except ImportError:
    from .py_shelf import *
