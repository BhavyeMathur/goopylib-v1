from goopylib.objects.GraphicsObject import GraphicsObject
from goopylib.styles import *
from goopylib.constants import _root, ALL_CHARACTERS, ALIGN_OPTIONS

from tkinter import StringVar as tkStringVar
from tkinter import Entry as tkEntry
from tkinter import Frame as tkFrame
from tkinter import END as tkEND

class Entry(GraphicsObject):

    def __init__(self, p, text_width=10, fill=None, font_colour=None, font_face=None, font_size=None,
                 outline=None, font_style=None, outline_width=None, border_relief="flat", password=False, layer=0,
                 active="NORMAL", justify="left", cursor="xterm", select_colour=None, prompt_text="", tag=None,
                 bounds=None, align="center", text="", max_characters=None):

        self.anchor = p.copy()

        if not isinstance(text_width, int):
            raise GraphicsError(f"Text Width for the Entry must be an integer, not {text_width}")
        self.text_width = text_width

        if align not in ALIGN_OPTIONS:
            raise GraphicsError(f"\n\nGraphicsError: Image align must be one of {ALIGN_OPTIONS}, not {align}")
        self.align = align

        self.text = tkStringVar(_root)
        self.text.set(text)

        self.was_edited_since_last_call = False

        if isinstance(fill, Colour):
            self.fill = fill
        else:
            self.fill = STYLES["default"]["fill"]

        if isinstance(select_colour, Colour):
            self.select_colour = select_colour
        else:
            self.select_colour = STYLES["default"]["select colour"]

        if isinstance(font_colour, Colour):
            self.font_colour = font_colour
        else:
            self.font_colour = STYLES["default"]["font colour"]

        if isinstance(outline_width, int):
            self.outline_width = outline_width
        else:
            self.outline_width = STYLES["default"]["entry width"]

        if isinstance(font_size, int):
            self.font_size = font_size
        else:
            self.font_size = STYLES["default"]["font size"]

        if isinstance(font_style, str):
            self.font_style = font_style
        else:
            self.font_style = STYLES["default"]["font style"]

        if isinstance(font_face, str):
            self.font = font_face
        else:
            self.font = STYLES["default"]["font face"]

        if isinstance(justify, str):
            self.justify = justify
        else:
            self.justify = STYLES["default"]["justify"]

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
        self.max_characters = None
        self.set_max_characters(max_characters)

        self.last_graphwin = None

        GraphicsObject.__init__(self, (), layer=layer, tag=tag, bounds=bounds)

    def __repr__(self):
        if self.drawn:
            return f"Entry({self.anchor}, {self.get_text()})"
        else:
            return f"Entry({self.anchor})"

    def _draw(self, canvas, options):
        x, y = self.anchor

        if self.last_graphwin != canvas:
            self.frm = tkFrame(canvas.master)
            self.set_font_size(int(self.initial_font_size / canvas.trans.x_scale), False)

            self.last_graphwin = canvas

            self.entry = tkEntry(self.frm, width=self.text_width, textvariable=self.text, bg=self.fill, fg=self.font_colour,
                                 bd=self.outline_width, font=(self.font, self.font_size, self.font_style),
                                 insertbackground=self.font_colour, show=self.text_type, state=self.enabled,
                                 justify=self.justify, cursor="xterm", exportselection=0,
                                 selectbackground=self.select_colour, insertborderwidth=0)

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

        return canvas.create_window(x, y, window=self.frm)

    def _move(self, dx, dy):
        self.anchor.move(dx, dy)

    def _in_allowed(self, c):
        return c in self.allowed_symbols

    def was_edited(self):
        if self.was_edited_since_last_call:
            self.was_edited_since_last_call = False
            return True
        return False

    def _on_edit(self, *args):
        text = self.text.get()
        if self.max_characters is not None:
            if len(text) > self.max_characters:
                self.text.set(text[:-1])
                return

        corrected = ''.join(filter(self._in_allowed, text))
        self.text.set(corrected)

        if not self.edited:
            self.edited = True
            self.set_text(corrected.replace(self.prompt_text, "", 1))

            if self.text_type == "*":
                self.entry.config(show="*")

        self.was_edited_since_last_call = True

    def _on_enter(self, e):
        pass

    def is_clicked(self, mouse_pos):
        if self.bounds is None:
            if self.entry:
                if mouse_pos is not None:
                    width, height = self.get_width(), self.get_height()
                    if (self.anchor[0] - width / 2 > mouse_pos[0] > self.anchor[0] + width / 2) and \
                       (self.anchor[1] - height / 2 > mouse_pos[1] > self.anchor[1] + height / 2):
                        return True
            return False

        return self.bounds.is_clicked(mouse_pos)

    def allow_character(self, character):
        if character not in self.allowed_symbols and character in ALL_CHARACTERS:
            self.allowed_symbols.append(character)
        return self

    def allow_only_numeric(self, allow=True):
        if allow:
            self.allowed_symbols = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', "-", "."]
        else:
            self.allowed_symbols = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
                                    'Z', '!', '"', '#', '$', '%', '&', '\\', "'", '(', ')', '*', '+', ',', '-', '.',
                                    '/', ':', ';', '<', '=', '>', '?', '@', '[', '\'', '"', ']', '^', '_', '`', '{',
                                    '|', '}', '~', ':', " "]
        return self

    def allow_only_integers(self, allow=True):
        if allow:
            self.allowed_symbols = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', "-"]
        else:
            self.allowed_symbols = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
                                    'Z', '!', '"', '#', '$', '%', '&', '\\', "'", '(', ')', '*', '+', ',', '-', '.',
                                    '/', ':', ';', '<', '=', '>', '?', '@', '[', '\'', '"', ']', '^', '_', '`', '{',
                                    '|', '}', '~', ':', " "]
        return self

    def allow_only_positive_integers(self, allow=True):
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

    def set_max_characters(self, max_characters=None):
        self.max_characters = max_characters

        return self

    def hide_cursor(self):
        self.entry.config(insertontime=0)

    def show_cursor(self):
        self.entry.config(insertontime=1)

    def disable(self):
        self.enabled = "disabled"
        if self.entry:
            self.entry.config(state=self.enabled)

    def enable(self):
        self.enabled = "normal"
        if self.entry:
            self.entry.config(state=self.enabled)

    def toggle_enabled(self):
        self.enabled = ["disabled", "normal"].index(int(self.enabled))
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

    def get_text(self):
        return self.text.get()

    def get_anchor(self):
        return self.anchor.clone()

    def get_width(self):
        if self.entry:
            return self.entry.winfo_width()

    def get_height(self):
        if self.entry:
            return self.entry.winfo_height()

    def get_font_size(self):
        return self.font_size

    def get_font_face(self):
        return self.font

    def get_font_colour(self):
        return self.font_colour

    def get_font_style(self):
        return self.font_style

    def get_justify(self):
        return self.justify

    def get_selection_colour(self):
        return self.select_colour

    def get_maximum_characters(self):
        return self.max_characters

    def get_outline_width(self):
        return self.outline_width

    def get_fill(self):
        return self.fill

    def clone(self):
        other = Entry(self.anchor, self.text_width)
        other.config = self.config.copy()
        other.text = tkStringVar()
        other.text.set(self.text.get())
        other.fill = self.fill
        return other

    def set_text(self, t):
        self.text.set(t)
        self._update_layer()
        return self

    def set_fill(self, colour):
        self.fill = colour
        if self.entry:
            self.entry.config(bg=colour)
        self._update_layer()
        return self

    def set_face(self, font_face):
        if font_face in STYLES[self.style].keys():
            self.font = STYLES[self.style][font_face]
        elif isinstance(font_face, str):
            self.font = font_face
        else:
            if "font face" in STYLES[self.style].keys():
                self.font = STYLES[self.style]["font face"]
            else:
                self.font = STYLES["default"]["font face"]

        if self.entry:
            self.entry.config(font=(self.font, self.font_size, self.font_style))
        self._update_layer()
        return self

    def set_font_size(self, font_size, set_initial_font_size=True):
        if isinstance(font_size, int):
            self.font_size = font_size
        elif font_size in STYLES[self.style].keys():
            self.font_size = STYLES[self.style][font_size]
        else:
            if "font size" in STYLES[self.style].keys():
                self.font_size = STYLES[self.style]["font size"]
            else:
                self.font_size = STYLES["default"]["font size"]

        if set_initial_font_size:
            self.initial_font_size = round(font_size)

        if self.entry:
            self.entry.config(font=(self.font, self.font_size, self.font_style))
        self._update_layer()
        return self

    def set_font_style(self, font_style):
        if font_style in STYLES[self.style].keys():
            self.font_style = STYLES[self.style][font_style]
        elif isinstance(font_style, str):
            self.font_style = font_style
        else:
            if "font style" in STYLES[self.style].keys():
                self.font_style = STYLES[self.style]["font style"]
            else:
                self.font_style = STYLES["default"]["font style"]

        if self.entry:
            self.entry.config(font=(self.font, self.font_size, self.font_style))
        self._update_layer()
        return self

    def set_text_colour(self, colour):
        self.font_colour = colour
        if self.entry:
            self.entry.config(fg=colour)
        self._update_layer()
        return self

    def set_border_relief(self, border):
        if border not in ["flat", "groove", "raised", "ridge", "solid", "sunken"]:
            raise GraphicsError("\n\nBorder type must be one of "
                                "['flat', 'groove', 'raised', 'ridge', 'solid', 'sunken']")
        self.border_type = border
        if self.entry:
            self.entry.config(relief=border)
        self._update_layer()
        return self

    def set_width(self, text_width):
        if not isinstance(text_width, int):
            raise GraphicsError(f"Text Width for the Entry must be an integer, not {text_width}")
        self.text_width = text_width

        if self.entry:
            self.entry.config(width=text_width)

        self._update_layer()
        return self
