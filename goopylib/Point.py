from goopylib.util import GraphicsError

class Point:
    def __init__(self, x, y):

        if not ((isinstance(x, int) or isinstance(x, float)) and (isinstance(y, int) or isinstance(y, float))):
            raise GraphicsError("\n\nx (x={}) & y (y={}) positions must be integers".format(x, y))

        self.x = x
        self.y = y

    def __repr__(self):
        return f"Point({self.x}, {self.y})"

    def __mul__(self, other):
        if isinstance(other, Point):
            return Point(self.x * other.x, self.y * other.y)
        elif isinstance(other, int) or isinstance(other, float):
            return Point(self.x * other, self.y * other)
        else:
            raise TypeError(f"unsupported operand type(s) for *: 'Point' and {type(other)}'")

    def __add__(self, other):
        if isinstance(other, Point):
            return Point(self.x + other.x, self.y + other.y)
        elif isinstance(other, int) or isinstance(other, float):
            return Point(self.x + other, self.y + other)
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'Point' and {type(other)}'")

    def __sub__(self, other):
        if isinstance(other, Point):
            return Point(self.x - other.x, self.y - other.y)
        elif isinstance(other, int) or isinstance(other, float):
            return Point(self.x - other, self.y - other)
        else:
            raise TypeError(f"unsupported operand type(s) for -: 'Point' and {type(other)}'")

    def __truediv__(self, other):
        if isinstance(other, Point):
            return Point(self.x / other.x, self.y / other.y)
        elif isinstance(other, int) or isinstance(other, float):
            return Point(self.x / other, self.y / other)
        else:
            raise TypeError(f"unsupported operand type(s) for /: 'Point' and {type(other)}'")
        
    def __floordiv__(self, other):
        if isinstance(other, Point):
            return Point(self.x // other.x, self.y // other.y)
        elif isinstance(other, int) or isinstance(other, float):
            return Point(self.x // other, self.y // other)
        else:
            raise TypeError(f"unsupported operand type(s) for //: 'Point' and {type(other)}'")
        
    def __pow__(self, power, modulo=None):
        if isinstance(power, Point):
            return Point(pow(self.x, power.x, modulo), pow(self.y, power.y, modulo))
        elif isinstance(power, int) or isinstance(power, float):
            return Point(pow(self.x, power, modulo), pow(self.y, power, modulo))
        else:
            raise TypeError(f"unsupported operand type(s) for **: 'Point' and {type(power)}'")

    def __lt__(self, other):
        if isinstance(other, Point):
            return abs(self.distance(Point(0, 0))) < abs(other.distance(Point(0, 0)))
        else:
            raise TypeError(f"'<' not supported between instances of 'Point' and '{type(other)}'")

    def __pos__(self):
        return Point(abs(self.x), abs(self.y))

    def __lshift__(self, other):
        if isinstance(other, Point):
            return Point(int(self.x) << int(other.x), int(self.y) << int(other.y))
        elif isinstance(other, int) or isinstance(other, float):
            return self.clone() if other % 2 == 0 else Point(self.y, self.x)
        else:
            raise TypeError(f"unsupported operand type(s) for <<: 'Point' and {type(other)}'")

    def __rshift__(self, other):
        if isinstance(other, Point):
            return Point(int(self.x) >> int(other.x), int(self.y) >> int(other.y))
        elif isinstance(other, int) or isinstance(other, float):
            return self << other
        else:
            raise TypeError(f"unsupported operand type(s) for >>: 'Point' and {type(other)}'")

    def __copy__(self):
        return Point(self.x, self.y)

    def __bytes__(self):
        return bytes(int(self.x)), bytes(int(self.y))

    def __bool__(self):
        return self.x != 0 and self.y != 0

    def __and__(self, other):
        if isinstance(other, Point):
            return Point(int(self.x) & int(other.x), int(self.y) & int(other.y))
        elif isinstance(other, int) or isinstance(other, float):
            return Point(int(self.x) & int(other), int(self.y) & int(other))
        else:
            raise TypeError(f"unsupported operand type(s) for &: 'Point' and {type(other)}'")

    def __abs__(self):
        return Point(abs(self.x), abs(self.y))

    def __ceil__(self):
        return -(-self//1)

    def __floor__(self):
        return self//1

    def __neg__(self):
        return Point(-self.x, -self.y)

    def __mod__(self, other):
        if isinstance(other, Point):
            return Point(self.x % other.x, self.y % other.y)
        elif isinstance(other, int) or isinstance(other, float):
            return Point(self.x % other, self.y % other)
        else:
            raise TypeError(f"unsupported operand type(s) for %: 'Point' and {type(other)}'")

    def __divmod__(self, other):
        return self // other, self % other

    def __eq__(self, other):
        if isinstance(other, Point):
            return self.x == other.x and self.y == other.y
        else:
            return self.x == self.y == other

    def __ne__(self, other):
        return not self == other

    def __ge__(self, other):
        return self > other or self == other

    def __gt__(self, other):
        return not (self < other or self == other)

    def __iadd__(self, other):
        self.x, self.y = self + other
        return self

    def __hex__(self):
        return hex(int(self.x)), hex(int(self.y))

    def __ilshift__(self, other):
        self.x, self.y = self << other
        return self

    def __irshift__(self, other):
        self.x, self.y = self >> other
        return self

    def __imod__(self, other):
        self.x, self.y = self % other
        return self

    def __imul__(self, other):
        self.x, self.y = self * other
        return self

    def __invert__(self):
        return Point(self.y, self.x)

    def __or__(self, other):
        if isinstance(other, Point):
            return Point(int(self.x) | int(other.x), int(self.y) | int(other.y))
        elif isinstance(other, int) or isinstance(other, float):
            return Point(int(self.x) | int(other), int(self.y) | int(other))
        else:
            raise TypeError(f"unsupported operand type(s) for |: 'Point' and {type(other)}'")

    def __ior__(self, other):
        self.x, self.y = self | other
        return self

    def __ipow__(self, other):
        self.x, self.y = self ** other
        return self

    def __isub__(self, other):
        self.x, self.y = self - other
        return self

    def __iand__(self, other):
        self.x, self.y = self & other
        return self

    def __ifloordiv__(self, other):
        self.x, self.y = self // other
        return self

    def __dir__(self):
        return "see https://github.com/BhavyeMathur/goopylib/wiki"

    def __contains__(self, item):
        return item == self.x or item == self.y

    def __ixor__(self, other):
        self.x, self.y = self ^ other
        return self
        
    def __xor__(self, other):
        if isinstance(other, Point):
            return Point(int(self.x) ^ int(other.x), int(self.y) ^ int(other.y))
        elif isinstance(other, int) or isinstance(other, float):
            return Point(int(self.x) ^ int(other), int(self.y) ^ int(other))
        else:
            raise TypeError(f"unsupported operand type(s) for ^: 'Point' and {type(other)}'")

    def __round__(self, n=None):
        return Point(round(self.x, n), round(self.y, n))

    def __len__(self):
        return 2

    def __getitem__(self, item):
        return (self.x, self.y)[item]

    def __iter__(self):
        for x in (self.x, self.y):
            yield x

    def __le__(self, other):
        return self < other or self == other

    def __itruediv__(self, other):
        self.x, self.y = self / other
        return self

    def __oct__(self):
        return oct(int(self.x)), oct(int(self.y))

    def __reversed__(self):
        return Point(self.y, self.x)

    def __deepcopy__(self, memodict={}):
        return Point(self.x, self.y)

    def distance(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError(f"\n\np2 argument for distance calculation must be a Point class, not {p2}")
        return ((p2.x - self.x) ** 2 + (p2.y - self.y) ** 2) ** 0.5

    def distance_x(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError(f"\n\np2 argument for distance calculation must be a Point class, not {p2}")
        return p2.x - self.x

    def distance_y(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError(f"\n\np2 argument for distance calculation must be a Point class, not {p2}")
        return p2.y - self.y

    def slope(self, p2):
        if not isinstance(p2, Point):
            raise GraphicsError(f"\n\np2 argument for slope calculation must be a Point class, not {p2}")
        if self.x == p2.x:
            raise GraphicsError(f"\n\nThe two points have the same x value, cannot calculate slope!")
        return (self.y - p2.y) / (self.x - p2.x)

    def clone(self):
        return Point(self.x, self.y)

    def swap(self):
        self.x, self.y = self.y, self.x

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def move_y(self, dy):
        if not (isinstance(dy, int) or isinstance(dy, float)):
            raise GraphicsError("\n\nThe value to move the point by (dy) must be a number (integer or float), "
                                f"not {dy}")
        self.y += dy
        return self

    def move_x(self, dx):
        if not (isinstance(dx, int) or isinstance(dx, float)):
            raise GraphicsError("\n\nThe value to move the point by (dx) must be a number (integer or float), "
                                f"not {dx}")
        self.x += dx
        return self

    def move(self, dx, dy):
        self.move_y(dy)
        self.move_x(dx)
        return self

    def move_to(self, x, y):
        self.move_to_x(x)
        self.move_to_y(y)
        return self

    def move_to_x(self, x):
        if not (isinstance(x, int) or isinstance(x, float)):
            raise GraphicsError(f"\n\nThe value to move the point by (x) must be a number (integer or float), not {x}")
        self.x = x
        return self

    def move_to_y(self, y):
        if not (isinstance(y, int) or isinstance(y, float)):
            raise GraphicsError(f"\n\nThe value to move the point by (y) must be a number (integer or float), not {y}")
        self.y = y
        return self

    def add(self, dx, dy):
        return self.clone().move(dx, dy)

    def set(self, x, y):
        return self.clone().move_to(x, y)

    def get_anchor(self):
        return self

    def add_y(self, dy):
        return self.clone().move_y(dy)

    def add_x(self, dx):
        return self.clone().move_x(dx)

    def set_x(self, x):
        return self.clone().move_to_x(x)

    def set_y(self, y):
        return self.clone().move_to_y(y)
