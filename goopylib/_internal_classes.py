class Transform:
    """Internal class for 2-D coordinate transformations"""

    def __init__(self, w, h, x_low, y_low, x_high, y_high):
        # w, h are width and height of window
        # (x_low,y_low) coordinates of lower-left [raw (0,h-1)]
        # (x_high,y_high) coordinates of upper-right [raw (w-1,0)]
        xspan = (x_high - x_low)
        yspan = (y_high - y_low)
        self.x_base = x_low
        self.y_base = y_high
        self.x_scale = xspan / w
        self.y_scale = yspan / h

    def screen(self, x, y):
        # Returns x,y in screen (actually window) coordinates
        xs = (x - self.x_base) / self.x_scale
        ys = (self.y_base - y) / self.y_scale
        return int(xs + 0.5), int(ys + 0.5)

    def world(self, xs, ys):
        # Returns xs,ys in world coordinates
        x = xs * self.x_scale + self.x_base
        y = self.y_base - ys * self.y_scale
        return x, y


class VectorEquation:
    def __init__(self, equation):
        self.equation = equation

    def __repr__(self):
        return self.equation

    def is_clicked(self, pos):
        if pos is not None:
            x = pos.x
            y = pos.y
            return eval(self.equation)
    
    def check_on_edge(self, pos):
        return False

    def check_overlapping(self, other):
        return False
