from goopylib.math.PyBezierCurve import *

try:
    from goopylib.math.CBezierCurve import *
except ImportError as e:
    print(f"Failed to import goopylib.math.CBezierCurve, Post this error on github.com/BhavyeMathur/goopylib/issues: {e}.")

from goopylib.math.BSpline import *

from goopylib.math.PyEasing import *

from goopylib.math.Triangulation import *

from goopylib.math.Curves import *
from goopylib.math.Interpolations import *
