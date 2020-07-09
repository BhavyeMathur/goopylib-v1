from goopylib.imports import *

window = GraphWin("Test Window", width=110, height=110, autoflush=False, bk_colour=WHITE)
e = Entry(Point(55, 55), text_width=10).draw(window)

time.sleep(1)

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    window.update_win()
