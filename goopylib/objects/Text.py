from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *

class Text(GraphicsObject):

    def __init__(self, p, text, style=None, font_size=None, font_face=None, font_style=None, font_colour=None,
                 justify="center", layer=0):

        self.anchor = p.clone()
        GraphicsObject.__init__(self, style=style, options=["justify", "fill", "text", "font"], layer=layer)

        if style is None:
            self.style = global_style
        else:
            self.style = style

        if isinstance(font_colour, Colour):
            self.outline = font_colour
        elif font_colour in STYLES[self.style].keys():
            self.outline = STYLES[self.style][font_colour]
        else:
            if "outline" in STYLES[self.style].keys():
                self.outline = STYLES[self.style]["outline"]
            else:
                self.outline = STYLES["default"]["outline"]

        if isinstance(font_size, int):
            self.font_size = font_size
        elif font_size in STYLES[self.style].keys():
            self.font_size = STYLES[self.style][font_size]
        else:
            if "font size" in STYLES[self.style].keys():
                self.font_size = STYLES[self.style]["font size"]
            else:
                self.font_size = STYLES["default"]["font size"]

        if font_style in STYLES[self.style].keys():
            self.font_style = STYLES[self.style][font_style]
        elif isinstance(font_style, str):
            self.font_style = font_style
        else:
            if "font style" in STYLES[self.style].keys():
                self.font_style = STYLES[self.style]["font style"]
            else:
                self.font_style = STYLES["default"]["font style"]

        if font_face in STYLES[self.style].keys():
            self.font = STYLES[self.style][font_face]
        elif isinstance(font_face, str):
            self.font = font_face
        else:
            if "font" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font face"]
            else:
                self.font = STYLES["default"]["font face"]

        if justify in STYLES[self.style].keys():
            self.justify = STYLES[self.style][justify]
        elif isinstance(justify, str):
            self.justify = justify
        else:
            if "justify" in STYLES[self.style].keys():
                self.justify = STYLES[self.style]["justify"]
            else:
                self.justify = STYLES["default"]["justify"]

        self._initial_font_size = self.font_size

        self.set_size(self.font_size, False)

        self.set_fill(self.outline)
        self.set_face(self.font)

        self.set_style(self.font_style)
        self.set_text_colour = self.set_fill

        self.set_justify(self.justify)

        self.set_text(text)

    def __repr__(self):
        return "Text({}, '{}')".format(self.anchor, self.get_text())

    def _draw(self, canvas, options):
        p = self.anchor
        x, y = canvas.to_screen(p.x, p.y)
        self.set_size(abs(int(self._initial_font_size / canvas.trans.x_scale)), False)
        return canvas.create_text(x, y, options)

    def _move(self, dx, dy):
        self.anchor.change_direction(dx, dy)

    def is_clicked(self, mouse_pos):
        return False

    def clone(self):
        other = Text(self.anchor, self.config['text'])
        other.config = self.config.copy()
        return other

    def set_text(self, text):
        self._reconfig("text", text)

    def get_text(self):
        return self.config["text"]

    def get_anchor(self):
        return self.anchor.clone()

    def set_face(self, face):
        f, s, b = self.config['font']
        self._reconfig("font", (face, s, b))

    def set_justify(self, justify):
        self._reconfig("justify", justify)

    def set_size(self, size, _update_init=True):
        f, s, b = self.font, size, self.font_style
        self.font_size = size

        if _update_init:
            self._initial_font_size = size
        self._reconfig("font", (f, size, b))

    def set_style(self, style):
        if style in ['bold', 'normal', 'italic', 'bold italic']:
            f, s, b = self.config['font']
            self._reconfig("font", (f, s, style))
        else:
            raise GraphicsError("Text stlye must be one of ['bold', 'normal', 'italic', 'bold italic']")

    def set_text_colour(self, colour):
        self.set_fill(colour)
