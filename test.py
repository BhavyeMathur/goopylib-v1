from goopylib.objects.imports import *
from goopylib.colours import *


window = GraphWin("Test Window", width=110, height=110, autoflush=False, bk_colour=DARKEST_GREEN)

"""
number_of_divisions = 17

for y_pos in range(30, 770, 45):
    gradient = ColourGradient(colour_start=RandomColourRGB(), colour_end=RandomColourRGB(), divisions=number_of_divisions)

    current_colour = 0
    for x_pos in range(30, 30 + 45 * number_of_divisions, 45):
        Rectangle(Point(x_pos - 20, y_pos - 20), Point(x_pos + 20, y_pos + 20), fill=gradient[current_colour]).draw(window)
        current_colour += 1

rect_size = 5
gap = 0
gradient = ColourGradient2D(RandomColourRGB(), RandomColourRGB(), RandomColourRGB(), RandomColourRGB(),
                            divisions_x=len(range(30, 770, (gap + rect_size * 2))),
                            divisions_y=len(range(30, 770, (gap + rect_size * 2))))

for i, y_pos in enumerate(range(30, 770, (gap + rect_size) * 2)):
    for j, x_pos in enumerate(range(30, 770, (gap + rect_size) * 2)):
        Rectangle(Point(x_pos - rect_size, y_pos - rect_size),
                  Point(x_pos + rect_size, y_pos + rect_size), fill=gradient[j][i], outline_width=0).draw(window)

"""

Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    window.update_win()
