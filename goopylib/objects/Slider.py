from goopylib.util import GraphicsError

from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.objects.Line import Line
from goopylib.Point import Point

class Slider:
    def __init__(self, p, length, orientation, minimum, maximum, value, pointer, step=1, style=None, outline=None,
                 width=None, text=None, label="Value "):

        self.range = [minimum - 1, maximum + 1]
        self.state = value - minimum

        if not self.range[1] > value > self.range[0]:
            raise GraphicsError(
                f"\n\nSlide Bar value must between min/max values: {minimum} < value ({value}) < {maximum}")

        self.anchor = p.clone()

        self.maximum = maximum
        self.minimum = minimum

        if self.minimum > self.maximum:
            self.minimum, self.maximum = self.maximum, self.minimum
        elif self.minimum == self.maximum:
            raise GraphicsError("\n\nMinimum and Maximum value cannot be the same")

        if orientation == "vertical":
            self.p1 = Point(self.anchor.x, self.anchor.y - length / 2)
            self.p2 = Point(self.anchor.x, self.anchor.y + length / 2)

            self.scale = self.p1.distance_y(self.p2) / (self.maximum - self.minimum)
            self.value_points = [y * self.scale + self.p1.y for y in range(int((maximum - minimum + 1) / step))]
        else:
            self.p1 = Point(self.anchor.x - length / 2, self.anchor.y)
            self.p2 = Point(self.anchor.x + length / 2, self.anchor.y)

            self.scale = self.p1.distance_x(self.p2) / (self.maximum - self.minimum)
            self.value_points = [x * self.scale + self.p1.x for x in range(int((maximum - minimum + 1) / step))]

        self.graphwin = None
        self.drawn = False
        self.selected = False

        self.orientation = orientation
        self.length = length
        self.step = step

        self.pointer = pointer
        self.text = text
        self.line = None

        self.style = style
        self.outline = outline
        self.width = width

        self.style = style
        self.label = label

        self.set_value(value)
        self.reload()

        GraphicsObject.slider_instances.add(self)

    def __repr__(self):
        return "SlideBar({}, {}, {}-{})".format(self.p1, self.p2, self.minimum, self.maximum)

    def set_selected(self, selected=True):
        self.selected = selected

    def draw(self, canvas):
        self.graphwin = canvas

        if self.text is not None:
            self.text.draw(canvas)

        self.line.draw(canvas)
        self.pointer.draw(canvas)

        self.drawn = True
        return self

    def get_anchor(self):
        return self.anchor

    def reload(self):
        self.line = Line(self.p1, self.p2, style=self.style, outline=self.outline, outline_width=self.width)

        if self.text is not None:
            self.text.set_text(f"{self.label}{self.state}")

        try:
            selected_clicks = self.pointer.selected_clicks
        except AttributeError:
            selected_clicks = -1

        if self.orientation == "vertical":
            self.pointer.move_to(self.anchor.x, ((self.state - self.minimum) * self.scale) + self.p1.y)
        else:
            self.pointer.move_to(((self.state - self.minimum) * self.scale) + self.p1.x, self.anchor.y)

        self.pointer.selected_clicks = selected_clicks

    def undraw(self):
        self.line.undraw()

        if self.text is not None:
            self.text.undraw()
        self.pointer.undraw()
        self.drawn = False

    def redraw(self):
        self.undraw()
        self.reload()
        self.draw(self.graphwin)

    def set_value(self, value):
        if value < self.minimum or value > self.maximum:
            raise GraphicsError(
                f"\n\nValue to set the Slider Bar must be within {self.minimum} and {self.maximum} not {value}")
        self.state = value
        try:
            self.redraw()
        except AttributeError:
            self.reload()

    def change_value(self, value):
        self.set_value(self.state + value)

    def mouse_value(self, mouse_pos):
        self.set_value(self.minimum + self.value_points.index(min(self.value_points, key=lambda x: abs(x - mouse_pos)))
                       * self.step)

    def move(self, dx, dy):
        self.undraw()

        self.line.move(dx, dy)
        if self.text is not None:
            self.text.move(dx, dy)
        self.pointer.move(dx, dy)

        self.p1 = Point(self.p1.x + dx, self.p1.y + dy)
        self.p2 = Point(self.p2.x + dx, self.p2.y + dy)

        self.draw(self.graphwin)

    def is_clicked(self, mouse_pos):
        return self.pointer.is_clicked(mouse_pos) or self.line.is_clicked(mouse_pos)

    def is_selected(self):
        return self.pointer.is_selected()

    def get_value(self):
        return self.state

    def bind_to_mouse_wheel(self, state=True):
        if state:
            if self not in GraphicsObject.slider_instances_bound:
                GraphicsObject.slider_instances_bound.add(self)
        else:
            GraphicsObject.slider_instances_bound.discard(self)
