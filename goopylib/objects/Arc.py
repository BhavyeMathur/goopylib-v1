from goopylib.objects.GraphicsObject import GraphicsObject

class Arc(GraphicsObject):
    def __init__(self, p1, angle, radius, radius2=None, style=None, fill=None, outline=None, width=None, cursor="arrow",
                 window=None):
        self.angle = angle

        GraphicsObject.__init__(self, style=style, options=["fill", "font_colour", "width"], cursor=cursor, window=window)

        self.anchor = p1

        self.radius1 = radius
        if radius2 is None:
            self.radius2 = radius

        # self.equation = VectorEquation()

    def _draw(self, canvas, options):
        pass
