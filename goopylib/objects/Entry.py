from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *
from goopylib.constants import _root, ALL_CHARACTERS, ALIGN_OPTIONS

from tkinter import StringVar as tkStringVar
from tkinter import Entry as tkEntry
from tkinter import Frame as tkFrame
from tkinter import END as tkEND

class Entry(GraphicsObject):

    def __init__(self, p, text_width=10, style=None, fill=None, font_colour=None, font_face=None, font_size=None,
                 outline=None, font_style=None, outline_width=None, border_relief="flat", password=False, layer=0,
                 active="NORMAL", justify="left", cursor="xterm", select_colour=None, prompt_text="", tag=None,
                 bounds=None, align="center", text=""):

        self.anchor = p.clone()
        self.text_width = text_width

        if align not in ALIGN_OPTIONS:
            raise GraphicsError(f"\n\nGraphicsError: Image align must be one of {ALIGN_OPTIONS}, not {align}")
        self.align = align

        self.text = tkStringVar(_root)
        self.text.set(text)

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

        if font_face in STYLES[self.style].keys():
            self.font = STYLES[self.style][font_face]
        elif isinstance(font_face, str):
            self.font = font_face
        else:
            if "font face" in STYLES[self.style].keys():
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

        self.font_config = (self.font, self.font_size, self.font_style)
        self.entry = None
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

        self.allowed_symbols = ALL_CHARACTERS

        GraphicsObject.__init__(self, style=style, options=["fill"], layer=layer, tag=tag, bounds=bounds)

    def __repr__(self):
        if self.drawn:
            return f"Entry({self.anchor}, {self.get_text()})"
        else:
            return f"Entry({self.anchor})"

    def _in_allowed(self, c):
        return c in self.allowed_symbols

    def _on_edit(self, *args):
        corrected = ''.join(filter(self._in_allowed, self.text.get()))
        self.text.set(corrected)

        if not self.edited:
            self.edited = True
            self.set_text(corrected.replace(self.prompt_text, "", 1))

            if self.text_type == "*":
                self.entry.config(show="*")

    def _on_enter(self, e):
        pass

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            if mouse_pos is not None:
                width, height = self.get_width(), self.get_height()
                if (self.anchor.x - width / 2 > mouse_pos.x > self.anchor.x + width / 2) and \
                   (self.anchor.y - height / 2 > mouse_pos.y > self.anchor.y + height / 2):
                    return True
                return False

        return self.bounds.is_clicked(mouse_pos)

    def allow_character(self, character):
        if character not in self.allowed_symbols and character in ALL_CHARACTERS:
            self.allowed_symbols.append(character)
        return self

    def allow_only_numeric(self, allow=True):
        if allow:
            self.allowed_symbols = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
        else:
            self.allowed_symbols = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
                                    'Z', '!', '"', '#', '$', '%', '&', '\\', "'", '(', ')', '*', '+', ',', '-', '.',
                                    '/', ':', ';', '<', '=', '>', '?', '@', '[', '\'', '"', ']', '^', '_', '`', '{',
                                    '|', '}', '~', ':', " "]
        return self

    def allow_all_characters(self):
        self.allowed_symbols = ALL_CHARACTERS

    def allow_only_alpha(self, allow=True):
        if allow:
            self.allowed_symbols = self.allowed_symbols = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                                                           'm','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                                                           'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                                           'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                                           'W', 'X', 'Y', 'Z', " "]
        else:
            self.allowed_symbols = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '"', '#', '$', '%', '&',
                                    '\\', "'", '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?',
                                    '@', '[', '\'', '"', ']', '^', '_', '`', '{', '|', '}', '~', ':', " "]
        return self

    def allow_only_custom(self, custom):
        if not set(custom).issubset(set(ALL_CHARACTERS)):
            raise GraphicsError("The Custom list of character contains invalid characters!")

        self.allowed_symbols = custom.copy()
        return self

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
        x, y = self.anchor

        frm = tkFrame(canvas.master)

        self.set_size(self.initial_font_size / canvas.trans.x_scale, False)

        self.entry = tkEntry(frm, width=self.text_width, textvariable=self.text, bg=self.fill, fg=self.font_colour,
                             bd=self.outline_width, font=self.font_config, insertbackground=self.font_colour,
                             show=self.text_type, state=self.enabled, justify=self.justify, cursor="xterm",
                             exportselection=0, selectbackground=self.select_colour, insertborderwidth=0)

        if not self.edited:
            self.entry.insert(0, self.prompt_text)
            self.entry.config(show="")
        self.entry.pack()

        self.entry.bind("<Return>", self._on_enter)

        self.text.trace('w', self._on_edit)

        width = self.get_width()
        height = self.get_height()

        if self.align == "center":
            pass
        elif self.align == "bottom":
            y -= self.font_size / 2
        elif self.align == "top":
            y += self.font_size / 2
        elif self.align == "left":
            x += self.font_size * self.text_width / 2
        elif self.align == "right":
            x -= self.font_size * self.text_width / 2
        elif self.align == "bottomleft":
            y -= self.font_size / 2
            x += self.font_size * self.text_width / 2
        elif self.align == "bottomright":
            y -= self.font_size / 2
            x -= self.font_size * self.text_width / 2
        elif self.align == "topleft":
            y += self.font_size / 2
            x += self.font_size * self.text_width / 2
        elif self.align == "topright":
            y += self.font_size / 2
            x -= self.font_size * self.text_width / 2

        x, y = canvas.to_screen(x, y)

        return canvas.create_window(x, y, window=frm)

    def get_text(self):
        if self.drawn and self.graphwin.is_open():
            return self.entry.get()
        else:
            raise GraphicsError(f"\n\nEntry can only return text when it is drawn and the window is open. Window Open"
                                f"? {self.graphwin.is_open()}, Drawn? {self.drawn}")

    def _move(self, dx, dy):
        self.anchor.move(dx, dy)

    def hide_cursor(self):
        self.entry.config(insertontime=0)

    def show_cursor(self):
        self.entry.config(insertontime=1)

    def get_anchor(self):
        return self.anchor.clone()

    def get_width(self):
        return self.entry.winfo_width()

    def get_height(self):
        return self.entry.winfo_height()

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
