import goopylib.objects._BBox as gpBBox
from goopylib.styles import *


class Line(gpBBox.BBox):

    def __init__(self, p1, p2, bounds=None, style=None, outline=None, outline_width=None, arrow=None, cursor="arrow",
                 window=None):

        self.set_outline = self.set_fill

        gpBBox.BBox.__init__(self, p1, p2, bounds=bounds, outline=outline, outline_width=outline_width, style=style,
                             options=["arrow", "width", "fill"], cursor=cursor, window=window)

        if arrow is not None:
            try:
                self.set_arrow(STYLES[self.style][arrow])
            except KeyError:
                self.set_arrow(arrow)
        else:
            self.set_arrow(self.config["arrow"])

    def __repr__(self):
        return "Line({}, {})".format(str(self.p1), str(self.p2))

    def clone(self):
        other = Line(self.p1, self.p2)
        other.config = self.config.copy()
        return other

    def _draw(self, canvas, options):
        p1 = self.p1
        p2 = self.p2
        x1, y1 = canvas.to_screen(p1.x, p1.y)
        x2, y2 = canvas.to_screen(p2.x, p2.y)
        self.graphwin = canvas

        return canvas.create_line(x1, y1, x2, y2, options)

    def set_arrow(self, option):
        if option.lower() not in ["first", "last", "both", "none"]:
            raise GraphicsError("\n\nArrow option for line must be one of ['first', 'last', 'both', 'none']")
        self._reconfig("arrow", option)

    def remove_arrows(self):
        self.set_arrow("none")

    def set_arrow_both(self):
        self.set_arrow("none")

    def set_arrow_first(self):
        self.set_arrow("none")

    def set_arrow_last(self):
        self.set_arrow("none")
