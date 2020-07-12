from goopylib.imports import *

#create_custom_ease()

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
x = 10
colour_grad1 = ColourGradient(LIGHTER_GREEN, DARKEST_GREEN, x)
colour_grad2 = ColourGradient(LIGHTER_BLUE, DARKEST_BLUE, x)
colour_grad3 = ColourGradient(LIGHTER_PURPLE, DARKEST_PURPLE, x)
points = [Point(50, 400), Point(150, 200), Point(200, 600), Point(400, 100), Point(500, 200), Point(700, 700), ]

for p in points:
    Circle(p, 5, fill=VIOLET, outline_width=0).draw(window)

for i in range(x):
    CurvedLine(*points, interpolation="cubic", resolution=i, outline=colour_grad2[i]).draw(window)
    CurvedLine(*points, interpolation="hermite", resolution=i, outline=colour_grad3[i], tension=0, bias=0).draw(window)

    CurvedLine(*points, interpolation="cosine", resolution=i, outline=colour_grad1[i]).draw(window)
"""

res = 10
CurvedLine(Point(100, 400), Point(400, 100), Point(700, 400), resolution=res, outline=BLUE).draw(window)
line = CurvedLine(Point(100, 400), Point(400, 100), Point(700, 400), smooth=False, resolution=res, bounds_width=20, outline=GREEN).draw(window)

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    mouse_pos = window.check_left_mouse_click()
    if line.is_clicked(mouse_pos):
        print(1)
    window.update_win()
