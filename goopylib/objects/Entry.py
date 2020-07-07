from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *
from goopylib.constants import _root

from tkinter import StringVar as tkStringVar
from tkinter import Entry as tkEntry
from tkinter import Frame as tkFrame
from tkinter import END as tkEND


class Entry(GraphicsObject):

    def __init__(self, p, text_width=10, style=None, fill=None, font_colour=None, entry=None, font=None, font_size=None,
                 outline=None, font_style=None, outline_width=None, border_relief="flat", password=False,
                 active="NORMAL", window=None, justify="center", cursor="xterm", select_colour=None, prompt_text=""):

        self.anchor = p.clone()
        self.text_width = text_width

        self.text = tkStringVar(_root)
        self.text.set("")

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

        if font in STYLES[self.style].keys():
            self.font = STYLES[self.style][font]
        elif isinstance(font, str):
            self.font = font
        else:
            if "font" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font"]
            else:
                self.font = STYLES["default"]["font"]

        if justify in STYLES[self.style].keys():
            self.justify = STYLES[self.style][justify]
        elif isinstance(justify, str):
            self.justify = justify
        else:
            if "justify" in STYLES[self.style].keys():
                self.justify = STYLES[self.style]["justify"]
            else:
                self.justify = STYLES["default"]["justify"]

        self.font_config = (self.font, self.font_size, self.font_style)
        self.entry = entry
        self.border_type = border_relief
        if password:
            self.text_type = "*"
        else:
            self.text_type = ""
        self.enabled = "normal"
        self.cursor = cursor
        self.prompt_text = prompt_text

        self.initial_font_size = self.font_size
        self.edited = False

        GraphicsObject.__init__(self, style=style, options=["fill", "outline"], window=window)

    def __repr__(self):
        return "Entry({}, {})".format(self.anchor, self.text_width)

    def _on_edit(self, e):
        if not self.edited:
            self.edited = True
            self.set_text(self.get_text().replace(self.prompt_text, "", 1))

            if self.text_type == "*":
                self.entry.config(show="*")

    def _on_enter(self, e):
        pass

    def is_clicked(self, mouse_pos):
        return False

    def disable(self):
        self.enabled = "disabled"
        if self.entry:
            self.entry.config(state=self.enabled)

    def enable(self):
        self.enabled = "normal"
        if self.entry:
            self.entry.config(state=self.enabled)

    def toggle_enabled(self):
        self.enabled = ["disabled", "normal"].index(self.enabled)
        if self.entry:
            self.entry.config(state=self.enabled)

    def set_enabled(self, active):
        if active not in ["normal", "disabled", "readonly"]:
            raise GraphicsError("\n\nState must be either normal, disabled or readonly")
        self.enabled = active
        if self.entry:
            self.entry.config(state=self.enabled)

    def set_text_type(self, text_type):
        self.text = text_type
        if self.entry:
            self.entry.config(show=self.text)

    def _draw(self, canvas, options):
        p = self.anchor
        x, y = canvas.to_screen(p.x, p.y)
        frm = tkFrame(canvas.master)

        self.set_size(self.initial_font_size / canvas.trans.x_scale, False)

        self.entry = tkEntry(frm, width=self.text_width, textvariable=self.text, bg=self.fill, fg=self.font_colour,
                             bd=self.outline_width, font=self.font_config, insertbackground=self.font_colour,
                             show=self.text_type, state=self.enabled, justify=self.justify, cursor="xterm",
                             exportselection=0, selectbackground=self.select_colour)

        if not self.edited:
            self.entry.insert(0, self.prompt_text)
            self.entry.config(show="")
        self.entry.pack()
        self.entry.focus_set()

        self.entry.bind("<Return>", self._on_enter)
        self.entry.bind("<Key>", self._on_edit)

        return canvas.create_window(x, y, window=frm)

    def get_text(self):
        if self.drawn and self.graphwin.is_open():
            return self.entry.get()
        else:
            raise GraphicsError(f"\n\nEntry can only return text when it is drawn and the window is open. Window Open"
                                f"? {self.graphwin.is_open()}, Drawn? {self.drawn}")

    def _move(self, dx, dy):
        self.anchor.changeDir(dx, dy)

    def get_anchor(self):
        return self.anchor.clone()

    def clone(self):
        other = Entry(self.anchor, self.text_width)
        other.config = self.config.copy()
        other.text = tkStringVar()
        other.text.set(self.text.get())
        other.fill = self.fill
        return other

    def set_text(self, t):
        self.entry.delete(0, tkEND)
        self.entry.insert(0, t)

    def set_fill(self, colour):
        self.fill = colour
        if self.entry:
            self.entry.config(bg=colour)

    def _set_font_component(self, which, value):
        font = (self.font, self.font_size, self.font_style)

        self.font_config = list(self.font_config)
        self.font_config[which] = value

        if self.entry:
            self.entry.config(font=font)

    def set_face(self, face):
        self._set_font_component(0, face)

    def set_size(self, size, font_size=True):
        if font_size:
            self.initial_font_size = round(size)
        self._set_font_component(1, round(size))

    def set_style(self, style):
        self._set_font_component(2, style)

    def set_text_colour(self, colour):
        self.font_colour = colour
        if self.entry:
            self.entry.config(fg=colour)

    def set_border_relief(self, border):
        if border not in ["flat", "groove", "raised", "ridge", "solid", "sunken"]:
            raise GraphicsError("\n\nBorder type must be one of "
                                "['flat', 'groove', 'raised', 'ridge', 'solid', 'sunken']")
        if self.entry:
            self.border_type = border
            self.entry.config(relief=border)
