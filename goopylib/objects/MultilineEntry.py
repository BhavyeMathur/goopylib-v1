from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import STYLES, global_style
from goopylib.colours import Colour

from tkinter import Text as tkText
from tkinter import WORD as tkWORD
from tkinter import Frame as tkFrame

class TextWidget(GraphicsObject):
    def __init__(self, p, line_length, style=None, fill=None, outline_width=None, relief=None, cursor="arrow",
                 font_size=None, font_style=None, font_colour=None, number_of_lines=2, align="center", tag=None,
                 bounds=None, select_colour=None, font_face=None):

        self.widget = None

        if style is None:
            self.style = global_style
        else:
            self.style = style

        if isinstance(fill, Colour):
            self.fill = fill
        elif fill in STYLES[self.style].keys():
            self.fill = STYLES[self.style][fill]
        else:
            if "fill" in STYLES[self.style].keys():
                self.fill = STYLES[self.style]["fill"]
            else:
                self.fill = STYLES["default"]["fill"]

        if isinstance(select_colour, Colour):
            self.select_colour = select_colour
        elif select_colour in STYLES[self.style].keys():
            self.select_colour = STYLES[self.style][select_colour]
        else:
            if "select colour" in STYLES[self.style].keys():
                self.select_colour = STYLES[self.style]["select colour"]
            else:
                self.select_colour = STYLES["default"]["select colour"]

        if isinstance(font_colour, Colour):
            self.font_colour = font_colour
        elif font_colour in STYLES[self.style].keys():
            self.font_colour = STYLES[self.style][font_colour]
        else:
            if "font colour" in STYLES[self.style].keys():
                self.font_colour = STYLES[self.style]["font colour"]
            else:
                self.font_colour = STYLES["default"]["font colour"]

        if isinstance(outline_width, int):
            self.outline_width = outline_width
        elif outline_width in STYLES[self.style].keys():
            self.outline_width = STYLES[self.style][outline_width]
        else:
            if "width" in STYLES[self.style].keys():
                self.outline_width = STYLES[self.style]["entry width"]
            else:
                self.outline_width = STYLES["default"]["entry width"]

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
            if "font face" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font face"]
            else:
                self.font = STYLES["default"]["font face"]

        self.relief = relief
        self.cursor = cursor

        self.font_size = 0
        self.initial_font_size = 0
        self.set_size(font_size, True)

        self.align = align
        self.line_length = line_length

        self.number_of_lines = number_of_lines

        self.anchor = p.clone()

        super().__init__((), tag=tag, bounds=bounds)

    def _draw(self, canvas, options):
        x, y = self.anchor

        frm = tkFrame(canvas.master)

        self.set_size(self.initial_font_size / canvas.trans.x_scale, False)

        self.widget = tkText(frm, bg=self.fill, bd=self.outline_width, relief=self.relief, width=self.line_length,
                             cursor=self.cursor, exportselection=0, fg=self.font_colour, wrap=tkWORD,
                             font=(self.font, self.font_size, self.font_style), height=self.number_of_lines,
                             insertbackground=self.font_colour)
        self.widget.pack()

        x, y = canvas.to_screen(x, y)

        return canvas.create_window(x, y, window=frm)

    def get_anchor(self):
        return self.anchor

    def set_size(self, font_size=None, _set_font_size=False):
        if isinstance(font_size, int):
            self.font_size = font_size
        elif font_size in STYLES[self.style].keys():
            self.font_size = STYLES[self.style][font_size]
        else:
            if "font size" in STYLES[self.style].keys():
                self.font_size = STYLES[self.style]["font size"]
            else:
                self.font_size = STYLES["default"]["font size"]

        if _set_font_size:
            self.initial_font_size = round(self.font_size)

        return self