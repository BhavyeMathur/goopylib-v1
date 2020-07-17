from goopylib.imports import *

window = GraphWin("Test Window", width=800, height=800, autoflush=False)

"""
Line(Point(0, 400), Point(470, 400), outline_width=10, outline=BLACK, arrow_scale=2).draw(window)

Line(Point(510, 382), Point(340, 272), arrow="both", outline=BLACK).draw(window)
Line(Point(505, 425), Point(340, 425), arrow="both", outline=BLACK).draw(window)
Line(Point(320, 390), Point(320, 290), arrow="both", outline=BLACK).draw(window)

Text(Point(422.5, 445), "d1", font_size=15).draw(window)
Text(Point(440, 305), "d2", font_size=15).draw(window)
Text(Point(290, 340), "d3", font_size=15).draw(window)

Polygon(Point(505, 404), Point(340, 300), Point(340, 404), fill=BLACK).draw(window)
"""

"""

Line(Point(400, 250), Point(400, 50), Point(100, 250), outline=BLACK, outline_width=30).draw(window)
Line(Point(400, 500), Point(400, 300), Point(100, 500), outline=BLACK, outline_width=30,
     capstyle="butt", joinstyle="bevel").draw(window)
Line(Point(400, 750), Point(400, 550), Point(100, 750), outline=BLACK, outline_width=30,
     capstyle="projecting", joinstyle="miter").draw(window)

Text(Point(170, 80), "'round' Capstyle\n& Joinstyle", font_size=15, font_face="Century Gothic").draw(window)
Text(Point(170, 330), "'butt' Capstyle\n& 'bevel' Joinstyle", font_size=15, font_face="Century Gothic").draw(window)
Text(Point(170, 580), "'projecting' Capstyle\n& 'miter' Joinstyle", font_size=15, font_face="Century Gothic").draw(window)

"""

"""
radius1 = 700
radius2 = 700
example_arc = Arc(Point(400, 400), start_angle=0, end_angle=360, radius=700, resolution=20).draw(window)

Line(Point(400, 400 - radius2/2), Point(400, 400 + radius2/2)).draw(window)
Line(Point(400 - radius1/2, 400), Point(400 + radius1/2, 400)).draw(window)
"""

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

""""
rect = Rectangle(Point(100, 100), Point(500, 500), fill=DARKER_GREY, outline=LIGHT_GREY, outline_width=4).draw(window)
rect.set_draggable_y()"""

img = Image(Point(400, 400), "Examples/Pac-Man-Animation Example/textures/PacMan1.png").draw(window)

#img.animate_skew_x(2, time=1, allow_duplicate=False)
img.animate_change_contrast(200, time=5, allow_duplicate=False)
#img.set_contrast(200)
#img.animate_change_skew_y(-2, time=1, allow_duplicate=False)

while True:
    mouse_pos = window.get_mouse_position()

    """
    if not window.check_left_mouse_down():
        if rect.is_clicked(mouse_pos):
            rect.animate_set_fill(DARK_WHITE, time=0.2, allow_duplicate=False)
            rect.animate_set_outline(DARKER_GREY, time=0.2, allow_duplicate=False)
            rect.animate_set_outline_width(8, time=0.2, allow_duplicate=False)
            rect.glide_to_x(340, time=0.2, allow_duplicate=False)
        else:
            rect.animate_set_fill(DARKER_GREY, time=0.2, allow_duplicate=False)
            rect.animate_set_outline(LIGHT_GREY, time=0.2, allow_duplicate=False)
            rect.animate_set_outline_width(4, time=0.2, allow_duplicate=False)
            rect.glide_to_x(300, time=0.2, allow_duplicate=False)
    """

    #img.animate_rotate(360, 2, allow_duplicate=False)
    window.update_win()
