from goopylib.maths.py_bezier_curve import *

try:
    from goopylib.maths.c_bezier_curve import *
except ImportError as e:
    print(f"Failed to import goopylib.math.CBezierCurve. Post this error on github.com/BhavyeMathur/goopylib/issues: {e}.")

from goopylib.maths.b_spline import *

from goopylib.maths.easing import *

from goopylib.maths.triangulation import *

from goopylib.maths.curves import *
from goopylib.maths.interpolations import *
