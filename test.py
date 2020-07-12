from goopylib.imports import *

#create_custom_ease()

window = GraphWin("Test Window", width=800, height=800, autoflush=False)

Line(Point(0, 400), Point(470, 400), outline_width=10, outline=BLACK, arrow_scale=2).draw(window)

Line(Point(510, 382), Point(340, 272), arrow="both", outline=BLACK).draw(window)
Line(Point(505, 425), Point(340, 425), arrow="both", outline=BLACK).draw(window)
Line(Point(320, 390), Point(320, 290), arrow="both", outline=BLACK).draw(window)

Text(Point(422.5, 445), "d1", font_size=15).draw(window)
Text(Point(440, 305), "d2", font_size=15).draw(window)
Text(Point(290, 340), "d3", font_size=15).draw(window)

Polygon(Point(505, 404), Point(340, 300), Point(340, 404), fill=BLACK).draw(window)

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    mouse_pos = window.check_left_mouse_click()
    window.update_win()
