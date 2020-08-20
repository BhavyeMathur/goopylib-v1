from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *

class Text(GraphicsObject):

    def __init__(self, p, text, style=None, font_size=None, font_face=None, font_style=None, font_colour=None,
                 justify="center", text_align="left", layer=0, tag=None, bounds=None):

        self.anchor = p.clone()
        GraphicsObject.__init__(self, style=style, options=["fill", "text"], layer=layer, tag=tag, bounds=bounds)

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

        self._initial_font_size = None
        self.set_size(font_size, True)

        self.set_fill(self.outline)
        self.set_face(font_face)

        self.set_style(font_style)
        self.set_text_colour = self.set_fill

        self.set_justify(justify)
        self.set_text_align(text_align)

        self.set_text(str(text))

    def __repr__(self):
        return f"Text({self.anchor}, '{self.config['text']}')"

    def _draw(self, canvas, options):
        x, y = canvas.to_screen(self.anchor.x, self.anchor.y)
        self.set_size(abs(int(self._initial_font_size / canvas.trans.x_scale)), False)

        return canvas.create_text(x, y, options, font=(self.font, self.font_size, self.font_style),
                                  anchor=self.text_align, justify=self.justify)

    def _move(self, dx, dy):
        self.anchor.move(dx, dy)

    def is_clicked(self, mouse_pos):
        if mouse_pos is None:
            return False
        if self.bounds is None:
            width = self.get_width()
            height = self.get_height()
            if (self.anchor.x - width / 2 < mouse_pos.x < self.anchor.x + width / 2) and \
                    (self.anchor.y - height / 2 < mouse_pos.y < self.anchor.y + height / 2):
                return True
            return False

        return self.bounds.is_clicked(mouse_pos)

    def get_width(self):

        return self.font_size * len(self.config["text"])

    def get_height(self):
        return self.font_size

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
        if face in STYLES[self.style].keys():
            self.font = STYLES[self.style][face]
        elif isinstance(face, str):
            self.font = face
        elif face is None:
            if "font" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font face"]
            else:
                self.font = STYLES["default"]["font face"]
        else:
            raise GraphicsError(f"The font face for the text must be a string, not {face}")

        return self

    def set_text_align(self, text_align):
        if text_align in STYLES[self.style].keys():
            self.text_align = STYLES[self.style][text_align]
        elif isinstance(text_align, str):
            self.text_align = text_align
        elif text_align is None:
            if "text align" in STYLES[self.style].keys():
                self.text_align = STYLES[self.style]["text align"]
            else:
                self.text_align = STYLES["default"]["text align"]

        if self.text_align == "top":
            self.text_align = "n"
        elif self.text_align == "topright":
            self.text_align = "ne"
        elif self.text_align == "right":
            self.text_align = "e"
        elif self.text_align == "bottomright":
            self.text_align = "se"
        elif self.text_align == "bottom":
            self.text_align = "s"
        elif self.text_align == "bottomleft":
            self.text_align = "sw"
        elif self.text_align == "left":
            self.text_align = "w"
        elif self.text_align == "topleft":
            self.text_align = "nw"
        elif self.text_align == "center":
            pass
        else:
            raise GraphicsError("Text align must be one one of 'top', 'topright', 'right', 'bottomright', 'bottom', "
                                f"'bottomleft', 'left', 'topleft', 'center', not {text_align}")
        return self
    
    def set_justify(self, justify):
        if justify in STYLES[self.style].keys():
            self.justify = STYLES[self.style][justify]
        elif isinstance(justify, str):
            self.justify = justify
        elif justify is None:
            if "justify" in STYLES[self.style].keys():
                self.justify = STYLES[self.style]["justify"]
            else:
                self.justify = STYLES["default"]["justify"]
        else:
            raise GraphicsError("Text justify must be one one of 'top', 'topright', 'right', 'bottomright', 'bottom', "
                                f"'bottomleft', 'left', 'topleft', 'center', not {justify}")
        return self

    def set_size(self, size, _update_init=True):
        if isinstance(size, int):
            self.font_size = size
        elif size in STYLES[self.style].keys():
            self.font_size = STYLES[self.style][size]
        elif size is None:
            if "font size" in STYLES[self.style].keys():
                self.font_size = STYLES[self.style]["font size"]
            else:
                self.font_size = STYLES["default"]["font size"]
        else:
            raise GraphicsError(f"The size for the text must be an integer, not {size}")

        if _update_init:
            self._initial_font_size = self.font_size

        return self
        
    def set_style(self, style):
        if style in STYLES[self.style].keys():
            self.font_style = STYLES[self.style][style]
        elif isinstance(style, str):
            if style in {'bold', 'normal', 'italic', 'bold italic'}:
                self.font_style = style
            else:
                raise GraphicsError("Text stlye must be one of 'bold', 'normal', 'italic', 'bold italic'")
        elif style is None:
            if "font style" in STYLES[self.style].keys():
                self.font_style = STYLES[self.style]["font style"]
            else:
                self.font_style = STYLES["default"]["font style"]
        else:
            raise GraphicsError("Text stlye must be one of ['bold', 'normal', 'italic', 'bold italic']")

        return self
