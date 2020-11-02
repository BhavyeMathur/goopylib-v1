from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *

class Text(GraphicsObject):

    def __init__(self, p, text, font_size=None, font_face=None, font_style=None, font_colour=None,
                 justify="left", text_align="center", layer=0, tag=None, bounds=None):

        self.anchor = p.copy()
        GraphicsObject.__init__(self, layer=layer, tag=tag, bounds=bounds)

        if isinstance(font_colour, Colour):
            self.outline = font_colour
        elif font_colour is None:
            self.outline = STYLES["default"]["outline"]
        else:
            raise GraphicsError("\n\nGraphicsError: font colour for Text object must be a Colour type object, "
                                f"not {font_colour}")

        if isinstance(font_face, str):
            self.font_face = font_face.lower()
        elif font_face is None:
            self.font_face = STYLES["default"]["font face"]
        else:
            raise GraphicsError(f"\n\nGraphicsError: font face for Text object must be a string, not {font_colour}")

        if isinstance(font_style, str):
            self.font_style = font_style.lower()
        elif font_style is None:
            self.font_style = STYLES["default"]["font style"]
        else:
            raise GraphicsError(f"\n\nGraphicsError: font style for Text object must be a string, not {font_style}")

        if isinstance(text_align, str):
            self.text_align = text_align.lower()
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
                raise GraphicsError(
                    "Text align must be one one of ['top', 'topright', 'right', 'bottomright', 'bottom', "
                    f"'bottomleft', 'left', 'topleft', 'center'], not {text_align}")
        elif text_align is None:
            self.text_align = STYLES["default"]["text align"]
        else:
            raise GraphicsError(f"\n\nGraphicsError: text align for Text object must be a string, not {text_align}")

        if isinstance(justify, str):
            self.justify = justify.lower()
        elif justify is None:
            self.justify = STYLES["default"]["justify"]
        else:
            raise GraphicsError(f"\n\nGraphicsError: justify for Text object must be a string, not {justify}")

        if isinstance(font_size, int):
            self.font_size = font_size
        elif font_size is None:
            self.font_size = STYLES["default"]["font size"]
        else:
            raise GraphicsError(f"\n\nGraphicsError: font size for Text object must be an integer, not {font_size}")

        self._initial_font_size = self.font_size

        self.set_text_colour = self.set_fill

        self.text = str(text)

    def __repr__(self):
        return f"Text({self.anchor}, '{self.text}')"

    def _draw(self, canvas, options):
        x, y = canvas.to_screen(self.anchor[0], self.anchor[1])

        self.set_size(abs(int(self._initial_font_size / canvas.trans.x_scale)), False)

        return canvas.create_text(x, y, font=(self.font_face, self.font_size, self.font_style),
                                  anchor=self.text_align, justify=self.justify, text=self.text, fill=self.outline)

    def _move(self, dx, dy):
        self.anchor[0] += dx
        self.anchor[1] += dy

    def is_clicked(self, mouse_pos):
        if mouse_pos is None:
            return False
        if self.bounds is None:
            width = self.get_width()
            height = self.get_height()

            if self.text_align == "center":
                anchor = self.anchor
            if self.text_align == "n":
                anchor = [self.anchor[0], self.anchor[1] + height // 2]
            elif self.text_align == "ne":
                anchor = [self.anchor[0] - width // 2, self.anchor[1] + height // 2]
            elif self.text_align == "e":
                anchor = [self.anchor[0] - width // 2, self.anchor[1]]
            elif self.text_align == "se":
                anchor = [self.anchor[0] - width // 2, self.anchor[1] - height // 2]
            elif self.text_align == "s":
                anchor = [self.anchor[0], self.anchor[1] - height // 2]
            elif self.text_align == "sw":
                anchor = [self.anchor[0] + width // 2, self.anchor[1] - height // 2]
            elif self.text_align == "w":
                anchor = [self.anchor[0] + width // 2, self.anchor[1]]
            elif self.text_align == "nw":
                anchor = [self.anchor[0] + width // 2, self.anchor[1] + height // 2]

            if (anchor[0] - width // 2 < mouse_pos[0] < anchor[0] + width // 2) and \
                    (anchor[1] - height // 2 < mouse_pos[1] < anchor[1] + height // 2):
                return True
            return False

        return self.bounds.is_clicked(mouse_pos)

    def get_width(self):
        return self.font_size * len(self.text)

    def get_height(self):
        return self.font_size

    def clone(self, new_tag=None):
        other = Text(self.anchor, self.text, font_size=self._initial_font_size, font_face=self.font_face,
                     font_style=self.font_style, font_colour=self.outline, justify=self.justify,
                     text_align=self.text_align, layer=self.layer, tag=new_tag, bounds=self.bounds.clone())
        return other

    def set_text(self, text):
        self.text = str(text)
        self._update_layer()
        return self

    def get_text(self):
        return self.text

    def get_anchor(self):
        return self.anchor.copy()

    def set_face(self, face):
        if isinstance(face, str):
            self.font_face = face
        else:
            raise GraphicsError(f"\n\nGraphicsError: The font face for the text must be a string, not {face}")
        self._update_layer()
        return self

    def set_text_align(self, text_align):
        if isinstance(text_align, str):
            self.text_align = text_align
        else:
            raise GraphicsError(f"\n\nGraphicsError: The text_align for the text must be a string, not {text_align}")

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
            raise GraphicsError("\n\nGraphicsError: Text align must be one one of ['top', 'topright', 'right', "
                                f"'bottomright', 'bottom', 'bottomleft', 'left', 'topleft', 'center'] not {text_align}")
        self._update_layer()
        return self
    
    def set_justify(self, justify):
        if isinstance(justify, str):
            self.justify = justify
        else:
            raise GraphicsError("\n\nGraphicsError: Text justify must be one one of ['top', 'topright', 'right', "
                                f"'bottomright', 'bottom', 'bottomleft', 'left', 'topleft', 'center'], not {justify}")
        self._update_layer()
        return self

    def set_size(self, size, _update_init=True):
        if isinstance(size, int):
            self.font_size = size
        else:
            raise GraphicsError(f"\n\nGraphicsError: The size for the text must be an integer, not {size}")

        if _update_init:
            self._initial_font_size = self.font_size

        self._update_layer()
        return self
        
    def set_style(self, style):
        if isinstance(style, str):
            if style in {'bold', 'normal', 'italic', 'bold italic'}:
                self.font_style = style
            else:
                raise GraphicsError("Text style must be one of ['bold', 'normal', 'italic', 'bold italic']")
        else:
            raise GraphicsError("\n\nGraphicsError: Text style must be one of ['bold', 'normal', 'italic', "
                                f"'bold italic'], not {style}")

        self._update_layer()
        return self
