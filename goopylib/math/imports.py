from goopylib.math.py_bezier_curve import *

try:
    from goopylib.math.c_bezier_curve import *
except ImportError as e:
    print(f"Failed to import goopylib.math.CBezierCurve, Post this error on github.com/BhavyeMathur/goopylib/issues: {e}.")

from goopylib.math.b_spline import *

from goopylib.math.py_easing import *

from goopylib.math.triangulation import *

from goopylib.math.curves import *
from goopylib.math.interpolations import *
