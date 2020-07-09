from goopylib.objects.imports import *
from goopylib.colours import *


window = GraphWin("Test Window", width=110, height=110, autoflush=False, bk_colour=WHITE)

entry = Entry(Point(55, 55), text_width=10, font_size=15).draw(window)
entry.allow_only_numeric()

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    window.update_win()
