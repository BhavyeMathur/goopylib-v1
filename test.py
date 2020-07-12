from goopylib.imports import *

#create_custom_ease()

window = GraphWin("Test Window", width=800, height=800, autoflush=False)

l = Line(Point(100, 400), Point(300, 200), Point(700, 400), outline_width=200, cursor="x").draw(window)

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    mouse_pos = window.check_left_mouse_click()

    if l.is_clicked(mouse_pos):
        print("It workd!")

    key = window.check_key_press()
    if key is not None:
        pass
    l.draw(window)
    window.update_win()
